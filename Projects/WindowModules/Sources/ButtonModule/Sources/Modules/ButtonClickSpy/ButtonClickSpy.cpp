#include "ButtonClickSpy.hpp"
#include "../Button/Button.hpp"
#include "define/define.hpp"
#include <iostream>
using namespace std;

namespace NE
{
	NE_DLL ButtonClickSpy::ButtonClickSpy()
		: WNDSpy()
	{
		
	}

	NE_DLL ButtonClickSpy::ButtonClickSpy(const ButtonClickSpy& source)
		: WNDSpy(source)
	{
		
	}

	NE_DLL ButtonClickSpy::~ButtonClickSpy()
	{
	
	}

	type_result NE_DLL ButtonClickSpy::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NEModuleSelector() ); // Window 모듈
		getKeySet().push( NEModuleSelector() ); // Button 모듈
		getKeySet().push( NEIntKey(BN_CLICKED) ); // 메세지의 종류: LButton과 관계된 메세지만 받기로 한다		

		return RESULT_SUCCESS;
	}

	type_result NE_DLL ButtonClickSpy::execute()
	{	
		//	pre:
		NEModuleSelector&	window_selector = static_cast<NEModuleSelector&>(getKeySet()[0]),
						&	button_selector = static_cast<NEModuleSelector&>(getKeySet()[1]);

		window_selector.initialize();
		button_selector.initialize();
		NEModule& module = window_selector.getModule();
		NEModule& module2 = button_selector.getModule();
		if( ! &module	||	! &module2)
			return RESULT_SUCCESS | RESULT_FALSE;
		Window& window = _castToWindow(module);
		Button& button = _castToButton(module2);
		if( ! &window || ! &button)
		{
			ALERT_ERROR(" : 모듈셀렉터로부터 버튼이나 윈도우가 아닌 모듈이 나왔음")

			return RESULT_TYPE_ERROR;
		}



		//	main:
		const MSG& msg = window.getMSG();
		
		if(msg.message == WM_COMMAND)
		{	/*	
				wParam :	
					low word:	id of button.
					high word:	notification code
			*/
			//	타겟팅:
			int button_id = button.getConnector().getMenuId().getValue();

			if(button_id == LOWORD(msg.wParam))
			{
				int notification_message = HIWORD(msg.wParam);
				int my_notification_message = (static_cast<NEIntKey&>(getKeySet()[2])).getValue();

				if(notification_message == my_notification_message)
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
}