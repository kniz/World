#ifdef DEVELOPER
#	ifdef _DEBUG
//	모듈 헤더:
#		define _NAME								"DebugManager"
#		define _REVISION							1
#		define _DATE								"2012-01-01"
#		define _VERSION								"0.0.1a"
#		define _COMMENT								"표준 디버그 매니져 클래스."
#		define _DEPENDENCIES						""
#		define _DEVELOPER							"haku"
//	디버그 문자열:	printf 타입 문자열
#		define _LOG_FILE_FORMAT						"%Y-%m-%d" // use _tcsftime printf-type string.
#		define _FILE_BUFFER_SIZE					24
#		define _DATE_BUFFER_SIZE					20
#		define _TIME_BUFFER_SIZE					20
#		define _DEFAULT_TCHAR_FINAL_BUFFER_SIZE		2048
#		define _DEFAULT_CONSOLE_WINDOW_BOOT_MESSAGE	"> Kernal Debug Console\n\tkernal : 0.0.1a\n\tDomain : Developer.Debug"
//	INI:
#		define _MODULE_FLAG_EXTRACTOR				"debug flag"
#		define _DEBUGMODE_EXTRACTOR					"on debug manager"
#		define _ERRORENABLE_EXTRACTOR				"error enable"
#		define _WARNINGENABLE_EXTRACTOR				"warning enable"
#		define _INFORMATIONENABLE_EXTRACTOR			"information enable"
#		define _OPENCONSOLE_EXTRACTOR				"open console"
#		define _OPENLOG_EXTRACTOR					"write log"
#		define _OPENMESSAGEBOX_EXTRACTOR			"show messagebox"
#		define _OPENDEBUGWINDOW_EXTRACTOR			"print into debugwindow"
//	Flag:
#		define _NOTHING								0x00
#		define _LOG									0x01
#		define _CONSOLE								0x02
#		define _MESSAGEBOX							0x04
#		define _DEBUGWINDOW							0x08
//	DebugManager Flags:
#		define _DEFAULT_ENABLE_ERROR				true
#		define _DEFAULT_ENABLE_WARNING				true
#		define _DEFAULT_ENABLE_INFORMATION			true
#		define _DEFAULT_OPEN_CONSOLE				true
#		define _DEFAULT_OPEN_LOG					true
#		define _DEFAULT_OPEN_MESSAGEBOX				false
#		define _DEFAULT_OPEN_DEBUGWINDOW			true
#		define _DEFAULT_DEBUG_MODE					true
#		define _DEFAULT_MODULE_FLAG					_LOG | _CONSOLE | _MESSAGEBOX | _DEBUGWINDOW
#	else
//	모듈 헤더:
#		define _NAME								"DebugManager"
#		define _REVISION							1
#		define _DATE								"2012-01-01"
#		define _VERSION								"0.0.1a"
#		define _COMMENT								"표준 디버그 매니져 클래스."
#		define _DEPENDENCIES						""
#		define _DEVELOPER							"haku"
//	디버그 문자열:	printf 타입 문자열
#		define _LOG_FILE_FORMAT						"%Y-%m-%d" // use _tcsftime printf-type string.
#		define _FILE_BUFFER_SIZE					24
#		define _DATE_BUFFER_SIZE					20
#		define _TIME_BUFFER_SIZE					20
#		define _DEFAULT_TCHAR_FINAL_BUFFER_SIZE		2048
#		define _DEFAULT_CONSOLE_WINDOW_BOOT_MESSAGE	"> Kernal Debug Console\n\tkernal : 0.0.1a\n\tDomain : Developer"
//	INI:
#		define _MODULE_FLAG_EXTRACTOR				"debug flag"
#		define _DEBUGMODE_EXTRACTOR					"on debug manager"
#		define _ERRORENABLE_EXTRACTOR				"error enable"
#		define _WARNINGENABLE_EXTRACTOR				"warning enable"
#		define _INFORMATIONENABLE_EXTRACTOR			"information enable"
#		define _OPENCONSOLE_EXTRACTOR				"open console"
#		define _OPENLOG_EXTRACTOR					"write log"
#		define _OPENMESSAGEBOX_EXTRACTOR			"show messagebox"
#		define _OPENDEBUGWINDOW_EXTRACTOR			"print into debugwindow"
//	Flag:
#		define _NOTHING								0x00
#		define _LOG									0x01
#		define _CONSOLE								0x02
#		define _MESSAGEBOX							0x04
#		define _DEBUGWINDOW							0x08
//	DebugManager Flags:
#		define _DEFAULT_ENABLE_ERROR				true
#		define _DEFAULT_ENABLE_WARNING				true
#		define _DEFAULT_ENABLE_INFORMATION			true
#		define _DEFAULT_OPEN_CONSOLE				true
#		define _DEFAULT_OPEN_LOG					true
#		define _DEFAULT_OPEN_MESSAGEBOX				false
#		define _DEFAULT_OPEN_DEBUGWINDOW			true
#		define _DEFAULT_DEBUG_MODE					true
#		define _DEFAULT_MODULE_FLAG					_LOG | _CONSOLE | _MESSAGEBOX | _DEBUGWINDOW
#	endif
#else
#		define _NAME								"DebugManager"
#		define _REVISION							1
#		define _DATE								"2012-01-01"
#		define _VERSION								"0.0.1a"
#		define _COMMENT								"표준 디버그 매니져 클래스."
#		define _DEPENDENCIES						""
#		define _DEVELOPER							"haku"
//	디버그 문자열:	printf 타입 문자열
#	define _LOG_FILE_FORMAT							"%Y-%m-%d" // use _tcsftime printf-type string.
#	define _FILE_BUFFER_SIZE						24
#	define _DATE_BUFFER_SIZE						20
#	define _TIME_BUFFER_SIZE						20
#	define _DEFAULT_TCHAR_FINAL_BUFFER_SIZE			2048
#	define _DEFAULT_CONSOLE_WINDOW_BOOT_MESSAGE	
//	INI:
#	define _MODULE_FLAG_EXTRACTOR					"debug flag"
#	define _DEBUGMODE_EXTRACTOR						"on debug manager"
#	define _ERRORENABLE_EXTRACTOR					"error enable"
#	define _WARNINGENABLE_EXTRACTOR					"warning enable"
#	define _INFORMATIONENABLE_EXTRACTOR				"information enable"
#	define _OPENCONSOLE_EXTRACTOR					"open console"
#	define _OPENLOG_EXTRACTOR						"write log"
#	define _OPENMESSAGEBOX_EXTRACTOR				"show messagebox"
#	define _OPENDEBUGWINDOW_EXTRACTOR				"print into debugwindow"
//	Flag:
#		define _NOTHING								0x00
#		define _LOG									0x01
#		define _CONSOLE								0x02
#		define _MESSAGEBOX							0x04
#		define _DEBUGWINDOW							0x08
//	DebugManager Flags:
#		define _DEFAULT_ENABLE_ERROR				false
#		define _DEFAULT_ENABLE_WARNING				false
#		define _DEFAULT_ENABLE_INFORMATION			false
#		define _DEFAULT_OPEN_CONSOLE				false
#		define _DEFAULT_OPEN_LOG					false
#		define _DEFAULT_OPEN_MESSAGEBOX				false
#		define _DEFAULT_OPEN_DEBUGWINDOW			false
#		define _DEFAULT_DEBUG_MODE					false
#		define _DEFAULT_MODULE_FLAG					_NOTHING
#endif
