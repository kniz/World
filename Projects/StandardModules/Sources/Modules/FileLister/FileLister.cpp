#include "FileLister.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL FileLister::FileLister()
		: NEModule()
	{
				
	}

	NE_DLL FileLister::FileLister(const FileLister& source)
		: NEModule(source)
	{
		
	}

	NE_DLL FileLister::~FileLister()
	{

	}
	
	type_result NE_DLL FileLister::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(	NETStringKey()		);
		getKeySet().push(	NEUByteKey()		);
		getKeySet().push(	NETStringSetKey()	);
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL FileLister::execute()
	{
		//	pre:
		//		타겟팅:
		NETString& path = (static_cast<NETStringKey&>(getKeySet()[0])).getValue();
		type_ubyte& flag = (static_cast<NEUByteKey&>(getKeySet()[1])).getValue();
		if(path.getLength() <= 0)
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
		filer.setPath(path.toCharPointer());
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

	NEObject NE_DLL &FileLister::clone() const
	{
		return *(new FileLister(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &FileLister::getHeader() const
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
			_header.setMaxErrorCodeCount(FileLister::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL FileLister::getErrorMessage(type_errorcode errorcode) const
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
