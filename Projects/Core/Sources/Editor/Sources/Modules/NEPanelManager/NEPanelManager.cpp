#include "NEPanelManager.hpp"
#include "define/define.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPanelManager::NEPanelManager()
		: NEModule()
	{
		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPanelManager::NEPanelManager(const NEPanelManager& source)
		: NEModule(source)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEPanelManager::~NEPanelManager()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEPanelManager::getType() const
	{
		return NEType::NEPANEL_MANAGER;
	}

	NEString& NEPanelManager::_getPanelEntryPointStringOfDLL() const
	{	
		static NEString _entrypoint_string;
		
		if(_entrypoint_string.getLength() <= 0)
			_entrypoint_string = _DLL_ENTRYPOINT_STRING;
		
		return _entrypoint_string;
	}
}
