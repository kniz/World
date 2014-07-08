#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/[!output module_name]/[!output module_name].hpp"

#ifndef [!output PROJECT_NAME]_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "[!output PROJECT_NAME].dev.dbg.lib")
#			else
#				pragma comment(lib, "[!output PROJECT_NAME].dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "[!output PROJECT_NAME].dev.lib")
#			else
#				pragma comment(lib, "[!output PROJECT_NAME].dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "[!output PROJECT_NAME].lib")
#		else
#			pragma comment(lib, "[!output PROJECT_NAME].mbcs.lib")
#		endif
#	endif
#endif
