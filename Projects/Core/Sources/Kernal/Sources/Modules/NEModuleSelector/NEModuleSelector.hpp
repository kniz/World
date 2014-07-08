#pragma once

#include "../../Commons/Templates/NEModuleSelectorTemplate/NEModuleSelectorTemplate.hpp"
#include "../NENodeSelector/NENodeSelector.hpp"
#include "../NEModuleCodeSetKey/NEModuleCodeSetKey.hpp"

namespace NE
{
	template
	class NE_DLL NEModuleSelectorTemplate<NENodeSelector, NEType::NEMODULE_SELECTOR>;
	typedef NEModuleSelectorTemplate<NENodeSelector, NEType::NEMODULE_SELECTOR> NEModuleSelector;
}	