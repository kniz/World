#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/WND/Window/Window.hpp"
#include "../Modules/WNDSpy/MouseSpy/MouseSpy.hpp"
#include "../Modules/WNDShowManipulator/WNDShowManipulator.hpp"
#include "../Modules/WNDDomainManipulator/WNDDomainManipulator.hpp"
#include "../Modules/CharInputSpy/CharInputSpy.hpp"

#ifndef Window_Module_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "WindowModule.dev.dbg.lib")
#			else
#				pragma comment(lib, "WindowModule.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "WindowModule.dev.lib")
#			else
#				pragma comment(lib, "WindowModule.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "WindowModule.lib")
#		else
#			pragma comment(lib, "WindowModule.mbcs.lib")
#		endif
#	endif
#endif
