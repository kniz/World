#include "Extender.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL Extender::Extender()
		: NEModule()
	{
				
	}

	NE_DLL Extender::Extender(const Extender& source)
		: NEModule(source)
	{
		
	}

	NE_DLL Extender::~Extender()
	{

	}
	
	type_result NE_DLL Extender::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(	NEKeySelector()	);
		getKeySet().push(	NEKeySelector()	);
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL Extender::execute()
	{
		//	pre:
		//		타겟팅:
		//			키셀렉터:
		NEKeySelector& operand_target	= static_cast<NEKeySelector&>( getKeySet()[0] ),
					 & operand_source	= static_cast<NEKeySelector&>( getKeySet()[1] );		


		//	main:
		while(NEKey* source_key = &operand_source.getKey())
		{
			while(true)
			{
				//	타겟키 추출:
				NEKey& target_key = operand_target.getKey();
				if( ! &target_key)
					break;

				target_key.extend(*source_key);
			}
		}
		

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &Extender::clone() const
	{
		return *(new Extender(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &Extender::getHeader() const
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
			_header.setMaxErrorCodeCount(Extender::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL Extender::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case COULD_NOT_GET_KEY_FROM_SOURCE_SELECTOR:
			return _T("소스 셀렉터로부터 키를 가져오지 못했습니다.");

		default:
			return _T("알수 없는 에러");
		}
	}
}
