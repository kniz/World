#include "BinaryLoader.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL BinaryLoader::BinaryLoader()
		: NEModule()
	{
				
	}

	NE_DLL BinaryLoader::BinaryLoader(const BinaryLoader& source)
		: NEModule(source)
	{
		
	}

	NE_DLL BinaryLoader::~BinaryLoader()
	{

	}
	
	type_result NE_DLL BinaryLoader::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NETStringKey());
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL BinaryLoader::execute()
	{
		//	pre:
		NETString& path = (static_cast<NETStringKey&>( getKeySet()[0] )).getValue();
		NEBinaryFileLoader loader(path.toCharPointer());
		loader.open();
		if( ! loader.isFileOpenSuccess())
		{
			ALERT_ERROR(" : 잘못된 경로 입니다. %s", path.toCharPointer())
			return RESULT_TYPE_ERROR | INVALID_PATH;
		}		
		Kernal& kernal = Kernal::getInstance();
		NENodeManager& noder = Kernal::getInstance().getNodeManager();



		//	main:
		loader >> noder; // 여기서 스크립트도 자동으로 교체된다.

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &BinaryLoader::clone() const
	{
		return *(new BinaryLoader(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &BinaryLoader::getHeader() const
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
			_header.setMaxErrorCodeCount(BinaryLoader::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL BinaryLoader::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case INVALID_PATH:
			return _T("잘못된 경로 입니다.");

		default:
			return _T("알수 없는 에러");
		}
	}
}
