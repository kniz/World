#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_short, false, type_short, NEType::NESHORT_SET>;
	typedef NEArrayTemplate<type_short, false, type_short, NEType::NESHORT_SET> NEShortSet;
}
