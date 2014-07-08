#include "NameChanger.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL NameChanger::NameChanger()
		: NEModule()
	{
				
	}

	NE_DLL NameChanger::NameChanger(const NameChanger& source)
		: NEModule(source)
	{
		
	}

	NE_DLL NameChanger::~NameChanger()
	{

	}
	
	type_result NE_DLL NameChanger::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NENodeSelector() );
		getKeySet().push( NEIntKey() );
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NameChanger::execute()
	{
		NENodeSelector&	selector	= static_cast<NENodeSelector&>(	getKeySet()[0] );
		NEIntKey&		code_key	= static_cast<NEIntKey&>(		getKeySet()[2] );
		


		//	main:		
		while(true)
		{
			NENode& node = selector.getNode();
			if( ! &node)
				break;

			type_result result = node.setNameCode(code_key.getValue());
			if(NEResult::hasError(result))
			{
				ALERT_ERROR("노드의 이름 변경 도중 에러가 발생했습니다.\n\t변경하려 했던 노드의 주소 : %d\n\t변경하려고 했던 새로운 코드값 : %d", &node, code_key.getValue() )
				selector.initializeReferingPoint();
				return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | KERNAL_HAS_FAILED_TO_CHANGE_NAMECODE_OF_NODE;
			}
		}		

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NameChanger::clone() const
	{
		return *(new NameChanger(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &NameChanger::getHeader() const
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
			_header.setMaxErrorCodeCount(NameChanger::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL NameChanger::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case KERNAL_HAS_FAILED_TO_CHANGE_NAMECODE_OF_NODE:
			return _T("노드의 이름 변경 도중 에러가 발생했습니다.");

		default:
			return _T("알수 없는 에러");
		}
	}
}
