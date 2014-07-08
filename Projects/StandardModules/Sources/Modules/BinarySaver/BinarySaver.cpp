#include "BinarySaver.hpp"
#include "define/define.hpp"

namespace NE
{
	NE_DLL BinarySaver::BinarySaver()
		: NEModule()
	{
				
	}

	NE_DLL BinarySaver::BinarySaver(const BinarySaver& source)
		: NEModule(source)
	{
		
	}

	NE_DLL BinarySaver::~BinarySaver()
	{

	}
	
	type_result NE_DLL BinarySaver::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NETStringKey());
		getKeySet().push(NEUByteKey());
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL BinarySaver::execute()
	{
		NETString& path = (static_cast<NETStringKey&>( getKeySet()[0] )).getValue();
		type_ubyte flag = (static_cast<const NEUByteKey&>( getKeySet()[1] )).getValue();
		


		//	main:
		//		Saver 정의:
		NEBinaryFileSaver saver(path.toCharPointer());
		switch(flag)
		{
		case _DONT_CARE:		
			break;
		case _DO_NOT_OVERWRITE:
			saver.findFile();
			if( &saver.getLastElement())
			{
				ALERT_ERROR(" : 파일이 이미 존재하고, Flag가 Overwrite를 금지했습니다.\n저장을 취소합니다.\n주어진 경로 : %s", path.toCharPointer());
				return RESULT_TYPE_ERROR | COULD_NOT_OVERWRITE_CAUSE_OF_FLAG;
			}
			break;
		case _OVERWRITE_ONLY:
			saver.findFile();
			if( ! &saver.getLastElement())
			{
				ALERT_ERROR(" : 파일이 존재하지 않고, Flag가 Overwrite만 허용했습니다.\n저장을 취소합니다.\n주어진 경로 : %s", path.toCharPointer());
				return RESULT_TYPE_ERROR | THERE_IS_NO_FILE_TO_OVERWRITE;
			}
			break;
		default:
			ALERT_ERROR(" : 잘못된 flag\nflag의 값 : %d", flag)
			return RESULT_TYPE_ERROR;
		}

		saver.open();
		if( ! saver.isFileOpenSuccess())
		{
			ALERT_ERROR(" : 파일 열기에 실패했습니다.\n 주어진 경로 : %s", path.toCharPointer());
			return RESULT_TYPE_ERROR | FAIL_TO_OPEN_THE_FILE;
		}

		saver << Kernal::getInstance().getNodeManager();



		//	post:
		saver.close();
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &BinarySaver::clone() const
	{
		return *(new BinarySaver(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &BinarySaver::getHeader() const
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
			_header.setMaxErrorCodeCount(BinarySaver::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL BinarySaver::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		case COULD_NOT_OVERWRITE_CAUSE_OF_FLAG:
			return _T("파일이 이미 존재. 플래그에서 덮어쓰기를 금지했기 때문에 작업취소 됨.");

		case THERE_IS_NO_FILE_TO_OVERWRITE:
			return _T("플래그에서 덮어쓰기만을 허용했으나, 덮어쓸 파일이 존재하지 않음.");

		case FAIL_TO_OPEN_THE_FILE:
			return _T("파일 열기에 실패");

		default:
			return _T("알수 없는 에러");
		}
	}
}
