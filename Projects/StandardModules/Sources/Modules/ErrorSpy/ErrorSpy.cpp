#include "ErrorSpy.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL ErrorSpy::ErrorSpy()
		: NEModule()
	{
				
	}

	NE_DLL ErrorSpy::ErrorSpy(const ErrorSpy& source)
		: NEModule(source)
	{
		
	}

	NE_DLL ErrorSpy::~ErrorSpy()
	{

	}
	
	type_result NE_DLL ErrorSpy::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NEUIntKey()	);
		getKeySet().push( NEBooleanKey()		);
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL ErrorSpy::execute()
	{
		//	pre:
		//		타겟팅:
		type_result	error_type_for_validation = static_cast<NEIntKey&>(getKeySet()[0]).getValue();			
		bool will_validate_exactly = static_cast<NEBooleanKey&>(getKeySet()[1]).getValue();
		type_result result_from_previous = Kernal::getInstance().getNodeManager().getLocalStack().getRecentResultCode();
		
		
		
		//	main:
		//		비교값과 대상값과의 연산:
		type_result validated_result = result_from_previous & error_type_for_validation;
		//		타입 검사:
		if(will_validate_exactly)
		{
			if(error_type_for_validation == validated_result)
				return RESULT_SUCCESS | RESULT_TRUE;
			else
				return RESULT_SUCCESS | RESULT_FALSE;
		}
		else
		{
			if(validated_result != 0)
				return RESULT_SUCCESS | RESULT_TRUE;
			else
				return RESULT_SUCCESS | RESULT_FALSE;
		}		
	}

	NEObject NE_DLL &ErrorSpy::clone() const
	{
		return *(new ErrorSpy(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ErrorSpy::getHeader() const
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
			_header.setMaxErrorCodeCount(ErrorSpy::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL ErrorSpy::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}
}
