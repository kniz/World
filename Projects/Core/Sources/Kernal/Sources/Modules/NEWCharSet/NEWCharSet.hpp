#pragma once

#pragma message("NEWCharSet.hpp - 1")
#include "../NETVector/NETVector.hpp"
#pragma message("NEWCharSet.hpp - 2")

namespace NE
{
	template
	class NE_DLL NETVector<type_wchar>;
	typedef NETVector<type_wchar> NEWCharSet;
}
#pragma message("NEWCharSet.hpp - 3")