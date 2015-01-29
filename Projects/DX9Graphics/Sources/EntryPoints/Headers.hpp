#pragma once

#include "../Commons/EntryPointName.hpp"
#include "../Modules/DX9/DX9.hpp"
#include "../Modules/PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Modules/BufferClearer/BufferClearer.hpp"
#include "../Modules/Sprite/Sprite.hpp"
#include "../Modules/SpriteTexter/SpriteTexter.hpp"
#include "../Modules/FixedProgram/FixedProgram.hpp"
#include "../Modules/TabledTexture/TabledTexture.hpp"
#include "../Modules/AnimatedModel/AnimatedModel.hpp"
#include "../Modules/BloomProgram/BloomProgram.hpp"
#include "../Modules/BlurProgram/BlurProgram.hpp"
#include "../Modules/Picker/Picker.hpp"
#include "../Modules/SpriteTexter/SpriteTexter.hpp"
#include "../Modules/DXFont/DXFont.hpp"

#ifndef DX9GRAPHICS_EXPORTS
#	ifdef DEVELOPER
#		ifdef _DEBUG
#			ifdef _UNICODE
#				pragma comment(lib, "DX9Graphics.dev.dbg.lib")
#			else
#				pragma comment(lib, "DX9Graphics.dev.dbg.mbcs.lib")
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "DX9Graphics.dev.lib")
#			else
#				pragma comment(lib, "DX9Graphics.dev.mbcs.lib")
#			endif
#		endif
#	else
#		ifdef _UNICODE
#			pragma comment(lib, "DX9Graphics.lib")
#		else
#			pragma comment(lib, "DX9Graphics.mbcs.lib")
#		endif
#	endif
#endif
