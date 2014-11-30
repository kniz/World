#include "ButtonClickSpy.hpp"
#include "../Button/Button.hpp"
#include "define/define.hpp"
#include <iostream>
using namespace std;

namespace NE
{
	type_result NE_DLL ButtonClickSpy::_onExecute()
	{	
		//	main:
		while(NEModule* m1= &arg_button.getValue().getModule())
		{
			Button& button = _castToButton(*m1);
			if( ! &button) break;
			Window& win = _castToWindow(button.arg_window_selector.getValue().getModule());
			if( ! &win) break;

			const MSG& msg = win.getMSG();
			
			if(msg.message == WM_COMMAND)
			{	/*	
					wParam :	
						low word:	id of button.
						high word:	notification code
				*/
				//	타겟팅:
				int button_id = button.arg_menu_id.getValue();

				if(button_id == LOWORD(msg.wParam))
					if(HIWORD(msg.wParam) == 0)	//	Button은 통지코드가 0만 사용됨(클릭)
						return RESULT_SUCCESS | RESULT_TRUE;
			}
		}		

		return RESULT_SUCCESS | RESULT_FALSE;
	}

	NEObject NE_DLL &ButtonClickSpy::clone() const
	{
		return *(new ButtonClickSpy(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ButtonClickSpy::getHeader() const
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
			_header.setMaxErrorCodeCount(ButtonClickSpy::ERROR_CODE_END - 1);
			NETStringSet& argcomments = _header.getArgumentsComments();
			argcomments.create(1+5);
			argcomments.create(_KEY_NUMBER);
			argcomments.push("Target\n클릭을 감지할 버튼을 지정합니다.");
			argcomments.push("왼쪽 좌표(X)");
			argcomments.push("위 좌표(Y)");
			argcomments.push("윈도우의 너비(Width)");
			argcomments.push("윈도우의 높이(Height)");
			argcomments.push("윈도우가 어떻게 보여질 것인가 (보통 : 5)");
		}

		return _header;
	}

	LPCTSTR NE_DLL ButtonClickSpy::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}	

	Button& ButtonClickSpy::_castToButton(NEModule& module)
	{
		Button *null_pointer = NE_NULL;
		if( ! &module)
		{
			ALERT_ERROR(" : 널이 들어왔음")

			return *null_pointer;
		}

		static NEExportable::Identifier _identifier(_T("Button"), _T("haku"), 1);

		if(_identifier != module.getHeader())
		{
			ALERT_ERROR(" : 찾은 모듈이 윈도우 모듈이 아닙니다")

			return *null_pointer;
		}

		return static_cast<Button&>(module);;
	}

	type_result ButtonClickSpy::_onFetchArguments(NEArgumentList& tray)
	{
		tray.push(arg_button);

		return RESULT_SUCCESS;
	}
}