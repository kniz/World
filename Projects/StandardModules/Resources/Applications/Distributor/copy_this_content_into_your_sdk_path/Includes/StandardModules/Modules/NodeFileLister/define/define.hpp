#define _WILL_SEARCH_SUB_DIRECTORY	0x01	//	0000 0001
#define _GET_FILENAME_ONLY			0x02	//	0000 0010

#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"NodeFileLister.dev.dbg"
#		define _DEVELOPER				"haku"
#		define _REVISION				1
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"노드데이터가 저장된 폴더의 모든 노드데이터 목록을 1번키에 입력한다.\n0번키는 옵션을 담당하는데 그 내용은 다음과 같다.\n\t1 포함시 : 하위디렉토리도 검사\n\t2 포함시 : 파일명만 가져옴. 2 없을시에는 파일의 경로 전부를 가져온다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				2
#	else
#		define _NAME					"NodeFileLister.dev"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"노드데이터가 저장된 폴더의 모든 노드데이터 목록을 1번키에 입력한다.\n0번키는 옵션을 담당하는데 그 내용은 다음과 같다.\n\t1 포함시 : 하위디렉토리도 검사\n\t2 포함시 : 파일명만 가져옴. 2 없을시에는 파일의 경로 전부를 가져온다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				2
#	endif
#else
#	define _NAME						"NodeFileLister"
#	define _DEVELOPER					"haku"
#	define _REVISION					1
#	define _VERSION						"0.0.1a"
#	define _COMMENT						"노드데이터가 저장된 폴더의 모든 노드데이터 목록을 1번키에 입력한다.\n0번키는 옵션을 담당하는데 그 내용은 다음과 같다.\n\t1 포함시 : 하위디렉토리도 검사\n\t2 포함시 : 파일명만 가져옴. 2 없을시에는 파일의 경로 전부를 가져온다."
#	define	_DATE						"2012-04-14"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					2
#endif
