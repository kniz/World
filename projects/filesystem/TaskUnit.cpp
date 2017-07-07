#include "NEFileSystem.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	설명	:	생성자
	//	동작	:	1	멤버변수를 초기화 시킨다(set null)
	//				2	path를 입력한다. (setPath)
	//	동작조건:	NEFileSystem의 setPath() 혹은, NEFileSystem(path) 가 먼저 실행되어야 한다
	//	인자값	:	LPCTSTR path	검색할 경로. 경로를 입력할때 C:\\data\\... 혹은 C:/data/... 
	//								의 형태로 사용해야한다.	
	//	메모	:	1	외부에 직접적으로 노출되지 않는다(NEFileSystem에서만 사용되는 클래스)
	//				2	기본생성자( TaskUnit(void) )는 존재하지 않는다
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEFileSystem::TaskUnit::TaskUnit(LPCTSTR path)
		:	_path(NE_NULL), _filepath(NE_NULL), _work_directory(NE_NULL), _filename(NE_NULL),
		_file(NE_NULL), _file_information(), _next(NE_NULL)
	{
		_release();

		setPath(path);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	소멸자
	//	동작	:	모든 멤버변수를 메모리에서 해제한다
	//	동작조건:	인스턴스 소멸시 자동으로 동작	
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEFileSystem::TaskUnit::~TaskUnit()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	멤버변수 path의 접근자 함수
	//	동작	:	현재 경로(path)를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	LPCTSTR NE_DLL NEFileSystem::TaskUnit::getPath() const
	{
		return _path;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	멤버변수 _work_directory의 접근자 함수
	//	동작	:	현재 작업디렉토리를 반환한다.
	//	동작조건:		
	//	메모	:	작업디렉토리란?	
	//					:	현재 검색이 이루어지고 있는 디렉토리를 말한다. 다음과 같은 용도로
	//						사용한다.
	//						1	현재 검색한 파일명과 합쳐서 절대 경로를 생성한다
	//						2	검색도중 하위폴더가 존재할 경우, 작업디렉토리 + 폴더명으로 통해
	//							새로운 절대검색경로(path)를 생성한다
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	LPCTSTR NE_DLL NEFileSystem::TaskUnit::getWorkDirectory() const
	{
		return _work_directory;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	멤버변수 _filepath의 접근자 함수
	//	동작	:	현재 검색된 파일의 절대경로(_filepath)를 반환한다
	//	동작조건:	최소한 한번 findfile()를 실시해 파일을 검색하지 않으면 null이 나올것이다.
	//				findfile()을 해도 파일이 존재하지 않는다면 역시 null이 나온다
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	LPCTSTR NE_DLL NEFileSystem::TaskUnit::getFilePath() const
	{
		return _filepath;
	}



	LPCTSTR NE_DLL NEFileSystem::TaskUnit::getFileName() const
	{
		return _filename;
	}
	
	
	
	bool NE_DLL NEFileSystem::TaskUnit::isFileHandelValid() const
	{
		return _is_file_handle_valid;
	}

	bool NE_DLL NEFileSystem::TaskUnit::isPathInputted() const
	{
		return _is_path_inputted;
	}

	bool NE_DLL NEFileSystem::TaskUnit::isTaskExecutedAtLeastOnce() const
	{
		return _is_task_executed_at_least_once;
	}

	bool NE_DLL NEFileSystem::TaskUnit::isThereAnyTask() const
	{
		return _is_there_any_task;
	}

	bool NE_DLL NEFileSystem::TaskUnit::isFileInformationFilledIn() const
	{
		return _is_fileinformation_filled_in;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	멤버변수 _file_information의 접근자 함수
	//				검색한 파일의 파일정보를, Windows.h의 WIN32_FIND_DATA의 포맷으로 넘겨준다.
	//	동작	:	현재 검색된 파일의 정보 _file_information를 반환한다
	//	동작조건:	최소한 한번 findfile()를 실시해 파일을 검색하지 않으면 null이 나올것이다.
	//				findfile()을 해도 파일이 존재하지 않는다면 역시 null이 나온다
	//	메모	:	WIN32_FIND_DATA는 본 파일의 최상단 헤더를 참고	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const WIN32_FIND_DATA NE_DLL & NEFileSystem::TaskUnit::getFoundFileInformation() const
	{
		return _file_information;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	경로에서 Wildcard를 추출한다. (c:\\data\\*.da?)를 입력한 경우, *.da?를 추출한다.
	//	동작	:	argument를 버퍼로 사용, _path로부터 wildcard를 추출해서 argument에 담는다.
	//	알고리즘:	1	가장 뒤에 위치한 "\" 나 "/"의 인덱스를 찾는다. 그 뒤가 wildcard가
	//					될것이다.(_findSlash)
	//				2	비워놓은 버퍼(buffer_null_pointer)를 동적할당해서, 하나씩 복사한다.
	//				3	마지막에 '\0'을 붙인다.
	//	동작조건:	setPath를 통해, path가 입력되어야 한다.
	//	인자값	:	LPTSTR* buffer_null_pointer	
	//					:	NE_OUT에서 볼 수 있듯이 외부에 반환하기 위해서 사용한다.
	//						반환값을 LPTSTR* 할수도 있으나, 반환된 LPTSTR*를 외부에서
	//						눈치채지 못하고 버리는 경우를 피하기 위해 인자로 받았다.	
	//	메모	:	NE_OUT은 외부에 반환되는 (영향을 미치는) 인자를 의미한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	LPTSTR NE_DLL NEFileSystem::TaskUnit::_getWildcard() const
	{
		//	pre:
		//		관련멤버함수 검사:
		if(!_path) return NE_NULL;



		//	main:
		//		초기화:
		//			변수:
		type_index index_of_slash = _findSlash(_path);
		type_index length = _tcslen(_path);
		type_index wildcard_length = length - (index_of_slash + 1); // 순수한 wildcard의 길이
		LPTSTR buffer = NE_NULL;
		//			동적할당:
		buffer = new TCHAR[wildcard_length + 1]; // wildcard + 널문자1
		memset(buffer, NE_NULL, (wildcard_length + 1) * sizeof(TCHAR));

		//		동작:
		//			실제 데이터 복사:
		for(type_index n=0, path_index=index_of_slash + 1; path_index < length ;n++, path_index++)
			buffer[n] = _path[path_index];
		//			널문자 추가:
		buffer[wildcard_length] = _T('\0');

		return buffer;
	}
	
	

	void NEFileSystem::TaskUnit::_releaseFlags()
	{
		_is_file_handle_valid = false;
		_is_path_inputted = false;
		_is_task_executed_at_least_once = false;
		_is_there_any_task = false;
		_is_fileinformation_filled_in = false;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	경로를 입력받는다
	//	동작	:	입력받은 경로를 _path에 할당하고, 작업디렉토리를 변경한다(_pickWorkDirectory)
	//	동작조건:		
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEFileSystem::TaskUnit::setPath(LPCTSTR new_path)
	{
		//	pre:
		//		파라메터 검사:
		if(!new_path) return;
		//		관련 멤버변수 검사:
		_release();



		//	main:
		//		준비과정:	new_path를 담기위해 _path 멤버변수의 버퍼를 생성한다.
		type_index length = _tcslen(new_path);	
		_path = new TCHAR[length + 1]; // length+1은 _path의 글자수. 거기에 널문자를 더해서 +2
		memset(reinterpret_cast<void*>(_path), NE_NULL, (length + 1) * sizeof(TCHAR));
		//		복사:
		_tcscpy_s(_path, length + 1, new_path); // assign


		//	post:
		//		새로운 경로의 작업경로추출:		
		_pickWorkDirectory(new_path);
		//		파일경로:	path를 그대로 복사한다.
		_filepath = new TCHAR[length + 1];
		memset(reinterpret_cast<void*>(_filepath), NE_NULL, (length + 1) * sizeof(TCHAR));
		_tcscpy_s(_filepath, length + 1, _path);
		//		파일이름:	와일드카드를 그대로 파일이름으로 한다.
		_mergeFileName();
		//		스테이터스 갱신:
		_is_path_inputted = true;
	}		

	//	---------------------------------------------------------------------------------
	//	설명	:	작업디렉토리의 접근자 함수	
	//	동작조건:	
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_setWorkDirectory(LPCTSTR work_directory)
	{
		//	pre:
		//		파라메터 검사:		
		if(!work_directory) return;
		//		관련 멤버변수 초기화:
		if(_work_directory) _releaseWorkDirectory();



		//	main:
		//		준비과정:
		type_index length = _tcslen(work_directory);
		_work_directory = new TCHAR[length + 1]; // 널문자 + 1
		memset(reinterpret_cast<void*>(_work_directory), NE_NULL, (length + 1) * sizeof(TCHAR));
		//		복사:
		_tcscpy_s(_work_directory, length + 1, work_directory);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_mergeFileName()
	{
		//	pre:
		//		관련멤버변수 검사:
		if(!_work_directory) return;		
		//		관련멤버함수 초기화:
		_releaseFileName();



		//	main:
		//		findfile 미 실행시:
		if(	!_file_information.cFileName						||
			_tcscmp(_file_information.cFileName, _T("")) == 0	)
			_filename = _getWildcard();
		else//	findfile 실행시:
		{
			//		fileinformation으로 filename merge:
			//			멤버변수의 버퍼 준비:
			//				길이 구하기:
			type_index filename_length = _tcslen(_file_information.cFileName);
			//				버퍼생성:
			_filename = new TCHAR[filename_length + 1];  // + 1 은 널문자.
			//				버퍼 초기화:
			memset(reinterpret_cast<void*>(_filename), NE_NULL, (filename_length + 1) * sizeof(TCHAR));
			//		복사:			
			_tcscat_s(_filename, filename_length + 1, _file_information.cFileName);
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	파일명과 작업디렉토리를 합쳐서 절대경로를 생성한다.
	//	동작조건:	1	파일을 성공적으로 검색해야한다.
	//				2	작업디렉토리가 존재해야한다 (setPath로 경로 입력)
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_mergeFilePath()
	{
		//	pre:
		//		관련멤버변수 검사:
		if(!_work_directory) return;
		if( !(_file_information.cFileName) ) return;
		//		관련멤버함수 초기화:
		_releaseFilePath();



		//	main:
		//		멤버변수의 버퍼 준비:
		//			길이 구하기:
		type_index filename_length = _tcslen(_filename);			
		type_index work_directory_length = _tcslen(_work_directory); // work_directory는 비어있는 경우가 없다. 적어도 "/"는 갖고 있음
		//			버퍼생성:
		type_index length = work_directory_length + filename_length;
		_filepath = new TCHAR[length + 1];
		memset(reinterpret_cast<void*>(_filepath), NE_NULL, (length + 1) * sizeof(TCHAR));
		//		복사:
		_tcscpy_s(_filepath, work_directory_length + 1, _work_directory);
		_tcscat_s(_filepath, work_directory_length + filename_length + 1, _filename);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	입력한 경로에서 작업디렉토리를 추출한다
	//	동작조건:		
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_pickWorkDirectory(LPCTSTR path)
	{
		//	pre:
		//		관련 멤버변수 초기화:
		_releaseWorkDirectory();



		//	main:
		//		작업경로의 끝부분 찾기:	구분자('/', '\\')의 인덱스를 검색
		type_index index_of_slash = _findSlash(path);

		//		부분복사:
		//			조건1:	구분자가 없는 경우:
		if(index_of_slash == NE_INDEX_ERROR)
		{
			//			작업경로를 ".\\"로 설정:
			_work_directory = new TCHAR[3];
			_tcscpy_s(_work_directory, 3, _T(".\\"));
		}
		else //		조건2: 찾았다면:
		{ 
			//			존재하는 경우, / 이하를 작업폴더로 지정:
			//				작업경로의 버퍼생성:
			_work_directory = new TCHAR[index_of_slash + 2]; // index는 /의 위치. 0~index까지는 index+1글자. 거기에 널문자를 넣어야 하므로 +2
			memset(reinterpret_cast<void*>(_work_directory), NE_NULL, (index_of_slash + 2 ) * sizeof(TCHAR));
			//				복사:
			for(type_index n=0; n <= index_of_slash ;n++) // 끝에 slash까지 넣는다
				_work_directory[n] = _path[n];
			//				끝에 널문자 표시:
			_work_directory[index_of_slash + 1] = _T('\0');
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	모든 멤버변수를 초기화한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_release()
	{
		if(_path)
			delete [] _path;
		_path = NE_NULL;

		_releaseFlags();
		_releaseFilePath();
		_releaseFileName();
		_releaseWorkDirectory();
		_releaseFileInformation();	
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	검색한 파일정보를 관리하는 멤버변수인 _file_information)을 초기화한다.
	//	동작조건:
	//	메모	:	memset을 사용한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_releaseFileInformation()
	{
		memset(static_cast<void*>(&_file_information), 0, sizeof(_file_information));
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	작업디렉토리를 관리하는 _work_directory를 메모리 할당을 해제한다
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_releaseWorkDirectory()
	{
		if(_work_directory)
			delete [] _work_directory;			
		_work_directory = NE_NULL;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	FindFile API의 식별자를 초기화한다.
	//	동작조건:
	//	메모	:	API FindClose를 사용한다
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_releaseFile()
	{
		if(_file)
			FindClose(_file);
		_file = NE_NULL;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	검색 파일 경로를 관리하는 멤버변수인 _filepath를 메모리할당에서 해제
	//				한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_releaseFilePath()
	{
		if(_filepath)
			delete [] _filepath;			
		_filepath = NE_NULL;
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-20	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEFileSystem::TaskUnit::_releaseFileName()
	{
		if(_filename)
			delete [] _filename;

		_filename = NE_NULL;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	입력받은 문자열(경로) 중, 가장 뒤쪽에 존재하는 슬래쉬 '\' 혹은 '/'의
	//				인덱스를 반환한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_index NEFileSystem::TaskUnit::_findSlash(LPCTSTR path) const
	{
		//	pre:
		//		파라메터검사:
		if(!path) return NE_INDEX_ERROR;



		//	main:
		//		구분자('/', '\\') 검사:
		type_index path_length = _tcslen(path);

		for(type_index index = path_length; index > 0 ;index--) // _tcslen은 널문자는 제외한다
		{
			if(path[index] == _T('\\') || path[index] == _T('/'))
				return index; // 찾으면 바로 리턴한다
		}


		//	post: 결국 찾지 못했음
		//		에러 리턴:
		return NE_INDEX_ERROR; // 인덱스이므로 0을 리턴하지 않고 -1(IS_ERROR_MINUS)를 리턴한다. 실제로 마지막에 \ 가 있을수도 있기 때문이다
	}
}