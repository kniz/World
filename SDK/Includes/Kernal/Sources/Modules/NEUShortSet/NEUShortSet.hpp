#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_ushort, false, type_ushort, NEType::NEUSHORT_SET>;
	typedef NEArrayTemplate<type_ushort, false, type_ushort, NEType::NEUSHORT_SET> NEUShortSet;
}
