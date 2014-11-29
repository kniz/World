#include "Button.hpp"
#include "../define/define.hpp"

namespace NE
{
	type_result NE_DLL Button::_onExecute()
	{
		//	pre:
		if(_hwnd) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		

		//	main:
		WND& module = static_cast<WND&>(arg_window_selector.getValue().getModule());
		if( ! &module) return RESULT_TYPE_ERROR;

		_parent_hwnd = module.getHWND();
		type_result result = _createButton();
		if(NEResult::hasError(result))
		{
			ALERT_ERROR(" : 버튼 생성 도중 에러 발생");

			return result | RESULT_TYPE_ERROR;
		}


		//	main:
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &Button::clone() const
	{
		return *(new Button(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &Button::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(Button::ERROR_CODE_END - 1);
			NETStringSet& arg_comments = _header.getArgumentsComments();
			arg_comments.create(8);
			arg_comments.push("Target\n버튼을 생성할 윈도우를 지정합니다.");
			arg_comments.push("글\n버튼에 씌여질 글 입니다.");
			arg_comments.push("ID\n이 버튼에 지정될 ID 입니다.\nButtonSpy에서 사용됩니다. 버튼끼리 중복되지 않도록 해야합니다.");
			arg_comments.push("왼쪽 좌표(X)");
			arg_comments.push("위 좌표(Y)");
			arg_comments.push("윈도우의 너비(Width)");
			arg_comments.push("윈도우의 높이(Height)");
			arg_comments.push("윈도우가 어떻게 보여질 것인가 (보통 : 5)");
		}

		return _header;
	}

	LPCTSTR NE_DLL Button::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}

	type_result Button::_createButton()
	{
		if( ! _parent_hwnd)
			return RESULT_TYPE_ERROR;

		_hwnd = CreateWindow(_T("BUTTON"), arg_caption.getValue().toCharPointer(), 
			WS_VISIBLE | WS_CHILD | WS_TABSTOP, arg_x.getValue(), arg_y.getValue(), 
			arg_width.getValue(), arg_height.getValue(), _parent_hwnd, (HMENU)arg_menu_id.getValue(),
			NULL, NULL);

		if( ! _hwnd)
			return RESULT_TYPE_ERROR;

		//	post:
		return RESULT_SUCCESS;
	}

	type_result Button::_onFetchArguments(NEArgumentList& tray)
	{
		tray.push(arg_window_selector);
		tray.push(arg_caption);
		tray.push(arg_menu_id);

		return SuperClass::_onFetchArguments(tray);
	}

	type_result Button::_onFetchModule()
	{
		SuperClass::_onFetchModule();

		arg_window_selector.getValue().isUsingAutoBinding() = true;
		arg_caption.setDefault("버튼1");
		arg_width.setDefault(80);
		arg_height.setDefault(20);

		return RESULT_SUCCESS;
	}

}