#pragma once

#include "../../Functions/NEResult/NEResult.hpp"

namespace NE
{
	class NE_DLL NEInitializable
	{
	public:
		virtual type_result initialize() = 0;
	};
}