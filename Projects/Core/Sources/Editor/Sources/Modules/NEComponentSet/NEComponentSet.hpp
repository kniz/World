#pragma once

#include "../NEComponent/NEComponent.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEComponent*, true, NEComponent*, NEType::NECOMPONENT_SET>;
	typedef NEArrayTemplate<NEComponent*, true, NEComponent*, NEType::NECOMPONENT_SET> NEComponentSet;
}
