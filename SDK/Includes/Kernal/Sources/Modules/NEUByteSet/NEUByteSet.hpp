#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_ubyte, false, type_ubyte, NEType::NEUBYTE_SET>;
	typedef NEArrayTemplate<type_ubyte, false, type_ubyte, NEType::NEUBYTE_SET> NEUByteSet;
}
