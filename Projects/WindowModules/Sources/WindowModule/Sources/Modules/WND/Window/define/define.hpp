#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME						"Window"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						""
#		define	_DATE						"2012-04-16"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					1

#		define _DEFAULT_WINDOW_STYLE		WS_OVERLAPPEDWINDOW | WS_VISIBLE
#		define _DEFAULT_WINDOW_TITLE		"Default Window"
#		define _DEFAULT_WINDOW_CLASS_NAME	"Window Class Of WindowModule"
#	else
#		define _NAME						"Window"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						""
#		define	_DATE						"2012-04-16"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					1

#		define _DEFAULT_WINDOW_STYLE		WS_OVERLAPPEDWINDOW | WS_VISIBLE
#		define _DEFAULT_WINDOW_TITLE		"Default Window"
#		define _DEFAULT_WINDOW_CLASS_NAME	"Window Class Of WindowModule"
#	endif
#else
#	define _NAME							"Window"
#	define _DEVELOPER						"haku"
#	define _REVISION						1 // 커널에서 판별하는 버전표기
#	define _VERSION							"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#	define _COMMENT							""
#	define	_DATE							"2012-04-16"
#	define _DEPENDENCIES_COUNT				0
#	define _KEY_NUMBER						1

#	define _DEFAULT_WINDOW_STYLE			WS_OVERLAPPEDWINDOW | WS_VISIBLE
#	define _DEFAULT_WINDOW_TITLE			"Default Window"
#	define _DEFAULT_WINDOW_CLASS_NAME		"Window Class Of WindowModule"
#endif

