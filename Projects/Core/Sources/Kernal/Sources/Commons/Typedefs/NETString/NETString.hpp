#pragma once
//	include:
#include "../../../Modules/NEString/NEString.hpp"
#include "../../../Modules/NEWString/NEWString.hpp"
#include "../../../Modules/NEStringList/NEStringList.hpp"
#include "../../../Modules/NEWStringList/NEWStringList.hpp"

namespace NE
{
#ifdef _UNICODE
	typedef NEWString NETString;
	typedef NEWStringSet NETStringSet;
	typedef NEWStringList NETStringList;
#else
	typedef NEString NETString;
	typedef NEStringSet NETStringSet;
	typedef NEStringList NETStringList;
#endif
}
