//	include:
#include "NESequencialFileSaver.hpp"

//	main:
namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	설명	:	생성자.
	//				NEFileSystem의 생성자를 호출해서 내부적으로 setPath를 수행한다.
	//	동작조건:
	//	메모	:	유니코드로 개발중이라면 (_UNICODE predefined가 정의되어있다면)
	//				로케일을 NE_LOCALE 값으로 설정한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NESequencialFileSaver::NESequencialFileSaver(LPCTSTR filename, NEFileSaverFlag flag)
		: NEFileSystem(filename),
		flag(flag)
	{
#ifdef _UNICODE
		_sequencial_file_out_stream.imbue(std::locale(NE_LOCALE));
#endif
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NESequencialFileSaver::NESequencialFileSaver(NEFileSaverFlag flag)
		: NEFileSystem(), flag(flag)
	{
#ifdef _UNICODE
		_sequencial_file_out_stream.imbue(std::locale(NE_LOCALE));
#endif
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NESequencialFileSaver::~NESequencialFileSaver()
	{
		release();
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	파일이 성공적으로 open 되었는지의 대한 여부를 반환한다.
	//	동작조건:	
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_success NE_DLL NESequencialFileSaver::isFileOpenSuccess() const
	{
		return _sequencial_file_out_stream.is_open();
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	주어진 문자열을 파일에 순차모드로 기록한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileSaver::writeString(const TCHAR* const string)
	{
		//	pre:
		if(!string) return;
		if(_sequencial_file_out_stream.is_open() == false) return;

		//	main:		
		_sequencial_file_out_stream << string;		
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	파일을 순차모드로 open 한다
	//	동작조건:	open할 파일이 입력되어야 한다.
	//				두가지 방법으로 파일의 경로를 줄 수 있다.
	//					방법 1.	직접 경로를 입력함
	//						: 이경우 findFile을 하지 않고 getPath()를 통해서 처음에 입력한
	//						경로로 open을 시도한다.
	//					방법 2. 와일드카드를 사용해서 파일을 검색후, open 한다.
	//						: 이 경우, 검색 경로를 입력한 후에 findFile()을 통해서 파일명을
	//						가져온다.
	//						그리고 open()을 통해서 가져온 파일의 경로(getFilePath())로 open
	//						하는 방법이다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileSaver::open()
	{	
		//	pre:
		if(_sequencial_file_out_stream.is_open()) return;
		const NEFileSystem::TaskUnit& task = getLastElement();
		if( ! &task) return;
		if(! task.isPathInputted()) return;		

		//	main:
		int stream_flag = 0;

		if(flag == NEFILESAVERFLAG_APPEND_AT_END_OF_FILE)
			stream_flag = std::ios::app;
		else if(flag == NEFILESAVERFLAG_OVERWRITE)
			stream_flag = std::ios::out;
		else if(flag == NEFILESAVERFLAG_DO_NOT_OVERWRITE)
			stream_flag = std::ios::_Noreplace;
		else if(flag == NEFILESAVERFLAG_EXISTED_ONLY)
			stream_flag = std::ios::_Nocreate;

		if(task.isFileInformationFilledIn())
			_sequencial_file_out_stream.open(task.getFilePath(), stream_flag); // 검색한 파일로 open 시도
		else
			_sequencial_file_out_stream.open(task.getPath(), stream_flag); // 직접입력한 경로로 open 시도
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	파일을 닫는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileSaver::close()
	{
		if(!_sequencial_file_out_stream.is_open()) return;

		_sequencial_file_out_stream.close();
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	초기화를 수행한다.
	//				파일을 닫고, NEFileSystem의 경로 데이터, "하위폴더검색 여부" Flag도 
	//				초기화한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileSaver::release() 
	{
		flag = NEFileSaverFlag(NE_DEFAULT);
		close();
		NEFileSystem::release();
	}	
}
