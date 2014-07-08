//	include:
#include "NEBinaryFileSaver.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEBinaryFileSaver::NEBinaryFileSaver(LPCTSTR filename, NEFileSaverFlag flag)
		: NEBinaryFileAccessor(filename),
		_flag(flag)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEBinaryFileSaver::NEBinaryFileSaver(NEFileSaverFlag flag)
		: NEBinaryFileAccessor(), _flag(flag)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEBinaryFileSaver::~NEBinaryFileSaver()
	{
		release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	이진 모드로 파일에 데이터를 저장한다.
	//	인자값	:	char*	data	데이터가 파일에 담기게 된다. char*의 형태이므로,
	//								데이터를 execute()에 넘겨주기 전에 강제 형변환 reinterpreter_cast
	//								가 필요하다.
	//	사용방법:	데이터를 reinterpreter_cast<char*>로 형변환해서 data에 넘겨준다.
	//				예)	CMyClass a;
	//				execute( reinterpreter_cast<char*>(&a), sizeof(a) );
	//	동작조건:	사전에 파일이 이진모드로 open 되어야 한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileSaver::execute(NE_IN const char* const data, int size)
	{
		//	pre:
		if(_binary_file_out_stream.is_open() == false) return;
		if(!data) return;
		if(size <= 0) return;

		//	main:
		_binary_file_out_stream.write(data, size);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일을 이진 모드로 open 한다
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
	//	메모	:	Flag는 open을 수행하기 전에 입력이 되어있어야한다. 일단 한번 open이 되면
	//				그 이후에 Flag를 수정해도 영향을 주지 못한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-07-11	이태훈	추가		
	//					:	NEBinaryFileLoader::open()에서처럼, 로드시 findFile()을 하지 않을 
	//						경우 자동으로 실시하도록 변경했다.
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileSaver::open()
	{
		//	pre:
		if(_binary_file_out_stream.is_open()) return;
		const NEFileSystem::TaskUnit& task = getLastElement();
		if( ! &task) return;
		if( ! task.isPathInputted()) return;

		//	main:
		int flag = 0;

		if(_flag == NEFILESAVERFLAG_APPEND_AT_END_OF_FILE)
			flag = (std::ios::binary | std::ios::app | std::ios::ate);
		else if(_flag == NEFILESAVERFLAG_OVERWRITE)
			flag = (std::ios::binary | std::ios::ate);
		else if(_flag == NEFILESAVERFLAG_DO_NOT_OVERWRITE)
			flag = std::ios::binary | std::ios::_Noreplace | std::ios::ate;
		else if(_flag == NEFILESAVERFLAG_EXISTED_ONLY)
			flag = std::ios::binary | std::ios::_Nocreate | std::ios::ate;


		_binary_file_out_stream.open(task.getFilePath(), flag);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일을 닫는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileSaver::close()
	{
		//	pre:
		if(_binary_file_out_stream.is_open() == false) return;

		//	main:
		_binary_file_out_stream.seekp(0);
		_binary_file_out_stream.clear();
		_binary_file_out_stream.close();
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	초기화를 수행한다.
	//	동작조건:
	//	메모	:	파일의 close, 입력한 경로, "하위폴더검색 여부" 전부 초기화 한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileSaver::release()
	{
		_flag = NEFileSaverFlag(NE_DEFAULT);
		close();
		NEFileSystem::release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일이 제대로 open 되었는지 여부를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_success NE_DLL NEBinaryFileSaver::isFileOpenSuccess() const
	{
		return _binary_file_out_stream.is_open();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	Flag를 설정한다.
	//	동작조건:
	//	메모	:	자세한 정보는 NEFileSaverFlag의 헤더를 참조
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileSaver::setFlag(NEFileSaverFlag flag)
	{
		_flag = flag;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	Flag의 상황을 가져온다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEFileSaverFlag NE_DLL NEBinaryFileSaver::getFlag() const
	{
		return _flag;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	현재 이진 파일의 위치를 파악한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	long int NE_DLL NEBinaryFileSaver::getPosition()
	{
		return _binary_file_out_stream.tellp();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정한 위치로 파일포인터를 이동시킨다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEBinaryFileSaver::setPosition(long int position)
	{
		_binary_file_out_stream.seekp(position);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEBinaryFileSaver::isSaver()
	{
		return true;
	}
}
