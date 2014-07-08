#include "GroupChanger.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL GroupChanger::GroupChanger()
		: NEModule()
	{
				
	}

	NE_DLL GroupChanger::GroupChanger(const GroupChanger& source)
		: NEModule(source)
	{
		
	}

	NE_DLL GroupChanger::~GroupChanger()
	{

	}
	
	type_result NE_DLL GroupChanger::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NENodeSelector() );
		getKeySet().push( NEIntSetKey() );
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL GroupChanger::execute()
	{
		NENodeSelector&	selector	= static_cast<NENodeSelector&>(	getKeySet()[0] );
		NEIntSetKey&	code_key	= static_cast<NEIntSetKey&>(	getKeySet()[1] );
		


		//	main:		
		while(true)
		{
			NENode& node = selector.getNode();
			if( ! &node)
				break;

			type_result result = node.setGroupCode(code_key.getValue());
			if(NEResult::hasError(result))
			{
				NETString codeset_string;
				for(int n=0; n < code_key.getValue().getLength() ;n++)
					codeset_string += code_key.getValue()[n] + " ";

				ALERT_ERROR("노드의 그룹 변경 도중 에러가 발생했습니다.\n\t변경하려 했던 노드의 주소 : %d\n\t변경하려고 했던 새로운 코드값 : %s", &node,  codeset_string.toCharPointer())
				selector.initializeReferingPoint();
				return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | KERNAL_HAS_FAILED_TO_CHANGE_GROUPCODE_OF_NODE;
			}
		}		

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &GroupChanger::clone() const
	{
		return *(new GroupChanger(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &GroupChanger::getHeader() const
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
			_header.setMaxErrorCodeCount(GroupChanger::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL GroupChanger::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case KERNAL_HAS_FAILED_TO_CHANGE_GROUPCODE_OF_NODE:
			return _T("노드의 그룹코드 변경 도중 에러가 발생했습니다.");

		default:
			return _T("알수 없는 에러");
		}
	}
}
