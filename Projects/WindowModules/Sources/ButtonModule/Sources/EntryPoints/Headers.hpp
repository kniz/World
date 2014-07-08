#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/Button/Button.hpp"
#include "../Modules/ButtonClickSpy/ButtonClickSpy.hpp"

#ifndef ButtonPackage_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "ButtonPackage.dev.dbg.lib")
#			else
#				pragma comment(lib, "ButtonPackage.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "ButtonPackage.dev.lib")
#			else
#				pragma comment(lib, "ButtonPackage.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "ButtonPackage.lib")
#		else
#			pragma comment(lib, "ButtonPackage.mbcs.lib")
#		endif
#	endif
#endif
