#include "ListContentInserter.hpp"
#include "define/define.hpp"
#include "../ListBox/ListBox.hpp"

namespace NE
{
	NE_DLL ListContentInserter::ListContentInserter()
		: NEModule()
	{

	}

	NE_DLL ListContentInserter::ListContentInserter(const ListContentInserter& source)
		: NEModule(source)
	{

	}

	NE_DLL ListContentInserter::~ListContentInserter()
	{

	}

	type_result NE_DLL ListContentInserter::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NEModuleSelector());
		getKeySet().push(NETStringKey());

		return RESULT_SUCCESS;
	}

	type_result NE_DLL ListContentInserter::execute()
	{
		//	pre:
		static NEExportable::Identifier _identifier(_T("ListBox"), _T("haku"), 1);
		NEModuleSelector& selector	= static_cast<NEModuleSelector&>(getKeySet()[0]);
		NETStringKey& content		= static_cast<NETStringKey&>(getKeySet()[1]);
	
		while(true)
		{
			ListBox& list = static_cast<ListBox&>(selector.getModule());

			if( ! &list)
				break;
			else if(_identifier != list.getHeader())
				ALERT_ERROR(" : 리스트 모듈이 아닙니다")
			else
			{
				if(NEResult::hasError( list.insertContent(content.getValue())) )
				{
					ALERT_ERROR(" : 리스트박스에 추가 실패")

					return RESULT_TYPE_ERROR;
				}
			}
		}

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &ListContentInserter::clone() const
	{
		return *(new ListContentInserter(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ListContentInserter::getHeader() const
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
			_header.setMaxErrorCodeCount(ListContentInserter::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL ListContentInserter::getErrorMessage(type_errorcode errorcode) const
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
