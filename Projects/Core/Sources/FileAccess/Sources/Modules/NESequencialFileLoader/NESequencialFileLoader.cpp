//	include:
#include "NESequencialFileLoader.hpp"

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
	NE_DLL NESequencialFileLoader::NESequencialFileLoader(LPCTSTR filename)
		: NEFileSystem(filename)
	{
#ifdef _UNICODE
		_sequencial_file_in_stream.imbue(std::locale(NE_LOCALE));
#endif
	}		



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NESequencialFileLoader::NESequencialFileLoader()
		: NEFileSystem()
	{
#ifdef _UNICODE
		_sequencial_file_in_stream.imbue(std::locale(NE_LOCALE));
#endif
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NESequencialFileLoader::~NESequencialFileLoader()
	{

	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	open한 파일로부터 순차적으로 한줄을 읽어들인다.
	//				읽어들인 문자열은 argument인 string_buffer_not_null에 저장한다.
	//	동작조건:	성공적으로 순차모드를 통해 파일을 open() 해야 한다.
	//	인자값	:	TCHAR*	string_pointer_with_null	
	//					:	로드한 데이터가 저장될 버퍼의 주소. 외부에서 데이터가 할당되서
	//						들어온다.
	//				int		buffer_size	:	버퍼의 글자수	
	//	메모	:	개행문자('\n')도 읽어들이므로, 버퍼에 개행문자가 남지않는다.
	//	히스토리:	2011-07-07	이태훈 개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileLoader::readByLine(NE_OUT TCHAR* string_buffer_not_null, int buffer_size)
	{
		//	pre:
		if(!buffer_size) return;
		if(!string_buffer_not_null) return;
		if(!_sequencial_file_in_stream.is_open()) return;

		//	main:
		_sequencial_file_in_stream.getline(string_buffer_not_null, buffer_size, '\n');
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	open한 파일로부터 순차적으로 주어진 구분자(delimter)까지 읽어들인다.
	//				읽어들인 문자열은 argument인 string_buffer_not_null에 저장한다.
	//	동작조건:	성공적으로 순차모드를 통해 파일을 open() 해야 한다.
	//	인자값	:	TCHAR*	string_pointer_with_null	
	//					:	로드한 데이터가 저장될 버퍼의 주소. 외부에서 데이터가 할당되서
	//						들어온다.
	//				int		buffer_size	:	버퍼의 글자수
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileLoader::readByToken(NE_OUT TCHAR* string_buffer_not_null, int buffer_size, TCHAR token)
	{
		//	pre:
		if(!buffer_size) return;
		if(!string_buffer_not_null) return;
		if(!_sequencial_file_in_stream.is_open()) return;

		//	main:
		_sequencial_file_in_stream.getline(string_buffer_not_null, buffer_size, token);
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	순차모드로 파일을 open 한다.
	//	동작조건:	파일 경로가 입력되어 있어야 한다. (NEFileSystem의 setPath)
	//	메모	:	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileLoader::open()
	{
		//	pre:
		if(_sequencial_file_in_stream.is_open()) return;
		const NEFileSystem::TaskUnit& task = getLastElement();
		if( ! &task) return;
		if( ! task.isPathInputted()) return;
		if(! task.isTaskExecutedAtLeastOnce()) findFile();
		//	여기에 도달했다는 건 최소한 1번은 findFile을 했다는 얘기			
		if(! task.isFileInformationFilledIn()) return;
		if(! task.isThereAnyTask()) return;

		//	main:
		_sequencial_file_in_stream.open(task.getFilePath(), std::ios_base::in);
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	open했던 파일을 close 한다.
	//	동작조건:
	//	메모	:	eof와 같은 상태비트나 에러를 초기화한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileLoader::close()
	{
		//	pre:
		if(!_sequencial_file_in_stream.is_open()) return;

		//	main:
		_sequencial_file_in_stream.close();
		_sequencial_file_in_stream.clear(); // 일단 eof bit가 발생했던걸 원래대로 good-bit로 되돌린다.
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	모든 변수와 상태를 초기화한다.
	//	동작조건:
	//	메모	:	파일의 close, 입력한 경로, "하위폴더검색 여부" 전부 초기화 한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NESequencialFileLoader::release()
	{
		_sequencial_file_in_stream.close();
		NEFileSystem::release();
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	파일이 성공적으로 open 되었는지의 대한 여부를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_success NE_DLL NESequencialFileLoader::isFileOpenSuccess() const
	{
		return _sequencial_file_in_stream.is_open();
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	파일이 끝에 도달했는지 여부를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NESequencialFileLoader::isEndOfFile() const
	{
		return _sequencial_file_in_stream.eof();
	}

}
