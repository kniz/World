#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_double, false, type_double, NEType::NEDOUBLE_SET>;
	typedef NEArrayTemplate<type_double, false, type_double, NEType::NEDOUBLE_SET> NEDoubleSet;
}
