#include "Enabler.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL Enabler::Enabler()
		: NEModule()
	{
		
	}

	NE_DLL Enabler::Enabler(const Enabler& source)
		: NEModule(source)
	{
		
	}

	NE_DLL Enabler::~Enabler()
	{

	}
	
	type_result NE_DLL Enabler::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push( NENodeSelector());
		getKeySet().push( NEBooleanKey() );
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL Enabler::execute()
	{
		NENodeSelector& selector = static_cast<NENodeSelector&>( getKeySet()[0] );
		NEBooleanKey& bool_key = static_cast<NEBooleanKey&>( getKeySet()[1] );
		
		NENode& node = Kernal::getInstance().getNodeManager().getLocalStack().getRecentNode();

		while(true)
		{
			NENode& node = selector.getNode();
			if( ! &node)
				break;

			node.setEnable(bool_key.getValue());
		}

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &Enabler::clone() const
	{
		return *(new Enabler(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &Enabler::getHeader() const
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
			_header.setMaxErrorCodeCount(Enabler::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL Enabler::getErrorMessage(type_errorcode errorcode) const
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
