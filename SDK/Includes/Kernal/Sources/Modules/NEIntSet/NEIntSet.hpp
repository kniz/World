#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_int, false, type_int, NEType::NEINT_SET>;
	typedef NEArrayTemplate<type_int, false, type_int, NEType::NEINT_SET> NEIntSet;
}
