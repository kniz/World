#include "[!output module_name].hpp"
#include "../define/define.hpp"
#include <iostream>

namespace NE
{
		NE_DLL [!output module_name]::Connector::Connector()
			:	NEModule::BaseConnector(), _helloworld(NE_NULL)
		{
			
		}

		type_result NE_DLL [!output module_name]::Connector::connect(NEKeySet& keyset)
		{
			if(keyset.getLength() < 0) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY | RESULT_WRONG_PARAMETER | RESULT_WRONG_POINTER_ADDRESSING;
			if( ! &keyset[0] ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_WRONG_BOUNDARY;

			_helloworld = static_cast<NEStringKey*>( &(keyset[0]) );

			return RESULT_SUCCESS;
		}

		NEStringKey NE_DLL &[!output module_name]::Connector::getHelloWorld()
		{
			return *_helloworld;
		}


	NE_DLL [!output module_name]::[!output module_name]()
		: NEModule()
	{
		
	}

	NE_DLL [!output module_name]::[!output module_name](const [!output module_name]& source)
		: NEModule(source)
	{
		_connector.connect(_keyset);
	}

	NE_DLL [!output module_name]::~[!output module_name]()
	{

	}
	
	[!output module_name]::Connector NE_DLL &[!output module_name]::getConnector()
	{
		return _connector;
	}
	
	const [!output module_name]::Connector NE_DLL &[!output module_name]::getConnector() const
	{
		return _connector;
	}

	type_result NE_DLL [!output module_name]::initialize()
	{
		_keyset.create(_KEY_NUMBER);
		_keyset.push(NEStringKey("hello world!"));
		_connector.connect(_keyset);

		return RESULT_SUCCESS;
	}

	type_result NE_DLL [!output module_name]::execute()
	{
		std::cout << _connector.getHelloWorld().getValue().toCharPointer() << std::endl;

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &[!output module_name]::clone() const
	{
		return *(new [!output module_name](*this));
	}

	const NEExportable::ModuleHeader NE_DLL &[!output module_name]::getHeader() const
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
			_header.setMaxErrorCodeCount([!output module_name]::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL [!output module_name]::getErrorMessage(type_errorcode errorcode) const
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
