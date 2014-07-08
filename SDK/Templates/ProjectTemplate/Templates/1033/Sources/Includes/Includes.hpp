#pragma once

#include <Macro/Sources/Modules/DLLMacro/SetDLLIMPORT.hpp>

[!if include_editor]
#include <Editor/Sources/EntryPoints/Headers.hpp>
[!else]
#include <Kernal/Sources/EntryPoints/Headers.hpp>
[!endif]

#ifdef [!output PROJECT_NAME]_EXPORTS
#	include <Macro/Sources/Modules/DLLMacro/SetDLLEXPORT.hpp>
#endif