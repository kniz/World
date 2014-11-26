#include "MouseSpy.hpp"
#include "define/define.hpp"
#include <MMSystem.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "winmm.lib")

namespace NE
{
	type_result NE_DLL MouseSpy::_onExecute()
	{	
		bool is_observed = false;
		while(true)
		{
			NEModule& module = arg_window_selector.getValue().getModule();
			if( ! &module)
				break;
			Window& window = _castToWindow(module);
			if( ! &window)
				continue;

			const MSG& msg = window.getMSG();
			if(msg.message == arg_notification_type.getValue())
			{
				is_observed = true;
				/*	
					상위비트: Y
					하위비트: X
				*/
				arg_out_cursor_x.getValue() = LOWORD(msg.lParam);
				arg_out_cursor_y.getValue() = HIWORD(msg.lParam);

				cout	<< "x : "	<< arg_out_cursor_x.getValue() 
						<< ", y : " << arg_out_cursor_y.getValue() << endl;
			}			
		}

		if(is_observed)
			return RESULT_SUCCESS | RESULT_TRUE;

		return RESULT_SUCCESS | RESULT_FALSE;
	}

	NEObject NE_DLL &MouseSpy::clone() const
	{
		return *(new MouseSpy(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &MouseSpy::getHeader() const
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
			_header.setMaxErrorCodeCount(MouseSpy::ERROR_CODE_END - 1);
			NETStringSet& args = _header.getArgumentsComments();
			args.create(4);
			args.push("마우스 커서 위치를 조사할 윈도우(Window) 모듈");
			args.push("마우스의 어떤 행동을 알아낼것인지 정한다.\n512: MOUSEMOVE, \
					  513:LBUTTON_DOWN, 514:LBUTTON_UP, 515:LBUTTON_DBLCLK, 516:RBUTTON_DOWN, \
					  517:RBUTTON_UP, 518:RBUTTON_DBLCLK");
			args.push("[OUT] 마우스의 X 위치를 이곳에 저장한다.");
			args.push("[OUT] 마우스의 Y 위치를 이곳에 저장한다.");
		}

		return _header;
	}

	LPCTSTR NE_DLL MouseSpy::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}	

	type_result MouseSpy::_onFetchArguments(NEArgumentInterfaceList& tray)
	{
		arg_notification_type.getDefault() = WM_MOUSEMOVE;
		tray.push(&arg_window_selector);
		tray.push(&arg_notification_type);
		tray.push(&arg_out_cursor_x);
		return tray.push(&arg_out_cursor_y);		
	}
}