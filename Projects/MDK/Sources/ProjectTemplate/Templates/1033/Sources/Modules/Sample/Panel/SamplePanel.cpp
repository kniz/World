#include "[!output panel_name].hpp"
#include "../define/define.hpp"

#include <iostream>

namespace NE
{
	NE_DLL [!output panel_name]::[!output panel_name]()
		: NEPanel()
	{

	}

	NE_DLL [!output panel_name]::[!output panel_name](const [!output panel_name]& source)
		: NEPanel(source)
	{

	}

	NE_DLL [!output panel_name]::~[!output panel_name]()
	{

	}
	
	type_result NE_DLL [!output panel_name]::initialize()
	{
		_componentset.create(1);
		_componentset.push( StringTyper() );
		
		return RESULT_SUCCESS;
	}


	NEObject NE_DLL &[!output panel_name]::clone() const
	{
		return *(new [!output panel_name](*this));
	}

	const NEExportable::ModuleHeader NE_DLL &[!output panel_name]::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment()  = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount([!output panel_name]::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL [!output panel_name]::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case PANEL_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}
}
