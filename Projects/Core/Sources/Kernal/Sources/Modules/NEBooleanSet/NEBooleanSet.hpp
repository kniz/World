#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_bool, false, type_bool, NEType::NEBOOLEAN_SET>;
	typedef NEArrayTemplate<type_bool, false, type_bool, NEType::NEBOOLEAN_SET> NEBooleanSet;
}
