#include "NodeRemover.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL NodeRemover::NodeRemover()
		: NEModule()
	{
		
	}

	NE_DLL NodeRemover::NodeRemover(const NodeRemover& source)
		: NEModule(source)
	{

	}

	NE_DLL NodeRemover::~NodeRemover()
	{

	}

	type_result NE_DLL NodeRemover::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NENodeSelector());

		return RESULT_SUCCESS;
	}

	type_result NE_DLL NodeRemover::execute()
	{
		//	pre:
		//		타겟팅:
		Kernal& kernal = Kernal::getInstance();		
		NERootNodeCodeSet& nodelist = kernal.getNodeManager().getRootNodes();
		NENodeSelector& selector = static_cast<NENodeSelector&>(getKeySet()[0]);
		


		type_result result = RESULT_SUCCESS;
		while(true)
		{
			NENode& node = selector.getNode();
			if( ! &node)
				break;

			NENodeCodeSet& owner = node.getOwner();
			if( ! &owner)
			{
				ALERT_ERROR(" : 주어진 노드의 소유자가 없습니다. 이 노드를 삭제하지 않고 건너뜁니다.");
				selector.initializeReferingPoint();
				result |= RESULT_TYPE_ERROR;
			}
			type_index node_index = NE_INDEX_ERROR;
			int n=0;
			while(1)
			{
				if(&owner[n] == &node)
				{
					type_result result = owner.remove(n);
					if(NEResult::hasError(result))
					{
						ALERT_ERROR(" : 노드 제거중 에러 발생\n에러코드:\t%d", result);
						selector.initializeReferingPoint();
						return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | ERROR_FROM_REMOVATION_OF_NODELIST;
					}
					break;
				}

				n++;
				if(n >= owner.getLength())
				{
					ALERT_ERROR(" : 주어진 노드가 소유자에 없습니다.");					
					result |= RESULT_ABORT_ACTION | RESULT_TYPE_WARNING;
				}
			}			
			
		}

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NodeRemover::clone() const
	{
		return *(new NodeRemover(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &NodeRemover::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(NodeRemover::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL NodeRemover::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case ERROR_FROM_REMOVATION_OF_NODELIST:
			return _T("ERROR_FROM_REMOVATION_OF_NODELIST");

		default:
			return _T("알수 없는 에러");
		}
	}
}
