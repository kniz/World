#pragma once

#include "../../Commons/Templates/NEArrayTemplate/NEArrayTemplate.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<type_wchar, false, type_wchar, NEType::NEWCHAR_SET>;
	typedef NEArrayTemplate<type_wchar, false, type_wchar, NEType::NEWCHAR_SET> NEWCharSet;
}
