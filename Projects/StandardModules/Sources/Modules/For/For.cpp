#include "For.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL For::For()
		: NEModule()
	{
				
	}

	NE_DLL For::For(const For& source)
		: NEModule(source)
	{
		
	}

	NE_DLL For::~For()
	{

	}
	
	type_result NE_DLL For::initialize()
	{
		getKeySet().create(4);
		getKeySet().push(NEIntKey());	//	시작 인덱스
		getKeySet().push(NEIntKey());	//	종료 인덱스
		getKeySet().push(NEIntKey());	//	OUT 카운트
		getKeySet().push(NEModuleCodeSetKey());
		
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL For::execute()
	{
		//	pre:
		type_int from_n = getStartIndex(),
				 to_n = getEndIndex();
		type_int& count = getCount();
		NEModuleCodeSet& actions = getActions();
		
		
		//	main:
		for(int n=from_n; n <= to_n ;n++)	//	n "<=" to_n 임에 주의하라.
		{
			count = n;
			actions.execute();
		}



		//	post:
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &For::clone() const
	{
		return *(new For(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &For::getHeader() const
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
			_header.setMaxErrorCodeCount(For::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL For::getErrorMessage(type_errorcode errorcode) const
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
