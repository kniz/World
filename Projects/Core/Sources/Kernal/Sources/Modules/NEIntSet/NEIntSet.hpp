#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_int, false, type_int>;
	typedef NETVector<type_int, false, type_int> NEIntSet;
}
