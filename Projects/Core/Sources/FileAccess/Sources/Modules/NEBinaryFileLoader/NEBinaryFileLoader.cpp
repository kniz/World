//	include:
#include "NEBinaryFileLoader.hpp"

//	main:
namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEBinaryFileLoader::NEBinaryFileLoader(LPCTSTR filename)
		: NEBinaryFileAccessor(filename)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEBinaryFileLoader::NEBinaryFileLoader()
		: NEBinaryFileAccessor()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEBinaryFileLoader::~NEBinaryFileLoader()
	{
		release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	이진 모드로 파일로부터 데이터를 로드한다.
	//	인자값	:	char*	data	로드한 데이터가 담기게 된다. char*의 형태이므로,
	//								실제로 사용하기 위해서는 강제 형변환 reinterpreter_cast
	//								가 필요하다.
	//	사용방법:	데이터를 reinterpreter_cast<char*>로 형변환해서 data에 넘겨준다.
	//				예)	CMyClass a;
	//				execute( reinterpreter_cast<char*>(&a), sizeof(a) );
	//	동작조건:	사전에 파일이 이진모드로 open 되어야 한다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileLoader::execute(NE_OUT char* data, int size)
	{
		//	pre:
		if(!isFileOpenSuccess()) return;

		//	main:
		_binary_file_in_stream.read(data, size);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일을 이진 모드로 open 한다.	
	//	동작조건:	이전에 open할 경로를 입력해야 한다. (NEBinaryFileAccessor의 setPath)
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileLoader::open()
	{			
		//	pre:
		if(_binary_file_in_stream.is_open()) return;
		const NEFileSystem::TaskUnit& task = getLastElement();
		if( ! &task) return;
		if( ! task.isPathInputted()) return;
		if( ! task.isTaskExecutedAtLeastOnce()) findFile();
		//	여기에 도달했다는 건 최소한 1번은 findFile을 했다는 얘기
		//	왜 TaskUnit을 두번 가져오는 가:
		//		findFile() 을 하면서 처음 task가 pop(= delete) 될수도 있다. 
		const NEFileSystem::TaskUnit& task_after_finding = getLastElement();
		if( ! &task_after_finding) return;
		if( ! task.isFileInformationFilledIn()) return;
		if( ! task.isThereAnyTask()) return;

		//	main:
		_binary_file_in_stream.open(task.getFilePath(), std::ios::binary);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일을 닫는다.	
	//	동작조건:
	//	메모	:	eof 설정을 비롯해서 에러가 발생한 것도 초기화 시킨다.	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileLoader::close()
	{
		//	pre:
		if(_binary_file_in_stream.is_open() == false) return;

		//	main:
		_binary_file_in_stream.seekg(0);
		_binary_file_in_stream.close();	
		_binary_file_in_stream.clear(); // 일단 eof bit가 발생했던걸 원래대로 good-bit로 되돌린다.
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	초기화한다.
	//				경로, "하위폴더검색여부", 파일 close를 전부 실행한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileLoader::release()
	{
		close();
		NEFileSystem::release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일이 성공적으로 open 되었는지 여부를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_success NE_DLL NEBinaryFileLoader::isFileOpenSuccess() const
	{
		return _binary_file_in_stream.is_open();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일의 끝에 도달했는지에 대한 여부를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEBinaryFileLoader::isEndOfFile() const
	{
		return _binary_file_in_stream.eof();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	현재 이진 파일의 위치를 파악한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	long int NE_DLL NEBinaryFileLoader::getPosition()
	{
		return _binary_file_in_stream.tellg();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정한 위치로 파일포인터를 이동시킨다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileLoader::setPosition(long int position)
	{
		_binary_file_in_stream.seekg(position);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEBinaryFileLoader::isSaver()
	{
		return false;
	}
}
