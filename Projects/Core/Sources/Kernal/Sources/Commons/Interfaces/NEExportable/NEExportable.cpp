#include "NEExportable.hpp"

namespace NE
{
	LPCTSTR NE_DLL NEExportable::getErrorMessage(type_errorcode errorcode) const
	{
		return _T("ERROR UNEXPECTED");
	}
}