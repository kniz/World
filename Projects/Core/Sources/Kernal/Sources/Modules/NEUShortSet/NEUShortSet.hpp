#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_ushort, false, type_ushort>;
	typedef NETVector<type_ushort, false, type_ushort> NEUShortSet;
}
