#define _WILL_SEARCH_SUB_DIRECTORY	0x01	//	0000 0001
#define _GET_FILENAME_ONLY			0x02	//	0000 0010

#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"FileLister.dev.dbg"
#		define _DEVELOPER				"haku"
#		define _REVISION				1
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"0번키에 입력된 경로에 존재하는 모든 파일명 혹은 경로를 2번키에 입력한다.\n1번키는 옵션을 담당하는데 그 내용은 다음과 같다.\n\t1 포함시 : 하위디렉토리도 검사\n\t2 포함시 : 파일명만 가져옴. 2 없을시에는 파일의 경로 전부를 가져온다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				3
#	else
#		define _NAME					"FileLister.dev"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"0번키에 입력된 경로에 존재하는 모든 파일명 혹은 경로를 2번키에 입력한다.\n1번키는 옵션을 담당하는데 그 내용은 다음과 같다.\n\t1 포함시 : 하위디렉토리도 검사\n\t2 포함시 : 파일명만 가져옴. 2 없을시에는 파일의 경로 전부를 가져온다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				3
#	endif
#else
#	define _NAME						"FileLister"
#	define _DEVELOPER					"haku"
#	define _REVISION					1
#	define _VERSION						"0.0.1a"
#	define _COMMENT						"0번키에 입력된 경로에 존재하는 모든 파일명 혹은 경로를 2번키에 입력한다.\n1번키는 옵션을 담당하는데 그 내용은 다음과 같다.\n\t1 포함시 : 하위디렉토리도 검사\n\t2 포함시 : 파일명만 가져옴. 2 없을시에는 파일의 경로 전부를 가져온다."
#	define	_DATE						"2012-04-14"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					3
#endif
