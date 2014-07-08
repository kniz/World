#include "../../NEPanelManager.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPanelManager::DLLHeader::DLLHeader()
		: NEObject()
	{
		
	}


	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPanelManager::DLLHeader::DLLHeader(const NEPanelManager::DLLHeader& source)
		: NEObject(source)
	{
		
	}

	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPanelManager::DLLHeader::~DLLHeader()
	{
		
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEPanelManager::DLLHeader::getType() const
	{
		return NEType::PANEL_MANAGER_HEADER;
	}	
	
	bool NE_DLL NEPanelManager::DLLHeader::operator==(const DLLHeader& source) const
	{
		if(isLoadable() != source.isLoadable()) return false;
		if(getPath() != source.getPath()) return false;
		if(getInstance() != source.getInstance()) return false;
		if(getPanelEntryPoint() != source.getPanelEntryPoint()) return false;

		return true;
	}

	bool NE_DLL NEPanelManager::DLLHeader::operator!=(const DLLHeader& source) const
	{
		return !(operator==(source));
	}
}

