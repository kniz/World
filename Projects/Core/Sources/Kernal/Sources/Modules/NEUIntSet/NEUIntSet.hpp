#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_uint, false, type_uint>;
	typedef NETVector<type_uint, false, type_uint> NEUIntSet;
}
