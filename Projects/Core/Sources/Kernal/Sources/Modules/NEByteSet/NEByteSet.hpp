#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_byte, false, type_byte>;
	typedef NETVector<type_byte, false, type_byte> NEByteSet;
}
