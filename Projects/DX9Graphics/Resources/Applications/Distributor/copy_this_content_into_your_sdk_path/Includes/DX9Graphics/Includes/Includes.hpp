#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment (lib, "dxguid.lib")
#ifdef	_DEBUG
#	include <crtdbg.h>
#	pragma comment (lib, "d3dx9d.lib")
#else
#	pragma comment (lib, "d3dx9.lib")
#endif

#include <Macro/Sources/Modules/DLLMacro/SetDLLIMPORT.hpp>
#include "../../../../WindowModules/Sources/WindowModule/Sources/EntryPoints/Headers.hpp"
#ifdef DX9GRAPHICS_EXPORTS
#	include <Macro/Sources/Modules/DLLMacro/SetDLLEXPORT.hpp>
#endif
using namespace NE;