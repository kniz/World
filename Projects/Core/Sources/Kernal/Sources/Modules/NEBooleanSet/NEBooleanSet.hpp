#pragma once

#include "../NETVector/NETVector.hpp"

namespace NE
{
	template
	class NE_DLL NETVector<type_bool, false, type_bool>;
	typedef NETVector<type_bool, false, type_bool> NEBooleanSet;
}
