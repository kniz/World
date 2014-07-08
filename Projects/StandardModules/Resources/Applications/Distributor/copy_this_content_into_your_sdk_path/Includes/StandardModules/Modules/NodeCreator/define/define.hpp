#define _START_OF_FLAG			0
#define _ALWAYS					0	// (= _HAS_FALSE_AND_TRUE_BOTH)
#define	_EVERYTHING_IS_FALSE	1
#define _EVERYTHING_IS_TRUE		2
#define _HAS_FALSE				3
#define _HAS_TRUE				4
#define _END_OF_FLAG			5

#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"NodeCreator.dev.dbg"
#		define _DEVELOPER				"haku"
#		define _REVISION				1
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"실행할때마다 0번키에 저장된 IDSet 요소 각각에 해당하는 스크립트를 모두 새롭게 생성합니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				1
#	else
#		define _NAME					"NodeCreator.dev"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"실행할때마다 0번키에 저장된 IDSet 요소 각각에 해당하는 스크립트를 모두 새롭게 생성합니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				1
#	endif
#else
#	define _NAME						"NodeCreator"
#	define _DEVELOPER					"haku"
#	define _REVISION					1
#	define _VERSION						"0.0.1a"
#	define _COMMENT						"실행할때마다 0번키에 저장된 IDSet 요소 각각에 해당하는 스크립트를 모두 새롭게 생성합니다."
#	define	_DATE						"2012-04-14"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					1
#endif
