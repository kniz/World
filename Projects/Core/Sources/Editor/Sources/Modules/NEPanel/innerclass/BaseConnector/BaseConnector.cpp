#include "../../NEPanel.hpp"

namespace NE
{
	NE_DLL NEPanel::BaseConnector::BaseConnector()
	{

	}

	NE_DLL NEPanel::BaseConnector::BaseConnector(const NEPanel::BaseConnector& source)
	{

	}

	NE_DLL NEPanel::BaseConnector::~BaseConnector()
	{

	}

	const NEPanel::BaseConnector NE_DLL &NEPanel::BaseConnector::operator=(const BaseConnector& source)
	{
		return *this;
	}

	bool NE_DLL NEPanel::BaseConnector::operator==(const BaseConnector& source) const
	{
		return true;
	}

	bool NE_DLL NEPanel::BaseConnector::operator!=(const BaseConnector& source) const
	{
		return false;
	}	
}

