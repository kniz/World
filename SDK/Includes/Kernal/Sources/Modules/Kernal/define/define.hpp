//	노드엔진 헤더:
#ifdef DEVELOPER
#	ifdef _DEBUG
//		식별자 헤더:
#		define _NAME										"Kernal.dev.dbg"
#		define _DEVELOPER									"haku"
#		define _REVISION									1
//		모듈 헤더:
#		define _DATE										"2011-07-11"
#		define _VERSION										"0.0.1a"
#		define _COMMENT										"NodeEngine Kernal. official web: http://www.haku.pe.kr"
#		define _DEPENDENCIES								""
#		define _VERSION_COMPATIBILITIES						""
//		세팅:
#		define _DEFAULT_TITLE								"NodeEngine"
#		define _DEFAULT_LOCALE_COMPATIBILITIES_COUNT		1
#		define _DEFAULT_LOCALE								"korean"
#		define _DEFAULT_EXECUTABLE_PLATFORMS_COUNT			1
#		define _DEFAULT_EXECUTABLE_PLATFORMS				"WINDOWS X86"
#		define _DEFAULT_INI_FORMS							""
#		define _DEFAULT_INI_FULLPATH						".\\Kernal.dev.dbg.ini" // INI 로드 API는 상대경로가 안된다. 절대경로를 입력하자.
#		define _DEFAULT_MODULE_DIRECTORY					"module.dev.dbg\\"
#		define _DEFAULT_LOG_DIRECTORY						"log.dev.dbg\\"
#		define _DEFAULT_LOG_EXTRACTOR						"log.dev.dbg"
#		define _DEFAULT_SCRIPT_DIRECTORY					"script.dev.dbg\\"
#		define _DEFAULT_SCRIPT_EXTRACTOR					"script.dev.dbg"
#		define _DEFAULT_NODE_DIRECTORY						"nodedata.dev.dbg\\"
#		define _DEFAULT_NODE_EXTRACTOR						"nodedata.dev.dbg"
#		define _DEFAULT_MAIN_SCRIPT_INDEX					0
#		define _DEFAULT_DEBUG_FLAG							15
#ifdef _UNICODE
#		define _DEFAULT_IS_KERNAL_USING_UNICODE				true
#else
#		define _DEFAULT_IS_KERNAL_USING_UNICODE				false
#endif
#		define _DEFAULT_LOAD_FROM_INI						true
#		define _DEFAULT_NODE_MANAGER_IDENTIFIER_NAME		"StandardNodeManager.dev.dbg"
#		define _DEFAULT_NODE_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_NODE_MANAGER_IDENTIFIER_REVISION	1
#		define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_NAME		"StandardScriptManager.dev.dbg"
#		define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_REVISION	1
//		INI 검색:
#		define _SCRIPT_DIRECTORY_INI_KEY					"script directory.dev.dbg"
#		define _NODE_DIRECTORY_INI_KEY						"node_directory.dev.dbg"
#		define _LOCALE_INI_KEY								"locale.dev.dbg"
#		define _LOG_DIRECTORY_INI_KEY						"log directory.dev.dbg"
#		define _MODULE_DIRECTORY_INI_KEY					"module directory.dev.dbg"
#		define _DEBUG_FLAG_INI_KEY							"debug flag.dev.dbg"
#	else
//		식별자 헤더:
#		define _NAME										"Kernal"
#		define _DEVELOPER									"haku"
#		define _REVISION									1
//		모듈 헤더:
#		define _DATE										"2011-07-11"
#		define _VERSION										"0.0.1a"
#		define _COMMENT										"NodeEngine Kernal. official web: http://www.haku.pe.kr"
#		define _DEPENDENCIES								""
#		define _VERSION_COMPATIBILITIES						""
//		세팅:
#		define _DEFAULT_TITLE								"NodeEngine"
#		define _DEFAULT_LOCALE_COMPATIBILITIES_COUNT		1
#		define _DEFAULT_LOCALE								"korean"
#		define _DEFAULT_EXECUTABLE_PLATFORMS_COUNT			1
#		define _DEFAULT_EXECUTABLE_PLATFORMS				"WINDOWS X86"
#		define _DEFAULT_INI_FORMS							""
#		define _DEFAULT_INI_FULLPATH						".\\Kernal.dev.ini" // INI 로드 API는 상대경로가 안된다. 절대경로를 입력하자.
#		define _DEFAULT_MODULE_DIRECTORY					"module.dev\\"
#		define _DEFAULT_LOG_DIRECTORY						"log.dev\\"
#		define _DEFAULT_LOG_EXTRACTOR						"log.dev"
#		define _DEFAULT_SCRIPT_DIRECTORY					"script.dev\\"
#		define _DEFAULT_SCRIPT_EXTRACTOR					"script.dev"
#		define _DEFAULT_NODE_DIRECTORY						"nodedata.dev\\"
#		define _DEFAULT_NODE_EXTRACTOR						"nodedata.dev"
#		define _DEFAULT_MAIN_SCRIPT_INDEX					0
#		define _DEFAULT_DEBUG_FLAG							15
#ifdef _UNICODE
#		define _DEFAULT_IS_KERNAL_USING_UNICODE				true
#else
#		define _DEFAULT_IS_KERNAL_USING_UNICODE				false
#endif
#		define _DEFAULT_LOAD_FROM_INI						true
#		define _DEFAULT_NODE_MANAGER_IDENTIFIER_NAME		"StandardNodeManager"
#		define _DEFAULT_NODE_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_NODE_MANAGER_IDENTIFIER_REVISION	1
#		define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_NAME		"StandardScriptManager"
#		define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_REVISION	1
//		INI 검색:
#		define _SCRIPT_DIRECTORY_INI_KEY					"script directory.dev"
#		define _NODE_DIRECTORY_INI_KEY						"node_directory.dev"
#		define _LOCALE_INI_KEY								"locale.dev"
#		define _LOG_DIRECTORY_INI_KEY						"log directory.dev"
#		define _MODULE_DIRECTORY_INI_KEY					"module directory.dev"
#		define _DEBUG_FLAG_INI_KEY							"debug flag.dev"
#	endif
#else
//	식별자 헤더:
#	define _NAME										"Kernal"
#	define _DEVELOPER									"haku"
#	define _REVISION									1
//	모듈 헤더:
#	define _DATE										"2011-07-11"
#	define _VERSION										"0.0.1a"
#	define _COMMENT										"NodeEngine Kernal. official web: http://www.haku.pe.kr"
#	define _DEPENDENCIES								""
#	define _VERSION_COMPATIBILITIES						""
//	세팅:
#	define _DEFAULT_TITLE								"NodeEngine"
#	define _DEFAULT_LOCALE_COMPATIBILITIES_COUNT		1
#	define _DEFAULT_LOCALE								"korean"
#	define _DEFAULT_EXECUTABLE_PLATFORMS_COUNT			1
#	define _DEFAULT_EXECUTABLE_PLATFORMS				"WINDOWS X86"
#	define _DEFAULT_INI_FORMS							""
#	define _DEFAULT_INI_FULLPATH						".\\Kernal.ini" // INI 로드 API는 상대경로가 안된다. 절대경로를 입력하자.
#	define _DEFAULT_MODULE_DIRECTORY					"module\\"
#	define _DEFAULT_LOG_DIRECTORY						"log\\"
#	define _DEFAULT_LOG_EXTRACTOR						"log"
#	define _DEFAULT_SCRIPT_DIRECTORY					"script\\"
#	define _DEFAULT_SCRIPT_EXTRACTOR					"script"
#	define _DEFAULT_NODE_DIRECTORY						"nodedata\\"
#	define _DEFAULT_NODE_EXTRACTOR						"nodedata"
#	define _DEFAULT_MAIN_SCRIPT_INDEX					0
#	define _DEFAULT_DEBUG_FLAG							15
#ifdef _UNICODE
#	define _DEFAULT_IS_KERNAL_USING_UNICODE				true
#else
#	define _DEFAULT_IS_KERNAL_USING_UNICODE				false
#endif
#	define _DEFAULT_LOAD_FROM_INI						true
#	define _DEFAULT_NODE_MANAGER_IDENTIFIER_NAME		"StandardNodeManager"
#	define _DEFAULT_NODE_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#	define _DEFAULT_NODE_MANAGER_IDENTIFIER_REVISION	1
#	define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_NAME		"StandardScriptManager"
#	define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#	define _DEFAULT_SCRIPT_MANAGER_IDENTIFIER_REVISION	1

//	INI 검색:
#	define _SCRIPT_DIRECTORY_INI_KEY					"script directory"
#	define _NODE_DIRECTORY_INI_KEY						"node_directory"
#	define _LOCALE_INI_KEY								"locale"
#	define _LOG_DIRECTORY_INI_KEY						"log directory"
#	define _MODULE_DIRECTORY_INI_KEY					"module directory"
#		define _DEBUG_FLAG_INI_KEY						"debug flag"
#endif
