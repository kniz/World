#pragma once

#include "../../../Macro/Sources/Modules/DLLMacro/SetDLLIMPORT.hpp"

#define CORES_BUILD_MODE
#include "../../../Editor/Sources/EntryPoints/Headers.hpp"
#undef CORES_BUILD_MODE

#ifdef StandardEditorManager_EXPORTS
#	include "../../../Macro/Sources/Modules/DLLMacro/SetDLLEXPORT.hpp"
#endif
