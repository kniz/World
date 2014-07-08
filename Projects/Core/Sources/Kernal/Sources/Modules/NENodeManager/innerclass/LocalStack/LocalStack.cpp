#include "../../NENodeManager.hpp"

namespace NE
{
	NE_DLL NENodeManager::LocalStack::LocalStack()
		: NEObject()
	{
	
	}
	
	NE_DLL NENodeManager::LocalStack::LocalStack(const LocalStack& source)
		: NEObject(source)
	{
		
	}
	
	NE_DLL NENodeManager::LocalStack::~LocalStack()
	{
	
	}


		
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NENodeManager::LocalStack::getType() const
	{
		return NEType::LOCALSTACK;
	}	
}
