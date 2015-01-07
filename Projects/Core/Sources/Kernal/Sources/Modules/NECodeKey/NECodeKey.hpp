#pragma once
#pragma warning(push)
#pragma warning(disable : 4800)
#pragma warning(disable : 4804)

//	include:
#include "../../Commons/Templates/NETArithmeticKey/NETArithmeticKey.hpp"
#include "../../Commons/Units/NECode/NECode.hpp"

namespace NE
{
	template
	class NE_DLL NETArithmeticKey<NECode, NEType::NECODE_KEY>;
	typedef NETArithmeticKey<NECode, NEType::NECODE_KEY> NECodeKey;
}

#pragma warning(pop)