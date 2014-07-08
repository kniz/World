#include "Button.hpp"
#include "../define/define.hpp"

namespace NE
{
	NE_DLL Button::Button()
		: WND()
	{
		
	}

	NE_DLL Button::Button(const Button& source)
		: WND(source)
	{
		_connector.connect(getKeySet());
	}

	NE_DLL Button::~Button()
	{

	}
	
	Button::ButtonConnector NE_DLL &Button::getConnector()
	{
		return _connector;
	}
	
	const Button::ButtonConnector NE_DLL &Button::getConnector() const
	{
		return _connector;
	}

	type_result NE_DLL Button::initialize()
	{
		WND::initialize();

		getKeySet().resize(getKeySet().getLength() + 3);
		getKeySet().push(NEModuleSelector());
		getKeySet().push(NETStringKey(_T(_DEFAULT_CAPTION)));
		getKeySet().push(NEIntKey(0));

		_connector.connect(getKeySet());

		return RESULT_SUCCESS;
	}

	type_result NE_DLL Button::execute()
	{
		//	pre:
		if(_hwnd) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		NEModuleSelector& sel = _connector.getWindowSelector();
		if( ! sel.getBinder().isBinded()	&&
			&sel.getModule()				)
		{
			sel.bind();
			sel.initializeReferingPoint();
		}


		//	main:
		WND& module = static_cast<WND&>(sel.getModule());
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

		_hwnd = CreateWindow(_T("BUTTON"), _connector.getCaption().getValue().toCharPointer(), WS_VISIBLE | WS_CHILD | WS_TABSTOP,
					_connector.getX().getValue(), _connector.getY().getValue(), _connector.getWidth().getValue(), _connector.getHeight().getValue(),			
					_parent_hwnd, (HMENU)_connector.getMenuId().getValue(),	NULL, NULL);
		if( ! _hwnd)
			return RESULT_TYPE_ERROR;



		//	post:
		return RESULT_SUCCESS;
	}
}
