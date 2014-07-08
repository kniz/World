#include "NodeFileLister.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL NodeFileLister::NodeFileLister()
		: NEModule()
	{
				
	}

	NE_DLL NodeFileLister::NodeFileLister(const NodeFileLister& source)
		: NEModule(source)
	{
		
	}

	NE_DLL NodeFileLister::~NodeFileLister()
	{

	}
	
	type_result NE_DLL NodeFileLister::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(	NEUByteKey()		);
		getKeySet().push(	NETStringSetKey()	);
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NodeFileLister::execute()
	{
		//	pre:
		//		타겟팅:
		const Kernal::ModifiableSettings& settings = Kernal::getInstance().getSettings();
		const NETString& node_path = settings.getNodeDirectory();
		type_ubyte& flag = (static_cast<NEUByteKey&>(getKeySet()[1])).getValue();
		if(node_path.getLength() <= 0)
		{
			ALERT_ERROR(" : 경로가 없습니다.")
			return RESULT_TYPE_WARNING | THERE_IS_NO_PATH;
		}
		NETStringSet& list = (static_cast<NETStringSetKey&>(getKeySet()[2])).getValue();
		


		//	main:
		//		파일 데이터를 담을 버퍼 정의:
		/*
					스택은 크기 변경시에 부하가 있으므로 List에 담은 후 스택으로 변경한다.
					2012년 3월 7일 버전 현재, 폴더명까지는 추출이 되지 않는다.
		*/
		NEStringList buffer;
		//		경로에 접근:
		NEFileSystem filer;
		filer.setPath((node_path + _T("\\*.") + settings.getScriptExtractor()).toCharPointer());
		filer.setSearchLowerDirectory( flag & _WILL_SEARCH_SUB_DIRECTORY );
		while(true)
		{
			filer.findFile();
			const NEFileSystem::TaskUnit& unit = filer.getLastElement();
			if( ! &unit)
				break;

			if(flag & _GET_FILENAME_ONLY)
				buffer.push(unit.getFileName());
			else
				buffer.push(unit.getFilePath());
		}



		//	post:
		//		입력된 버퍼(리스트)를 스택으로 변환:
		//			스택 초기화:
		list.create(buffer.getLength());
		for(int n=0; n < buffer.getLength() ;n++)
			list.push(buffer[n]);
	
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NodeFileLister::clone() const
	{
		return *(new NodeFileLister(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &NodeFileLister::getHeader() const
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
			_header.setMaxErrorCodeCount(NodeFileLister::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL NodeFileLister::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case THERE_IS_NO_PATH:
			return _T("경로가 입력되지 않았습니다");

		default:
			return _T("알수 없는 에러");
		}
	}
}
