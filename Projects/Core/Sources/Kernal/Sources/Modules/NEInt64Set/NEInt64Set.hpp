#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_int64, false, type_int64>;
	typedef NETVector<type_int64, false, type_int64> NEInt64Set;
}
