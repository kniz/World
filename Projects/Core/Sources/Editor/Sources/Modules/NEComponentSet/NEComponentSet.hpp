#pragma once

#include "../NEComponent/NEComponent.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<NEComponent*, true, NEComponent*, NEType::NECOMPONENT_SET>;
	typedef NETVector<NEComponent*, true, NEComponent*, NEType::NECOMPONENT_SET> NEComponentSet;
}
