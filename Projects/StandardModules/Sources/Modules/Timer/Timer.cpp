#include "Timer.hpp"
#include "define/define.hpp"
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

namespace NE
{
	type_int Timer::_count_of_instance = 0;

	NE_DLL Timer::Timer()
		: NEModule()
	{
		_time_evaluated_before = 0;
		
		_count_of_instance++;
		if(_count_of_instance == 1)
			timeBeginPeriod(1);

		initialize();
	}

	NE_DLL Timer::Timer(const Timer& source)
		: NEModule(source)
	{
		_time_evaluated_before = source._time_evaluated_before;

		_count_of_instance++;
		if(_count_of_instance == 1)
			timeBeginPeriod(1);
	}

	NE_DLL Timer::~Timer()
	{
		_count_of_instance--;
		if( ! _count_of_instance)
			timeEndPeriod(1);
	}
	
	type_result NE_DLL Timer::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NEUIntKey());
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL Timer::execute()
	{
		type_uint term = (static_cast<NEUIntKey&>( getKeySet()[0] )).getValue();
		if( ! _time_evaluated_before)
			_time_evaluated_before = timeGetTime();



		//	main:
		type_uint time_new_evaluated = timeGetTime();
		if(term > time_new_evaluated - _time_evaluated_before)
		{
			_time_evaluated_before += term;
			return RESULT_SUCCESS | RESULT_TRUE;
		}
		
		

		return RESULT_SUCCESS | RESULT_FALSE;
	}

	NEObject NE_DLL &Timer::clone() const
	{
		return *(new Timer(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &Timer::getHeader() const
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
			_header.setMaxErrorCodeCount(Timer::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL Timer::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}
}
