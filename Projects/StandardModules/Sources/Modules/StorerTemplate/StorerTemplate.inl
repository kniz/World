#include "StorerTemplate.hpp"
#include "define/define.hpp"

namespace NE
{
	template <TEMPLATE_SIGNATURE>
	NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::StorerTemplate()
		: NEModule()
	{
		
	}

	template <TEMPLATE_SIGNATURE>
	NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::StorerTemplate(const StorerTemplate& source)
		: NEModule(source)
	{
		_connector.connect(getKeySet());
	}

	template <TEMPLATE_SIGNATURE>
	NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::~StorerTemplate()
	{

	}

	template <TEMPLATE_SIGNATURE>
	type_result NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::initialize()
	{
		getKeySet().create(1);
		getKeySet().push( KeyClass() );
		_connector.connect(getKeySet());

		return RESULT_SUCCESS;
	}

	template <TEMPLATE_SIGNATURE>
	type_result NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::execute()
	{
		return RESULT_SUCCESS;
	}

	template <TEMPLATE_SIGNATURE>
	NEObject NE_DLL &StorerTemplate<TEMPLATE_PARAMETERS>::clone() const
	{
		return *(new StorerTemplate<TEMPLATE_PARAMETERS>(*this));
	}

	template <TEMPLATE_SIGNATURE>
	const NEExportable::ModuleHeader NE_DLL &StorerTemplate<TEMPLATE_PARAMETERS>::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() =  _NAME;
			_header.getDeveloper() = _DEVELOPER;
			_header.setRevision(_REVISION);
			_header.getComment() = _COMMENT;
			_header.getVersion()  = _VERSION;
			_header.getReleaseDate() = _DATE;
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(StorerTemplate<TEMPLATE_PARAMETERS>::ERROR_CODE_END - 1);
		}

		return _header;
	}

	template <TEMPLATE_SIGNATURE>
	LPCTSTR NE_DLL StorerTemplate<TEMPLATE_PARAMETERS>::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}

	template <TEMPLATE_SIGNATURE>
	typename StorerTemplate<TEMPLATE_PARAMETERS>::Connector NE_DLL &StorerTemplate<TEMPLATE_PARAMETERS>::getConnector()
	{
		return _connector;
	}
}

#include "innerclass/Connector/Connector.inl"