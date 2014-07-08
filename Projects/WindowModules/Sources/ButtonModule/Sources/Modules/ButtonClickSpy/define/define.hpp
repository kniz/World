#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"ButtonClickSpy"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 // 커널에서 판별하는 버전표기
#		define _VERSION					"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT					"0번 셀렉터에서 1번 가져온 윈도우모듈과 1번 셀렉터에서 1번 가져온 버튼 모듈로부터 2번키의 이벤트가 발생했다면 true를 반환합니다"
#		define	_DATE					"2012-05-05"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				3

#		define _DEFAULT_NOTIFICATION	BN_CLICKED
#	else
#		define _NAME					"ButtonClickSpy"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 // 커널에서 판별하는 버전표기
#		define _VERSION					"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT					"0번 셀렉터에서 1번 가져온 윈도우모듈과 1번 셀렉터에서 1번 가져온 버튼 모듈로부터 2번키의 이벤트가 발생했다면 true를 반환합니다"
#		define	_DATE					"2012-05-05"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				3

#		define _DEFAULT_NOTIFICATION	BN_CLICKED
#	endif
#else
#	define _NAME						"ButtonClickSpy"
#	define _DEVELOPER					"haku"
#	define _REVISION					1 // 커널에서 판별하는 버전표기
#	define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#	define _COMMENT						"0번 셀렉터에서 1번 가져온 윈도우모듈과 1번 셀렉터에서 1번 가져온 버튼 모듈로부터 2번키의 이벤트가 발생했다면 true를 반환합니다"
#	define	_DATE						"2012-05-05"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					3

#	define _DEFAULT_NOTIFICATION		BN_CLICKED
#endif