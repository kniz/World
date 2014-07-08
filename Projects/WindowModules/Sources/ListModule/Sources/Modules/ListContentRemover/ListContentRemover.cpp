#include "ListContentRemover.hpp"
#include "define/define.hpp"
#include "../ListBox/ListBox.hpp"

namespace NE
{
	NE_DLL ListContentRemover::ListContentRemover()
		: NEModule()
	{

	}

	NE_DLL ListContentRemover::ListContentRemover(const ListContentRemover& source)
		: NEModule(source)
	{

	}

	NE_DLL ListContentRemover::~ListContentRemover()
	{

	}

	type_result NE_DLL ListContentRemover::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NEModuleSelector());
		getKeySet().push(NEIntKey(0));

		return RESULT_SUCCESS;
	}

	type_result NE_DLL ListContentRemover::execute()
	{
		//	pre:
		static NEExportable::Identifier _identifier(_T("ListBox"), _T("haku"), 1);
		NEModuleSelector& selector	= static_cast<NEModuleSelector&>(getKeySet()[0]);
		NEIntKey& index				= static_cast<NEIntKey&>(getKeySet()[1]);

		while(true)
		{
			ListBox& list = static_cast<ListBox&>(selector.getModule());

			if( ! &list)
				break;
			else if(_identifier != list.getHeader())
				ALERT_ERROR(" : 리스트 모듈이 아닙니다")
			else
			{
				if(NEResult::hasError( list.removeContent(index.getValue())) )
				{
					ALERT_ERROR(" : 리스트박스에 삭제 실패")

						return RESULT_TYPE_ERROR;
				}
			}
		}

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &ListContentRemover::clone() const
	{
		return *(new ListContentRemover(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ListContentRemover::getHeader() const
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
			_header.setMaxErrorCodeCount(ListContentRemover::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL ListContentRemover::getErrorMessage(type_errorcode errorcode) const
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
