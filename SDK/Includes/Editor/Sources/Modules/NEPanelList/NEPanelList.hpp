#pragma once

#include "../NEPanel/NEPanel.hpp"

namespace NE
{
	template
	class NE_DLL NEListTemplate<NEPanel*, true, NEType::NEPANEL_LIST>;
	typedef NEListTemplate<NEPanel*, true, NEType::NEPANEL_LIST> NEPanelList;
}
