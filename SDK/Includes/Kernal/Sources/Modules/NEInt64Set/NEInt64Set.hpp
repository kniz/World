#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_int64, false, type_int64, NEType::NEINT64_SET>;
	typedef NEArrayTemplate<type_int64, false, type_int64, NEType::NEINT64_SET> NEInt64Set;
}
