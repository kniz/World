
#pragma once

#include "../../Commons/Templates/NEKeySelectorTemplate/NEKeySelectorTemplate.hpp"
#include "../NEModuleSelector/NEModuleSelector.hpp"

namespace NE
{
	template
	class NE_DLL NEKeySelectorTemplate<NENodeSelector, NEType::NEKEY_SELECTOR>;
	typedef NEKeySelectorTemplate<NENodeSelector, NEType::NEKEY_SELECTOR> NEKeySelector;
}
