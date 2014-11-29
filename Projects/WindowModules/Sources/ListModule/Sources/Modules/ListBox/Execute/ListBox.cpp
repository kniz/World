#include "ListBox.hpp"
#include "../define/define.hpp"

namespace NE
{
	type_result NE_DLL ListBox::initialize()
	{
		WND::initialize();

		getKeySet().resize(getKeySet().getLength() + 3);

		getKeySet().push( NEModuleSelector() );
		getKeySet().push( NETStringSetKey() );
		getKeySet().push( NEIntKey(_DEFAULT_MENU_ID) );

		_connector.connect(getKeySet());

		return RESULT_SUCCESS;
	}
	
	type_result NE_DLL ListBox::_onExecute()
	{
		//	pre:
		if(_hwnd)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		NEModuleSelector& selector = static_cast<NEModuleSelector&>(getKeySet()[5]);
		WND& module = static_cast<WND&>(selector.getModule());
		if( ! &module)
			return RESULT_SUCCESS;



		//	main:
		_parent_hwnd = module.getHWND();
		type_result result = _createList();
		if(NEResult::hasError(result))
		{
			ALERT_ERROR(" :  리스트 생성도중 에러 발생")

			return result | RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | ERROR_IN_CREATION_OF_LIST;
		}

		result = _fillContentsFromKey();
		if(NEResult::hasError(result))
		{
			ALERT_ERROR(" : 리스트에 키로부터 내용 추가하는 도중 에러 발생")

			return result | RESULT_TYPE_ERROR | RESULT_ABORT_ACTION | ERROR_IN_FILL_CONTENTS_FROM_KEY;
		}

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &ListBox::clone() const
	{
		return *(new ListBox(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &ListBox::getHeader() const
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
			_header.setMaxErrorCodeCount(ListBox::ERROR_CODE_END - 1);
			NETStringSet& argcomments = _header.getArgumentsComments();
			argcomments.create(3);
			argcomments.push("")
		}

		return _header;
	}

	LPCTSTR NE_DLL ListBox::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case ERROR_IN_CREATION_OF_LIST:
			return _T("리스트 생성도중 에러 발생");

		case ERROR_IN_FILL_CONTENTS_FROM_KEY:
			return _T("ERROR_IN_FILL_CONTENTS_FROM_KEY");

		default:
			return _T("알수 없는 에러");
		}
	}

	type_result NE_DLL ListBox::insertContent(const NETString& content)
	{
		if(! _hwnd) return RESULT_TYPE_ERROR;

		if(SendMessage(_hwnd, LB_ADDSTRING, 0, (LPARAM) content.toCharPointer()) == LB_ERR)
			return RESULT_TYPE_ERROR;		

		return RESULT_SUCCESS;
	}

	type_result NE_DLL ListBox::removeContent(type_index index)
	{
		if( ! _hwnd) return RESULT_TYPE_ERROR;

		if(SendMessage(_hwnd, LB_DELETESTRING, index, NE_NULL) == LB_ERR)
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	WND::WNDConnector NE_DLL &ListBox::getConnector()
	{
		return _connector;
	}

	const WND::WNDConnector NE_DLL &ListBox::getConnector() const
	{
		return _connector;
	}

	type_result ListBox::_createList()
	{
		if( ! _parent_hwnd)
			return RESULT_TYPE_ERROR;
		HINSTANCE instance = GetModuleHandle(NULL);
		NEIntKey& menu_id = static_cast<NEIntKey&>(getKeySet()[7]);



		//	main:
		_hwnd = CreateWindow(_T("listbox"),NULL,WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_SORT | LBS_DISABLENOSCROLL|
					WS_VSCROLL,	_connector.getX().getValue(), _connector.getY().getValue(), _connector.getWidth().getValue(), _connector.getHeight().getValue(),
					_parent_hwnd, (HMENU) menu_id.getValue(), instance, NULL);
		if( ! _hwnd)
			return RESULT_TYPE_ERROR;

		
		
		//	post:
		return RESULT_SUCCESS;
	}

	type_result ListBox::_fillContentsFromKey()
	{
		const NETStringSet& contents = (static_cast<NETStringSetKey&>(getKeySet()[6])).getValue();

		for(int n=0; n < contents.getLength() ;n++)
		{
			const NETString& content = contents[n];

			insertContent(content);
		}

		return RESULT_SUCCESS;
	}
}
