#pragma once

#include "../Modules/NodeVisualizer/NodeVisualizer.hpp"
#include "../Modules/WorldVisualizer/WorldVisualizer.hpp"
#include "../Modules/NodeBinder/NodeBinder.hpp"
#include "../Modules/PanelBinder/PanelBinder.hpp"
#include "../Modules/KeyBinder/KeyBinder.hpp"

#ifndef METAWORLD_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "MetaWorld.dev.dbg.lib")
#			else
#				pragma comment(lib, "MetaWorld.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "MetaWorld.dev.lib")
#			else
#				pragma comment(lib, "MetaWorld.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "MetaWorld.lib")
#		else
#			pragma comment(lib, "MetaWorld.mbcs.lib")
#		endif
#	endif
#endif
