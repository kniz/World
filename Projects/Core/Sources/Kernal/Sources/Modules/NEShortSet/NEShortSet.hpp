#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_short, false, type_short>;
	typedef NETVector<type_short, false, type_short> NEShortSet;
}
