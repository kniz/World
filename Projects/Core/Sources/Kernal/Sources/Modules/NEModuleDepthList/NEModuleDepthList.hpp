#pragma once

#include "../../Commons/Templates/NEListTemplate/NEListTemplate.hpp"
#include "../../Commons/Units/NEModuleDepthUnit/NEModuleDepthUnit.hpp"

namespace NE
{
	template
	class NE_DLL NEListTemplate<NEModuleDepthUnit, false, NEType::NEMODULE_DEPTH_LIST>;
	typedef NEListTemplate<NEModuleDepthUnit, false, NEType::NEMODULE_DEPTH_LIST> NEModuleDepthList;
}