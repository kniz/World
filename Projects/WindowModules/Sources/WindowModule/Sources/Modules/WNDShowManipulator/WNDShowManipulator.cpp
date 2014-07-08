#include "WNDShowManipulator.hpp"
#include "../WND/WND.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL WNDShowManipulator::WNDShowManipulator()
		: NEModule()
	{
		
	}

	NE_DLL WNDShowManipulator::WNDShowManipulator(const WNDShowManipulator& source)
		: NEModule(source)
	{
		
	}

	NE_DLL WNDShowManipulator::~WNDShowManipulator()
	{
	
	}

	type_result NE_DLL WNDShowManipulator::execute()
	{	
		while(true)
		{	
			WND& wnd = static_cast<WND&>(arg_window_selector.getValue().getModule());
			if( ! &wnd)
				return RESULT_TYPE_ERROR;

			type_result result = wnd.changeShowCommand(arg_show_command.getValue());
			if(NEResult::hasError(result))
			{
				ALERT_ERROR(" : wnd.changeShowCommand에서 에러 발생");

				return result | RESULT_TYPE_ERROR | ERROR_HAPPEN_WHILE_CHANGING_COMMAND_SHOW_OF_WND;
			}
		}		

		return RESULT_SUCCESS | RESULT_TRUE;
	}

	NEObject NE_DLL &WNDShowManipulator::clone() const
	{
		return *(new WNDShowManipulator(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &WNDShowManipulator::getHeader() const
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
			_header.setMaxErrorCodeCount(WNDShowManipulator::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL WNDShowManipulator::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case ERROR_HAPPEN_WHILE_CHANGING_COMMAND_SHOW_OF_WND:
			return _T("WND 객체의 COMMAND SHOW를 바꾸는 동안 에러가 발생했다");

		default:
			return _T("알수 없는 에러");
		}
	}	

	type_result WNDShowManipulator::_onArgumentsFetched(NEArgumentInterfaceList& tray)
	{
		arg_show_command.getDefault().getValue() = _DEFAULT_SHOW_COMMAND;		
		tray.push(&arg_window_selector);
		return tray.push(&arg_show_command);
	}

}