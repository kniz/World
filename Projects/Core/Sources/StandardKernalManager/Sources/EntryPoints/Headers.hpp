#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/NEStandardNodeManager/NEStandardNodeManager.hpp"
#include "../Modules/NEStandardScriptManager/NEStandardScriptManager.hpp"

#ifndef StandardKernalManager_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "StandardKernalManager.dev.dbg.lib")
#			else
#				pragma comment(lib, "StandardKernalManager.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "StandardKernalManager.dev.lib")
#			else
#				pragma comment(lib, "StandardKernalManager.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "StandardKernalManager.lib")
#		else
#			pragma comment(lib, "StandardKernalManager.mbcs.lib")
#		endif
#	endif
#endif
