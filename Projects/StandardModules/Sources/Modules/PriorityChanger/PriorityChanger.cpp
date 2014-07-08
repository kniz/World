#include "PriorityChanger.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL PriorityChanger::PriorityChanger()
		: NEModule()
	{
		
	}

	NE_DLL PriorityChanger::PriorityChanger(const PriorityChanger& source)
		: NEModule(source)
	{
		
	}

	NE_DLL PriorityChanger::~PriorityChanger()
	{

	}
	
	type_result NE_DLL PriorityChanger::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NENodeSelector() );
		getKeySet().push( NEIntKey() );
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL PriorityChanger::execute()
	{
		NENodeSelector&	selector	= static_cast<NENodeSelector&>(	getKeySet()[0] );
		NEIntKey&		code_key	= static_cast<NEIntKey&>(		getKeySet()[2] );
		


		//	main:		
		while(true)
		{
			NENode& node = selector.getNode();
			if( ! &node)
				break;

			type_result result = node.setPriority(code_key.getValue());
			if(NEResult::hasError(result))
			{
				ALERT_ERROR("노드의 우선권 변경 도중 에러가 발생했습니다.\n\t변경하려 했던 노드의 주소 : %d\n\t변경하려고 했던 새로운 코드값 : %d", &node, code_key.getValue() )
				selector.initializeReferingPoint();
				return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | KERNAL_HAS_FAILED_TO_CHANGE_PRIORITYCODE_OF_NODE;
			}
		}		

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &PriorityChanger::clone() const
	{
		return *(new PriorityChanger(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &PriorityChanger::getHeader() const
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
			_header.setMaxErrorCodeCount(PriorityChanger::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL PriorityChanger::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case KERNAL_HAS_FAILED_TO_CHANGE_PRIORITYCODE_OF_NODE:
			return _T("노드의 우선권 변경 도중 에러가 발생했습니다.");

		default:
			return _T("알수 없는 에러");
		}
	}
}
