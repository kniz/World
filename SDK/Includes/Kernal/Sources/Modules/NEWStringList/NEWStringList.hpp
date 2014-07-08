#pragma once

#include "../NEWString/NEWString.hpp"
#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEListTemplate<NEWString, false, NEType::NEWSTRING_LIST>;
	typedef NEListTemplate<NEWString, false, NEType::NEWSTRING_LIST> NEWStringList;
}
