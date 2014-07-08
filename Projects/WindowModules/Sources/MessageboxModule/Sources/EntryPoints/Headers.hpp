#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/MessageBox/MessageBox.hpp"

#ifndef MessagePackage_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "MessagePackage.dev.dbg.lib")
#			else
#				pragma comment(lib, "MessagePackage.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "MessagePackage.dev.lib")
#			else
#				pragma comment(lib, "MessagePackage.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "MessagePackage.lib")
#		else
#			pragma comment(lib, "MessagePackage.mbcs.lib")
#		endif
#	endif
#endif
