#pragma once

#include "../Modules/Editor/Editor.hpp"
#include "../Modules/NEDialog/NEDialog.hpp"
#include "../Modules/NETextComponent/NETextComponent.hpp"
#include "../Modules/NECheckListComponent/NECheckListComponent.hpp"
#include "../Modules/NEModifiableListComponent/NEModifiableListComponent.hpp"
#include "../Modules/NESwitchComponent/NESwitchComponent.hpp"
#include "../Modules/NEButtonComponent/NEButtonComponent.hpp"

#ifndef EDITOR_EXPORTS
#	ifdef CORES_BUILD_MODE
#		ifdef DEVELOPER
#			ifdef _DEBUG
#				ifdef _UNICODE
#					pragma comment(lib, "../../../Binaries/Core/Editor.dev.dbg.lib")
#				else
#					pragma comment(lib, "../../../Binaries/Core/Editor.dev.dbg.mbcs.lib")
#				endif
#			else
#				ifdef _UNICODE
#					pragma comment(lib, "../../../Binaries/Core/Editor.dev.lib")
#				else
#					pragma comment(lib, "../../../Binaries/Core/Editor.dev.mbcs.lib")
#				endif
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "../../../Binaries/Core/Editor.lib")
#			else
#				pragma comment(lib, "../../../Binaries/Core/Editor.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef DEVELOPER
#			ifdef _DEBUG
#				ifdef _UNICODE
#					pragma comment(lib, "Editor.dev.dbg.lib")
#				else
#					pragma comment(lib, "Editor.dev.dbg.mbcs.lib")
#				endif
#			else
#				ifdef _UNICODE
#					pragma comment(lib, "Editor.dev.lib")
#				else
#					pragma comment(lib, "Editor.dev.mbcs.lib")
#				endif
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "Editor.lib")
#			else
#				pragma comment(lib, "Editor.mbcs.lib")
#			endif
#		endif
#	endif
#endif
