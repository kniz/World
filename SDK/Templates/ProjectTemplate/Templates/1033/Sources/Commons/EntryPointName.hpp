#pragma once

#ifdef DEVELOPER
#	ifdef _DEBUG
[!if export_execute_module]
#		define	_EXECUTE_ENTRYPOINT	registerModuleDevDbg()
[!endif]
[!if export_panel]
#		define	_PANEL_ENTRYPOINT	registerPanelDevDbg()
[!endif]
#	else
[!if export_execute_module]
#		define	_EXECUTE_ENTRYPOINT	registerModuleDev()
[!endif]
[!if export_panel]
#		define	_PANEL_ENTRYPOINT	registerPanelDev()
[!endif]
#	endif
#else
[!if export_execute_module]
#	define	_EXECUTE_ENTRYPOINT		registerModule()
[!endif]
[!if export_panel]
#	define	_PANEL_ENTRYPOINT		registerPanel()
[!endif]
#endif
