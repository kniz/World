#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_float, false, type_float>;
	typedef NETVector<type_float, false, type_float> NEFloatSet;
}
