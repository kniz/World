#ifdef DEVELOPER
#	ifdef _DEBUG
//		식별자 헤더:
#		define _NAME										"Editor.dev.dbg"
#		define _DEVELOPER									"haku"
#		define _REVISION									1
//		모듈 헤더:
#		define _DATE										"2011-08-09"
#		define _VERSION										"0.0.1a"
#		define _COMMENT										"에디터 패키지를 관리한다."
#		define _DEPENDENCIES								"Kernal"
//		식별자:
#		define _DEFAULT_PANEL_MANAGER_IDENTIFIER_NAME		"PanelManager.dev.dbg"
#		define _DEFAULT_PANEL_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_PANEL_MANAGER_IDENTIFIER_REVISION	1
#		define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_NAME		"ScriptEditor.dev.dbg"
#		define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_REVISION	1
#		define _DEFAULT_EVENT_HANDLER_IDENTIFIER_NAME		"EventHandler.dev.dbg"
#		define _DEFAULT_EVENT_HANDLER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_EVENT_HANDLER_IDENTIFIER_REVISION	1
//		세팅:
#		define _PANEL_DIRECTORY_KEY							"panel directory.dev.dbg"
#	else
//		식별자 헤더:
#		define _NAME										"Editor"
#		define _DEVELOPER									"haku"
#		define _REVISION									1
//		모듈 헤더:
#		define _DATE										"2011-08-09"
#		define _VERSION										"0.0.1a"
#		define _COMMENT										"에디터 패키지를 관리한다."
#		define _DEPENDENCIES								"Kernal"
//		식별자:
#		define _DEFAULT_PANEL_MANAGER_IDENTIFIER_NAME		"PanelManager"
#		define _DEFAULT_PANEL_MANAGER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_PANEL_MANAGER_IDENTIFIER_REVISION	1
#		define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_NAME		"ScriptEditor"
#		define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_REVISION	1
#		define _DEFAULT_EVENT_HANDLER_IDENTIFIER_NAME		"EventHandler"
#		define _DEFAULT_EVENT_HANDLER_IDENTIFIER_DEVELOPER	_DEVELOPER
#		define _DEFAULT_EVENT_HANDLER_IDENTIFIER_REVISION	1
//		세팅:
#		define _PANEL_DIRECTORY_KEY							"panel directory.dev"
#	endif
#else
//	식별자 헤더:
#	define _NAME											"Editor"
#	define _DEVELOPER										"haku"
#	define _REVISION										1
//	모듈 헤더:
#	define _DATE											"2011-08-09"
#	define _VERSION											"0.0.1a"
#	define _COMMENT											"에디터 패키지를 관리한다."
#	define _DEPENDENCIES									"Kernal"
//	식별자:
#	define _DEFAULT_PANEL_MANAGER_IDENTIFIER_NAME			"PanelManager"
#	define _DEFAULT_PANEL_MANAGER_IDENTIFIER_DEVELOPER		_DEVELOPER
#	define _DEFAULT_PANEL_MANAGER_IDENTIFIER_REVISION		1
#	define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_NAME			"ScriptEditor"
#	define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_DEVELOPER		_DEVELOPER
#	define _DEFAULT_SCRIPT_EDITOR_IDENTIFIER_REVISION		1
#	define _DEFAULT_EVENT_HANDLER_IDENTIFIER_NAME			"EventHandler"
#	define _DEFAULT_EVENT_HANDLER_IDENTIFIER_DEVELOPER		_DEVELOPER
#	define _DEFAULT_EVENT_HANDLER_IDENTIFIER_REVISION		1
//	세팅:
#	define _PANEL_DIRECTORY_KEY								"panel directory"
#endif
