#pragma once

#ifdef DEVELOPER
#	undef ALERT_ERROR
#	undef ALERT_WARNING
#	undef ALERT_INFORMATION
#	undef ALERT_ERROR_IN_SPECIFIED_MODULE
#	undef ALERT_WARNING_IN_SPECIFIED_MODULE
#	undef ALERT_INFORMATION_IN_SPECIFIED_MODULE
#	define	EDITOR_ERROR(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(Kernal::getInstance().getHeader(), NEResult::LEVEL_ERROR, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tError")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	EDITOR_WARNING(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(Kernal::getInstance().getHeader(), NEResult::LEVEL_WARNING, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tWarning")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	EDITOR_INFORMATION(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(Kernal::getInstance().getHeader(), NEResult::LEVEL_INFORMATION, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tInformation")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_ERROR(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(getHeader(), NEResult::LEVEL_ERROR, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tError")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_WARNING(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(getHeader(), NEResult::LEVEL_WARNING, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tWarning")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_INFORMATION(printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert(getHeader(), NEResult::LEVEL_INFORMATION, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tInformation")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
	
#	define	ALERT_ERROR_IN_SPECIFIED_MODULE(identifier, printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert((identifier), NEResult::LEVEL_ERROR, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\nEditor")## \
	_T("\ntype :\t\tError")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);

#	define	ALERT_WARNING_IN_SPECIFIED_MODULE(identifier, printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert((identifier), NEResult::LEVEL_WARNING, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tWarning")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);

#	define	ALERT_INFORMATION_IN_SPECIFIED_MODULE(identifier, printf_string, ...)	\
	Kernal::getInstance().getDebugManager().alert((identifier), NEResult::LEVEL_INFORMATION, \
	_T("\n-----------------------------------------------------------")## \
	_T("\n")##_T(printf_string)## \
	_T("\n-----------------------------------------------------------")## \
	_T("\ndomain :\tEditor")## \
	_T("\ntype :\t\tInformation")## \
	_T("\nfunction :\t")##_T(__FUNCSIG__)## \
	_T("\nline :\t\t%d ")## \
	_T("\n")##_T(__FILE__)##_T("(%d)")## \
	_T("\n-----------------------------------------------------------\n"), \
	__VA_ARGS__, __LINE__, __LINE__);
#else
#	define EDITOR_ERROR(...)			;
#	define EDITOR_WARNING(...)			;
#	define EDITOR_INFORMATION(...)		;
#endif
