#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_char, false, type_char>;
	typedef NETVector<type_char, false, type_char> NECharSet;
}