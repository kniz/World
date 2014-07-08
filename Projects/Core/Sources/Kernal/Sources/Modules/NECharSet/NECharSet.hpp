#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_char, false, type_char, NEType::NECHAR_SET>;
	typedef NEArrayTemplate<type_char, false, type_char, NEType::NECHAR_SET> NECharSet;
}