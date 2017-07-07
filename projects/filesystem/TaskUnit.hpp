//	---------------------------------------------------------------------------------
//	클래스명:	TaskUnit
//	설명	:	NEFileSystem의 Task를 담당한다.
//	관계	:	NEFileSystem의 내부 클래스
//	특성	:	1	NEFileSystem과 friend관계다.
//				2	선언과 정의가 하나의 파일에 이루어진다.
//					컴파일시 "인라인 명령"을 선언하지 않으므로 각 멤버함수는 인라인 
//					함수는 아니다.
//	알고리즘:	파일 검색시, CRT 명령으로는 하위폴더를 검색하지 못한다. 그래서 "해당 
//				폴더를 검색한다"고 하는 Task란 개념을 만들어서, 하위폴더가 발견되면
//				해당 폴더로 Task를 추가	시킨다. 
//				때문에, 실질적인 검색이 이루어지는 곳은 TaskUnit 클래스라고 할 수 
//				있다.
//	사용방법:	NEFileSystem 클래스를 참고하라
//	메모	:	WIN32_FIND_DATA 포맷이란?
//					+ 구조
//						typedef struct _WIN32_FIND_DATA 
//						{ 
//							DWORD dwFileAttributes; 
//							FILETIME ftCreationTime; 
//							FILETIME ftLastAccessTime; 
//							FILETIME ftLastWriteTime; 
//							DWORD nFileSizeHigh; 
//							DWORD nFileSizeLow; 
//							DWORD dwOID; 
//							TCHAR cFileName[MAX_PATH]; 
//						} WIN32_FIND_DATA; 
//
//					+ 설명
//						dwFileAttributes	:	파일의 속성을 알려준다. 다음과 같은 종류가 있다.
//							FILE_ATTRIBUTE_ARCHIVE		
//							FILE_ATTRIBUTE_COMPRESSED	
//							FILE_ATTRIBUTE_DIRECTORY	디렉토리일 경우
//							FILE_ATTRIBUTE_ENCRYPTED	
//							FILE_ATTRIBUTE_HIDDEN		
//							FILE_ATTRIBUTE_INROM		Rom안에 있는 파일일때
//							FILE_ATTRIBUTE_NORMAL		아무런 속성이 없을때
//							FILE_ATTRIBUTE_READONLY		
//							FILE_ATTRIBUTE_REPARSE_POINT
//							FILE_ATTRIBUTE_ROMMODULE	
//							FILE_ATTRIBUTE_ROMSTATICREF	
//							FILE_ATTRIBUTE_SPARSE_FILE	
//							FILE_ATTRIBUTE_SYSTEM		
//							FILE_ATTRIBUTE_TEMPORARY	
//						ftCreationTime		:	파일이 생성된 시각 FILETIME의 형태로 반환된다.
//						ftLastAccessTime	:	최근 접근 시간
//						ftLastWriteTime		:	최근 작성 시간
//						nFileSizeLow		:	파일의 크기를 바이트로 표현한다. DWORD이므로 약 4GB가 표현가능하다.
//						nFileSizeHigh		:	4GB 이후의 크기를 기록한다. 만약, 4GB + 1이라면, nFileSizeHigh값은 1이 될것이다.
//												최종 파일크기는  (nFileSizeHigh * MAXDWORD+1) + nFileSizeLow 가 된다.
//						dwOID				:	파일의 식별자
//						cFileName			:	파일명
//
//				파일검색에 API를 사용		=	FirstFindFile, NextFindFile
//				문자열 다루는데 CRT 사용	=	_tcscpy, _tcscat, strlen
//	히스토리:	2011-05-29	이태훈	개발 완료
//	--------------------------------------------------------------------------------
class NE_DLL TaskUnit
{				
	//	프렌드 선언:
public:
	friend class NEFileSystem;

	//	생성자:
public:
	TaskUnit(LPCTSTR path);

	//	소멸자:
public:
	~TaskUnit();

	//	접근자:
public:
	LPCTSTR getPath() const;
	LPCTSTR getWorkDirectory() const;
	LPCTSTR getFilePath() const;
	LPCTSTR getFileName() const;
	const WIN32_FIND_DATA& getFoundFileInformation() const;
	bool isFileHandelValid() const;
	bool isPathInputted() const;
	bool isTaskExecutedAtLeastOnce() const;
	bool isThereAnyTask() const;
	bool isFileInformationFilledIn() const;

	//	인터페이스:
public:	
	void setPath(LPCTSTR new_path);
	
	//	내부함수:
private:
	LPTSTR _getWildcard() const;
	void _setWorkDirectory(LPCTSTR work_directory);
	void _mergeFileName();
	void _mergeFilePath();
	void _pickWorkDirectory(LPCTSTR path);
	void _release();
	void _releaseFlags();
	void _releaseFileInformation();
	void _releaseWorkDirectory();
	void _releaseFile();
	void _releaseFilePath();
	void _releaseFileName();
	type_index _findSlash(LPCTSTR path) const;

	//	멤버변수:
protected:
	//		Flag:
	bool _is_file_handle_valid;
	bool _is_path_inputted;
	bool _is_task_executed_at_least_once;
	bool _is_there_any_task;
	bool _is_fileinformation_filled_in;
	//		외부에 출력하기 위해 두는 멤버변수
	LPTSTR _path;
	LPTSTR _filepath;
	LPTSTR _work_directory;
	LPTSTR _filename;
	//		실제로 사용하는 멤버변수
	HANDLE _file;
	WIN32_FIND_DATA _file_information;
	TaskUnit* _next;
};