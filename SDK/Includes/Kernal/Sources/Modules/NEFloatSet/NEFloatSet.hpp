#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_float, false, type_float, NEType::NEFLOAT_SET>;
	typedef NEArrayTemplate<type_float, false, type_float, NEType::NEFLOAT_SET> NEFloatSet;
}
