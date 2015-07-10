#include "NENodeManager.hpp"
#include "../NENode/NENode.hpp"

namespace NE
{	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NENodeManager::getType() const
	{
		return NEType::NENODE_MANAGER;
	}

	type_result NENodeManager::initialize()
	{
		return getLocalStack().initialize();
	}
}
