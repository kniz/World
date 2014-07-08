#include "Exactor.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL Exactor::Exactor()
		: NEModule()
	{
				
	}

	NE_DLL Exactor::Exactor(const Exactor& source)
		: NEModule(source)
	{
		
	}

	NE_DLL Exactor::~Exactor()
	{

	}
	
	type_result NE_DLL Exactor::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NEKeySelector() );
		getKeySet().push( NEKeySelector() );
		getKeySet().push( NEBooleanKey(false) );
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL Exactor::execute()
	{
		//	pre:
		NEKeySelector&	selector_left	= static_cast<NEKeySelector&>( getKeySet()[0] ),
					 &	selector_right	= static_cast<NEKeySelector&>( getKeySet()[1] );
		NEBooleanKey&	bool_key		= static_cast<NEBooleanKey&>( getKeySet()[2] );
		

		//	main:
		while(NEKey* source_key = &selector_left.getKey())
		{
			while(true)
			{
				NEKey& target_key = selector_right.getKey();
				if( ! &target_key)
					break;

				bool result_of_keys = (*source_key == target_key);
				if(bool_key.getValue() != result_of_keys)
				{
					selector_left.initializeReferingPoint();
					selector_right.initializeReferingPoint();
					return RESULT_SUCCESS | RESULT_FALSE;
				}
			}
		}
		

		//	post:
		return RESULT_SUCCESS | RESULT_TRUE;
	}

	NEObject NE_DLL &Exactor::clone() const
	{
		return *(new Exactor(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &Exactor::getHeader() const
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
			_header.setMaxErrorCodeCount(Exactor::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL Exactor::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case THERE_IS_NO_SOURCE_KEY:
			return _T("소스키(0번) 어떠한 키도 추출되지 않았습니다");

		default:
			return _T("알수 없는 에러");
		}
	}
}
