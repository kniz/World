#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_double, false, type_double>;
	typedef NETVector<type_double, false, type_double> NEDoubleSet;
}
