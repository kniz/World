#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME						"WNDShowManipulator.dev.dbg"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"0번키로부터 추출된 모든 WND를 1번키에 지정한 모드로 출력합니다"
#		define	_DATE						"2012-05-03"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					2

#		define _DEFAULT_SHOW_COMMAND		SW_SHOWNORMAL
#	else
#		define _NAME						"WNDShowManipulator"
#		define _DEVELOPER					"haku"
#		define _REVISION					1 // 커널에서 판별하는 버전표기
#		define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT						"0번키로부터 추출된 모든 WND를 1번키에 지정한 모드로 출력합니다"
#		define	_DATE						"2012-05-03"
#		define _DEPENDENCIES_COUNT			0
#		define _KEY_NUMBER					2

#		define _DEFAULT_SHOW_COMMAND		SW_SHOWNORMAL
#	endif
#else
#	define _NAME							"WNDShowManipulator"
#	define _DEVELOPER						"haku"
#	define _REVISION						1 // 커널에서 판별하는 버전표기
#	define _VERSION							"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#	define _COMMENT							"0번키로부터 추출된 모든 WND를 1번키에 지정한 모드로 출력합니다"
#	define	_DATE							"2012-05-03"
#	define _DEPENDENCIES_COUNT				0
#	define _KEY_NUMBER						2

#	define _DEFAULT_SHOW_COMMAND			SW_SHOWNORMAL
#endif

