#pragma once

//	include:
#include "NEFileSystem.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	설명	:	기본 생성자
	//	동작조건:	
	//	메모	:	하위폴더를 검색하지 않는다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEFileSystem::NEFileSystem()
		: _length(NE_NULL), _header(NE_NULL), _is_search_lower_directory_too(false)
	{

	}



	//	---------------------------------------------------------------------------------
	//	설명	:	생성자
	//	동작조건:
	//	인자값	:	bool _is_search_lower_directory_too	하위폴더도 같이 검사하는가		
	//	메모	:	기본값을 사용하지 않기 위해서 함수를 둘로 나누었다
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEFileSystem::NEFileSystem(bool _is_search_lower_directory_too)
		: _length(NE_NULL), _header(NE_NULL), _is_search_lower_directory_too(_is_search_lower_directory_too)
	{

	}



	//	---------------------------------------------------------------------------------
	//	설명	:	생성자
	//	동작조건:	
	//	메모	:	하위폴더는 검색하지 않는다. 
	//				setPath()를 사용하는 것과 같은 효과다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEFileSystem::NEFileSystem(LPCTSTR path)
		: _length(NE_NULL), _header(NE_NULL), _is_search_lower_directory_too(false)
	{			
		setPath(path);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	생성자
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEFileSystem::NEFileSystem(LPCTSTR path, bool is_search_lower_directory_too)
		: _length(NE_NULL), _header(NE_NULL), _is_search_lower_directory_too(is_search_lower_directory_too)
	{		
		setPath(path);			
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	소멸자. 모든 멤버변수를 초기화하고 메모리 할당을 해제한다
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEFileSystem::~NEFileSystem()
	{
		release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	몇개의 작업이 실행중 및 예약중인가를 반환한다.
	//				TaskUnit의 갯수를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_index NE_DLL NEFileSystem::getLength() const
	{
		return _length;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	현재 실행중인 작업의 인덱스를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_index NE_DLL NEFileSystem::getLastIndex() const
	{			
		return _length-1;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	TaskUnit의 멤버변수를 통해서 파일을 검색한다.
	//	동작	:	실제 검색은 API인 FindFirstFile과 FindNextFile을 통해서 이루어진다.
	//				NEFileSystem은 API의 결과와 진행상황을 관리/기록하는 역할만 수행한다.
	//	동작조건:	사전에 경로가 입력되어야한다. (setPath)
	//	메모	:	이 클래스의 가장 핵심적인 함수
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEFileSystem::findFile()
	{	
		//	pre:
		//		멤버변수 검사:
		if(_length <= 0) 
			return;

		//		find할 Task검사:
		TaskUnit& target = _getElement(getLastIndex());
		if( ! &target) return;
		if( !(target._path) ) return;
		if(target._is_task_executed_at_least_once)
		{
			if( ! target._is_there_any_task) return;
			if( ! target._is_file_handle_valid) return;
		}



		//	main:
		if(target._is_task_executed_at_least_once) 			
			_findNextFile();
		else
			_findFirstFile();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	모든 TaskUnit을 초기화하고, 주어진 경로로 새로운 TaskUnit을 만든다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEFileSystem::setPath(LPCTSTR path)
	{
		//	pre:
		if(!path) 
			return;

		_releaseTasks();


		//	main:
		_push(path);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	폴더를 생성하는 API CreateDirectory를 호출한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_error NE_DLL NEFileSystem::createDirectory(LPCTSTR path) const
	{
		return (CreateDirectory(path, NE_NULL) == 0); // 에러발생시 0 반환.
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	비어있는 디렉토리를 삭제한다.
	//	동작조건:	반드시 비어있는 디렉토리여야만 한다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_error NE_DLL NEFileSystem::removeEmptyDirectory(LPCTSTR path) const
	{
		return (RemoveDirectory(path) == 0);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일을 삭제한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_error NE_DLL NEFileSystem::removeFile(LPCTSTR path) const
	{
		return (DeleteFile(path) == 0);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	NEFileSystem의 모든 멤버변수와 데이터를 초기화한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEFileSystem::release()
	{
		_releaseTasks();
		_is_search_lower_directory_too = false;
	}


	
	//	---------------------------------------------------------------------------------
	//	설명	:	특정 TaskUnit에 접근한다
	//	동작	:	LinkedList의 순차탐색
	//	동작조건:	1개 이상의 TaskUnit이 있어야 한다.
	//				TaskUnit의 갯수와 맞지않는 인덱스를 입력하면 안된다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEFileSystem::TaskUnit& NEFileSystem::_getElement(type_index index) const
	{
		NEFileSystem::TaskUnit* null_pointer = NE_NULL;
		//	pre:
		//		파라메터 검사:
		if(index < 0) return *null_pointer;
		if(index > getLastIndex()) return *null_pointer;
		//		관련 멤버변수 검사:
		if(!_header) return *null_pointer;



		//	main:	iterator를 index횟수만큼 접근한다. (부하가 크다)			
		NEFileSystem::TaskUnit* iterator = _header;

		for(type_index n=0; n < index ;n++)
		{
			iterator = iterator->_next;

			if(!iterator) return *null_pointer; // index에 접근하기 전에 먼저 끝에 도달했다. (= size보다 큰 index를 인자로 받았다 )
		}


		//	post:
		return *iterator;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	입력된 작업디렉토리에 추가로 검색해야하는 "하위폴더"가 존재하는지 
	//				검색한다
	//	동작	:	1	하위폴더를 검색하기 위한 검색경로를 따로 생성한다.
	//					작업디렉토리 + "\*.*"
	//				2	검색경로를 일단 한번 입력해본다. (FindFirstFile)
	//				3	성공했다면 (!= INVALID_HANDLE) 계속 검색을 하면서 디렉토리인지 판단한다.
	//				4	디렉토리일경우, "." 나 ".." 가 아닐경우에 새로 TaskUnit을 pushFront한다.
	//					(_whetherIsNewTaskOrNot)	
	//	동작조건:	_is_search_lower_directory_too	하위폴더 검색이 true 일 경우
	//	메모	:	pushFront를 하는 이유는, 스택구조이기 때문이다. push를 하면, 현재 작업중인
	//				Task가 중간에 위치하게 되면서 꼬여버린다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	해당 폴더의 검색은 이미 끝나있는 순간에 마지막으로 서브폴더를 검색하는 FindFirstFile를 오픈한다
	//	이 함수 안에서만 루프를 돌고, path를 없앤다
	void NEFileSystem::_findSubDirectoryFile()
	{
		//	pre:
		//		관련 멤버변수 검사:
		if(_is_search_lower_directory_too == false) return;



		//	main:
		//		새로운 검색경로 생성:	하위 폴더를 검색하기 위해 작업경로/*.*를 만든다
		//			하위폴더 검색용 경로를 생성:
		LPTSTR path_for_finding_sub_directory_null_pointer = _mergePathForFindingSubDirectory();
		if(!path_for_finding_sub_directory_null_pointer) return;			

		//		하위폴더 검색:
		NEFileSystem::TaskUnit& target = _getElement(getLastIndex());
		if( ! &target) return;

		target._file = FindFirstFile(path_for_finding_sub_directory_null_pointer, &(target._file_information));
		//			검색 종료:	버퍼 해제 한다
		delete [] path_for_finding_sub_directory_null_pointer;
		path_for_finding_sub_directory_null_pointer = NE_NULL;

		//		검색 결과:
		//			하위 디렉토리가 존재한다면:
		if(target._file != INVALID_HANDLE_VALUE)
		{	
			target._releaseFileInformation();
			//			하위디렉토리 무결성 검사:	찾은 하위디렉토리가 '.', '..' 같은 무의미한 디렉토리인지 확인한다
			while(FindNextFile(target._file, &target._file_information) != 0) // 파일이 없을경우 0이 나온다
			{

				if(	(_tcscmp(target._file_information.cFileName, _T(".")) != 0)		&& // == 0 이면 같다
					(_tcscmp(target._file_information.cFileName, _T("..")) != 0)	)
				{						
					_whetherIsNewTaskOrNot(target); // 폴더라면 task 추가
				}

			}
		}


		//	post:
		//		상태 복귀:	하위 디렉토리를 검사하기 이전 상태로 현재 작업상태를 되돌린다
		target._releaseFile();
		target._releaseFileInformation();			
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	특정 TaskUnit에 접근한다
	//	동작	:	LinkedList의 순차탐색
	//	동작조건:	1개 이상의 TaskUnit이 있어야 한다.
	//				TaskUnit의 갯수와 맞지않는 인덱스를 입력하면 안된다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEFileSystem::TaskUnit& NEFileSystem::_getElement(type_index index)
	{			
		NEFileSystem::TaskUnit* null_pointer = NE_NULL;
		//	pre:
		//		파라메터 검사:
		if(index < 0) return *null_pointer;
		if(index > getLastIndex()) return *null_pointer;
		//		관련 멤버변수 검사:
		if(!_header) return *null_pointer;



		//	main:
		NEFileSystem::TaskUnit* iterator = _header;

		for(type_index n=0; n < index ;n++)
		{
			iterator = iterator->_next;

			if(!iterator) return *null_pointer;
		}



		//	post:
		return *iterator;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	Flag인 "하위폴더검색여부"를 초기화한다
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::_releaseFlag()
	{
		_is_search_lower_directory_too = false;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일검색을 처음으로 실시한다.
	//	동작조건:	1	처음 FindFile을 실시해야한다.
	//				2	경로가 입력되어 있어야 한다.
	//	메모	:	FindFile API는, 처음 검색시에는 FindFirstFile을, 2번째 부터는 FindNextFile
	//				을 실행하도록 되어있다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::_findFirstFile()
	{
		//	pre:
		//		관련 멤버변수검사:
		if(_length <= 0) return;
		//		현재 Task 유효검사:
		//			Task 가져옴:
		NEFileSystem::TaskUnit& target = _getElement(getLastIndex());
		//			검사:
		if( ! &target) return;
		if(target._file) target._releaseFile();
		if(target._is_task_executed_at_least_once) return; // 이미 한번 실행한 경우는 그냥 종료



		//	main:
		//		하위디렉토리 검사:
		_findSubDirectoryFile(); // 일단, 해당 폴더 안에 서브폴더를 pushFront()한다.
		//		
		target._file = FindFirstFile(target._path, &(target._file_information));
		target._is_task_executed_at_least_once = true;

		if(target._file == INVALID_HANDLE_VALUE) // 핸들값이 잘못되었다면
			//	파일이 없다.
			_backtrackTask();
		else // 올바른 핸들값이 들어왔다면
		{				
			target._is_there_any_task = true;				
			target._is_fileinformation_filled_in = true;
			target._is_file_handle_valid = true;				
			_filterDottedDirectory(target); // 이 함수를 가장 마지막에 실행시켜야 한다. 이 함수에서 현재 task를 pop 할수가 있기 때문이다.				
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	계속 파일검색을 수행한다.
	//	동작조건:	처음 파일검색을 수행했고(findfile), INVALID_HANDLE이 나오지 않았어야 한다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::_findNextFile()
	{
		//	pre:
		//		관련 멤버함수 검사:
		if(_length <= 0) return;
		//		현재 Task 유효검사:
		//			Task 가져옴:
		TaskUnit& target = _getElement(getLastIndex());
		//			Task 검사:
		if( ! &target) return;
		if( !(target._file) ) return;
		if( ! target._is_task_executed_at_least_once) return;



		//	main:	파일 정보를 가져옴
		//		버퍼 초기화:
		target._releaseFileInformation();
		//		파일 가져옴:
		if(FindNextFile(target._file, &target._file_information) == NE_ERROR_0)
		{	//		조건1:	에러가 발생했다면
			_backtrackTask();
		}
		else
		{	//		조건2:	에러 없다면, 현재 파일명을 보존하고 복귀한다.
			//			하위 디렉토리 여부 판단:	가져온 파일정보가 디렉토리인가? (= 새롭게 하위 디렉토리를 검색해야 하는가? )
			_whetherIsNewTaskOrNot(target);
			//			파일명 합산:	target._file_path에 _work_directory와 filename이 합쳐저 최종적으로 들어간다.
			target._mergeFileName();
			target._mergeFilePath();			
			//			상태변수 변경:
			target._is_there_any_task = true; // 파일 끝에 도달하지 않았다.
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	이전 작업으로 돌아간다.
	//	동작	:	현재 작업인 TaskUnit을 비운다(_pop) 그리고 findFile에서 lastElement로
	//				검색을 수행하므로, 자동으로 작업이 스위칭된다.
	//	동작조건:
	//	메모	:	그냥 POP만 하면, 사용자입장에서는 매 작업스위칭때마다 findFile을 2번 
	//				호출해야하는 결과가 생긴다. 그래서 _backtrackTask시 findFile을 수행함.
	//				이전 Task를 한번진행시켜서 다음파일을 검색해야한다. 
	//				그래야 1회분의 분량(파일이름)이 나오니까. 만약 다음파일을 찾지 않으면
	//				유저는 같은파일명만 2번 내보내는 셈이된다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	void NEFileSystem::_backtrackTask()
	{
		_pop();
		findFile(); 
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	현재 검색한 파일이 . 혹은 .. 인 파일명인지 판단한다.
	//				만약 이런 필터링을 거치지 않을 경우, *.* 검색에서는 항상 "." 와 ".."가
	//				먼저 나오게 되어버린다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::_filterDottedDirectory(TaskUnit& target)
	{
		//	main:
		//		조건1:	대상의 filename이 '.', '..' 인가?
		if(	(_tcscmp(target._file_information.cFileName, _T(".")) == 0)	|| // == 0 이면 같다
			(_tcscmp(target._file_information.cFileName, _T("..")) == 0)	)
		{
			//		'.', '..' 스킵:
			while(	(_tcscmp(target._file_information.cFileName, _T(".")) == 0)	||
				(_tcscmp(target._file_information.cFileName, _T("..")) == 0)	)
			{
				//		스킵:	파일 정보를 계속 가져옴
				//			버퍼초기화:
				target._releaseFileInformation();
				//			버퍼에 정보 기록:
				//				조건1-1:	검색중 에러 발생
				if(FindNextFile(target._file, &target._file_information) == NE_ERROR_0)
				{	//				이전 Task로 복귀:						
					_backtrackTask();

					return;
				}
				else
				{	//				에러 없음:						
					target._is_there_any_task = true;					
				}
			}
			//		스킵완료:	검색후, 성공적으로 폴더 제거됨
			//					찾은 결과물로 filepath 생성:
			target._mergeFileName();
			target._mergeFilePath();			
			//			하위 디렉토리 여부 판단:	그런데, 찾은 결과물이 하위디렉토리라면 다시 새로운 Task를 추가.
			_whetherIsNewTaskOrNot(target);		

		}
		else
		{	//	조건2:	애초에 검색을 하지 않은 경우
			target._mergeFileName();
			target._mergeFilePath();
		}

	}



	//	---------------------------------------------------------------------------------
	//	설명	:	검색한 파일명과 해당 TaskUnit의 작업디렉토리를 합쳐서(merge) 검색한
	//				파일의 경로를 동적할당으로 생성한다.
	//	동작조건:	해당 TaskUnit를 최소한 한번이상 실행하고, 정상적으로 파일을 검색한 경우
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	LPTSTR NEFileSystem::_mergeNewPath(const TaskUnit& target) const
	{
		//	pre:
		//		파라메터 검사:
		//			대상 Task:
		if( !(target._file) ) return NE_NULL;
		if( !(target._work_directory) ) return NE_NULL;
		if( !(target._path) ) return NE_NULL;
		if( !(target._file_information.cFileName) ) return NE_NULL;



		//	main:
		//		와일드 카드 추출:
		//			와일드카드버퍼 포인터 생성:
		LPTSTR wildcard = target._getWildcard(); // 내부에서 동적생성한다. 그러므로 외부에서 메모리 반환시켜야 한다.				
		//			무결성 검사:
		if(!wildcard) return NE_NULL; // validcheck

		//		최종버퍼에 저장:	기존 작업 경로 + 찾아낸 하위디렉토리 + 와일드카드 + 널문자
		//			길이 정보 변수 정의:
		type_index	work_directory_length	= _tcslen(target._work_directory),
					directory_name_length	= _tcslen(target._file_information.cFileName), // 찾아낸 파일이 디렉토리였다
					wildcard_length			= _tcslen(wildcard),
					full_length				= work_directory_length + directory_name_length + wildcard_length + 1;
		//			최종버퍼 생성:
		LPTSTR buffer = new TCHAR[full_length + 1];
		//			최종버퍼에 값 축적:
		//				작업경로:
		_tcscpy_s(buffer, _tcslen(target._work_directory) + 1, target._work_directory); // work_directory는 최소한 "\"를 갖는다
		//				하위디렉토리:
		if(directory_name_length > 0)
		{
			_tcscat_s(buffer, full_length + 1, target._file_information.cFileName);
			_tcscat_s(buffer, full_length + 1, _T("\\"));
		}
		//				와일드카드:
		if(wildcard_length > 0)
			_tcscat_s(buffer, full_length + 1, wildcard);



		//	post:	전에 생성했던 와일드카드버퍼 해제			
		delete [] wildcard;
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	하위폴더를 검색하기위한 검색경로를 생성한다.
	//	동작조건:
	//	메모	:	동적할당되어서 외부로 반환된다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	LPTSTR NEFileSystem::_mergePathForFindingSubDirectory()
	{
		//	pre:
		//		파라메터 검사:
		LPTSTR buffer = NE_NULL;



		//	main: 작업경로(_work_directory)에 와일드카드(*.*)를 붙인다.			
		//		작업할 대상을 가져옴:
		NEFileSystem::TaskUnit& target = _getElement(getLastIndex());
		if( ! & target) return NE_NULL;
		//		주어진 포인터로 버퍼 생성:
		type_index length = _tcslen(target._work_directory) + 3; // 3은 "*.*"
		buffer = new TCHAR[length + 1];
		memset(reinterpret_cast<void*>(buffer), NE_NULL, (length + 1) * sizeof(TCHAR));
		//		복사:
		_tcscpy_s(buffer, _tcslen(target._work_directory) + 1, target._work_directory);			
		_tcscat_s(buffer, length + 1, _T("*.*"));

		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 TaskUnit가 가지고 있는 "파일명"과 "파일정보"를 통해서
	//				추가적으로 검색해야하는 하위디렉토리인지를 판단하고,
	//				하위디렉토리일 경우에는 새로운 TaskUnit을 PushFront 한다.
	//	동작조건:	
	//	메모	:	1	하위폴더 검색 Flag를 검사하지는 않는다. 하위폴더 검색 검사를 통과
	//					한 시점에서만 이 함수가 호출되기 때문이다.
	//				2	pushFront를 하는 이유는, TaskUnit이 스택 구조로 되어있기 때문.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	새로얻은 파일명이 디렉토리인지 확인한다.
	//	디렉토리일 경우, 플래그가 켜졌으면 새로운 태스크를 생성한다.
	void NEFileSystem::_whetherIsNewTaskOrNot(NEFileSystem::TaskUnit& target)
	{
		//	새로운 태스크 생성:	찾은 하위 디렉토리를 _path로 가지고 있는 target를 이용한다
		//		디렉토리 확인:	찾은 정보가 디렉토리인가?
		if(target._file_information.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // 비트다룰때는 ==가 아니라 &임을 잊지말라
		{
			//	태스크 추가:	디렉토리찾으면, 나중에 검색하기 위해서 task를 생성한다
			//		새로운 경로 생성:
			LPTSTR buffer = NE_NULL;
			buffer = _mergeNewPath(target);
			if(!buffer) return;
			//		추가:	스택에 TaskUnit(LPCTSTR)의 형태로 추가된다
			_pushFront(buffer); // 작업을 예약 한다. 현재 작업이 끝나면 추가한 하위 디렉토리로 이동할 것이다
			//		메모리 해제:
			delete [] buffer;				
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	새로운 TaskUnit(검색 작업)을 추가한다.
	//	동작	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::_push(LPCTSTR new_path)
	{
		if(getLength() == 0) 
		{
			_header = new NEFileSystem::TaskUnit(new_path);
			_length++;
		}
		else
		{
			_getElement(getLastIndex())._next = new NEFileSystem::TaskUnit(new_path);
			_length++;
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	새로운 TaskUnit을 앞에 추가한다 (스택구조로 보면 제일 밑에)
	//	동작	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::_pushFront(LPCTSTR new_path)
	{
		if(getLength() == 0) 
		{
			_header = new NEFileSystem::TaskUnit(new_path);
			_length++;
		}
		else
		{
			NEFileSystem::TaskUnit* newbie = new NEFileSystem::TaskUnit(new_path);
			newbie->_next = _header;
			_header = newbie;
			_length++;
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	가장 뒤에 있는 (스택 구조에서는 위에 있는) TaskUnit를 하나 없앤다.
	//				소멸자를 통해 메모리 할당도 해제한다.
	//	동작조건:	TaskUnit이 1개 이상 존재
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::_pop()
	{
		if(getLength() == 0) return;
		if(getLength() == 1) 
		{
			delete _header;
			_header = NE_NULL;
			_length = NE_NULL;
		}
		else
		{
			//	마지막 작업을 삭제:	메모리해제를 위해, 마지막 바로 전 Task의 next를 가져와야 한다
			//		마지막 전 Task:
			NEFileSystem::TaskUnit& last_onestep_before = _getElement(getLastIndex() - 1);
			//		해제:
			delete last_onestep_before._next; // TaskManager <--- Friend(= open to ) ---- TaskUnit
			last_onestep_before._next = NE_NULL;
			//		길이 동기화:
			_length--;
		}
	}

	const NEFileSystem::TaskUnit NE_DLL &NEFileSystem::operator[](type_index index) const
	{
		return _getElement(index);
	}

	const NEFileSystem::TaskUnit NE_DLL &NEFileSystem::getElement(type_index index) const
	{
		return _getElement(index);
	}

	bool NE_DLL NEFileSystem::isSearchLowerDirectory() const
	{
		return _is_search_lower_directory_too;
	}

	void NE_DLL NEFileSystem::setSearchLowerDirectory(bool search_lower_directory)
	{
		_is_search_lower_directory_too = search_lower_directory;
	}

	const NEFileSystem::TaskUnit& NEFileSystem::getLastElement() const
	{
		return _getElement(getLastIndex());
	}

	void NEFileSystem::_releaseTasks()
	{
		while(getLength())
			_pop();
	}
}
