#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_ubyte, false, type_ubyte>;
	typedef NETVector<type_ubyte, false, type_ubyte> NEUByteSet;
}
