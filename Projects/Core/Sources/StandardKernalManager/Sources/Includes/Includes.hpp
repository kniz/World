#pragma once

#include "../../../Macro/Sources/Modules/DLLMacro/SetDLLIMPORT.hpp"

#define CORES_BUILD_MODE
#include "../../../Kernal/Sources/EntryPoints/Headers.hpp"
#undef CORES_BUILD_MODE

#ifdef StandardKernalManager_EXPORTS
#	include "../../../Macro/Sources/Modules/DLLMacro/SetDLLEXPORT.hpp"
#endif
