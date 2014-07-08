#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/ListBox/ListBox.hpp"
#include "../Modules/ListContentInserter/ListContentInserter.hpp"
#include "../Modules/ListContentRemover/ListContentRemover.hpp"

#ifndef ListModule_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "ListModule.dev.dbg.lib")
#			else
#				pragma comment(lib, "ListModule.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "ListModule.dev.lib")
#			else
#				pragma comment(lib, "ListModule.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "ListModule.lib")
#		else
#			pragma comment(lib, "ListModule.mbcs.lib")
#		endif
#	endif
#endif
