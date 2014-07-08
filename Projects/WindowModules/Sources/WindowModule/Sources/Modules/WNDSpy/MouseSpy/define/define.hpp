#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME						"MouseSpy.dev.dbg"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"0번. 윈도우모듈\n1번. 메세지종류(512:MOUSEMOVE, 513:LBUTTON_DOWN, 514:LBUTTON_UP, 515:LBUTTON_DBLCLK, 516:RBUTTON_DOWN, 517:RBUTTON_UP, 518:RBUTTON_DBLCLK 등등)\n2번. OUT X좌표 저장\n3번. OUT Y좌표 저장"
#		define	_DATE						"2012-04-16"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					4
#	else
#		define _NAME						"MouseSpy"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						""
#		define	_DATE						"2012-04-16"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					4
#	endif
#else
#	define _NAME							"MouseSpy"
#	define _DEVELOPER						"haku"
#	define _REVISION						1 // 커널에서 판별하는 버전표기
#	define _VERSION							"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#	define _COMMENT							""
#	define	_DATE							"2012-04-16"
#	define _DEPENDENCIES_COUNT				0
#	define _KEY_NUMBER						4
#endif

