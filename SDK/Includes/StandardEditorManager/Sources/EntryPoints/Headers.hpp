#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/NEStandardPanelManager/NEStandardPanelManager.hpp"
#include "../Modules/NEStandardScriptEditor/NEStandardScriptEditor.hpp"

#ifndef StandardEditorManager_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "StandardEditorManager.dev.dbg.lib")
#			else
#				pragma comment(lib, "StandardEditorManager.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "StandardEditorManager.dev.lib")
#			else
#				pragma comment(lib, "StandardEditorManager.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "StandardEditorManager.lib")
#		else
#			pragma comment(lib, "StandardEditorManager.mbcs.lib")
#		endif
#	endif
#endif
