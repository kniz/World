#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME						"WNDDomainManipulator.dev.dbg"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"0번셀렉터로 추출되는 모든 WND모듈의 크기를(2번키:x, 3번키:y, 4번키:width, 5번키:height)로 적용합니다.\n1번키로는 윈도우를 이동하고 나서 앞에다 놓을지 뒤에다 놓을지 정할수 있습니다.\n6번키로는 움직이고 난후의 윈도우의 상태를 결정할 수 있습니다."
#		define	_DATE						"2012-05-03"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					7

#		define _DEFAULT_X					100
#		define _DEFAULT_Y					100
#		define _DEFAULT_WIDTH				100
#		define _DEFAULT_HEIGHT				100
#		define _DEFAULT_HWND_INSERTED_AFTER	0 // HWND_TOP
#		define _DEFAULT_FLAG				SWP_SHOWWINDOW
#	else
#		define _NAME						"WNDDomainManipulator"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"0번셀렉터로 추출되는 모든 WND모듈의 크기를(2번키:x, 3번키:y, 4번키:width, 5번키:height)로 적용합니다.\n1번키로는 윈도우를 이동하고 나서 앞에다 놓을지 뒤에다 놓을지 정할수 있습니다.\n6번키로는 움직이고 난후의 윈도우의 상태를 결정할 수 있습니다."
#		define	_DATE						"2012-05-03"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					7

#		define _DEFAULT_X					100
#		define _DEFAULT_Y					100
#		define _DEFAULT_WIDTH				100
#		define _DEFAULT_HEIGHT				100
#		define _DEFAULT_HWND_INSERTED_AFTER	0 // HWND_TOP
#		define _DEFAULT_FLAG				SWP_SHOWWINDOW
#	endif
#else
#	define _NAME							"WNDDomainManipulator"
#	define _DEVELOPER						"haku"
#	define _REVISION						1 // 커널에서 판별하는 버전표기
#	define _VERSION							"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"0번셀렉터로 추출되는 모든 WND모듈의 크기를(2번키:x, 3번키:y, 4번키:width, 5번키:height)로 적용합니다.\n1번키로는 윈도우를 이동하고 나서 앞에다 놓을지 뒤에다 놓을지 정할수 있습니다.\n6번키로는 움직이고 난후의 윈도우의 상태를 결정할 수 있습니다."
#	define	_DATE							"2012-05-03"
#	define _DEPENDENCIES_COUNT				0
#	define _KEY_NUMBER						7

#	define _DEFAULT_X						100
#	define _DEFAULT_Y						100
#	define _DEFAULT_WIDTH					100
#	define _DEFAULT_HEIGHT					100
#	define _DEFAULT_HWND_INSERTED_AFTER		0 // HWND_TOP
#	define _DEFAULT_FLAG					SWP_SHOWWINDOW
#endif

