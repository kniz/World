#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_uint, false, type_uint, NEType::NEUINT_SET>;
	typedef NEArrayTemplate<type_uint, false, type_uint, NEType::NEUINT_SET> NEUIntSet;
}
