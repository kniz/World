#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_byte, false, type_byte, NEType::NEBYTE_SET>;
	typedef NEArrayTemplate<type_byte, false, type_byte, NEType::NEBYTE_SET> NEByteSet;
}
