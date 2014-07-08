#pragma once

#include "../NEString/NEString.hpp"
#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEListTemplate<NEString, false, NEType::NESTRING_LIST>;
	typedef NEListTemplate<NEString, false, NEType::NESTRING_LIST> NEStringList;
}
