#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME									"INIManager"
#		define _AUTHOR									"haku"
#		define _REVISION								1
#		define _VERSION									"0.0.1a"
#		define _COMMENT									"표준 INI 매니져 클래스."
#		define	_DATE									"2012-01-01"
#		define _DEPENDENCIES_COUNT						0
#		define _KEY_NUMBER								0
#		define _DEFAULT_TCHAR_BUFFER_SIZE				512
#		define _DEFAULT_INI_MODULE_CATEGORY_EXTRACTOR	identifier.getName() + _T(" - ") + identifier.getDeveloper() + _T(" - ") + identifier.getRevision()
#	else
#		define _NAME									"INIManager"
#		define _AUTHOR									"haku"
#		define _REVISION								1
#		define _VERSION									"0.0.1a"
#		define _COMMENT									"표준 INI 매니져 클래스."
#		define	_DATE									"2012-01-01"
#		define _DEPENDENCIES_COUNT						0
#		define _KEY_NUMBER								0
#		define _DEFAULT_TCHAR_BUFFER_SIZE				512
#		define _DEFAULT_INI_MODULE_CATEGORY_EXTRACTOR	identifier.getName() + _T(" - ") + identifier.getDeveloper() + _T(" - ") + identifier.getRevision()
#	endif
#else
#	define _NAME										"INIManager"
#	define _AUTHOR										"haku"
#	define _REVISION									1
#	define _VERSION										"0.0.1a"
#	define _COMMENT										"표준 INI 매니져 클래스."
#	define	_DATE										"2012-01-01"
#	define _DEPENDENCIES_COUNT							0
#	define _KEY_NUMBER									0
#	define _DEFAULT_TCHAR_BUFFER_SIZE					512
#	define _DEFAULT_INI_MODULE_CATEGORY_EXTRACTOR		identifier.getName() + _T(" - ") + identifier.getDeveloper() + _T(" - ") + identifier.getRevision()
#endif
