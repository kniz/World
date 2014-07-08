#include "NodeCreator.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL NodeCreator::NodeCreator()
		: NEModule()
	{
				
	}

	NE_DLL NodeCreator::NodeCreator(const NodeCreator& source)
		: NEModule(source)
	{
		
	}

	NE_DLL NodeCreator::~NodeCreator()
	{

	}
	
	type_result NE_DLL NodeCreator::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NENodeSelector(NEType::NESCRIPT_MANAGER));
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NodeCreator::execute()
	{
		//	pre:
		//		타겟팅:
		Kernal& kernal = Kernal::getInstance();
		const NERootNodeCodeSet& scriptset = kernal.getScriptManager().getScriptNodes();
		NERootNodeCodeSet& nodelist = kernal.getNodeManager().getRootNodes();
		NENodeSelector& selector = static_cast<NENodeSelector&>(getKeySet()[0]);

		NENode* node = 0;
		while( node = &selector.getNode())
		{
			NENode& script = *node;

			type_result result = nodelist.push(script);
			if(NEResult::hasError(result))
			{
				ALERT_ERROR(" : 노드리스트에 push 도중 에러 발생.\n에러 코드 : \t%d", result);
				selector.initializeReferingPoint();
				return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | ERROR_HAPPEN_WHILE_PUSHING_TO_NODELIST;
			}
		}


		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NodeCreator::clone() const
	{
		return *(new NodeCreator(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &NodeCreator::getHeader() const
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
			_header.setMaxErrorCodeCount(NodeCreator::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL NodeCreator::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case INVALID_SCRIPT_ACCESS:
			return _T("INVALID_SCRIPT_ACCESS");

		case ERROR_HAPPEN_WHILE_PUSHING_TO_NODELIST:
			return _T("ERROR_HAPPEN_WHILE_PUSHING_TO_NODELIST");

		default:
			return _T("알수 없는 에러");
		}
	}
}
