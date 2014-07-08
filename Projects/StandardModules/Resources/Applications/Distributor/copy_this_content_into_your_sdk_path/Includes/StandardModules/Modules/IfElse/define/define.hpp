#define _START_OF_FLAG			0
#define _ALWAYS					0	// (= _HAS_FALSE_AND_TRUE_BOTH)
#define	_EVERYTHING_IS_FALSE	1
#define _EVERYTHING_IS_TRUE		2
#define _HAS_FALSE				3
#define _HAS_TRUE				4
#define _END_OF_FLAG			5

#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"IfElse.dev.dbg"
#		define _DEVELOPER				"haku"
#		define _REVISION				1
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"조건모듈(0번키)이 주어진 조건상수(3번키)에 참이면 액션모듈(1번키)를 실행하고, 조건이 거짓이면 거짓액션모듈(2번키)를 실행합니다.\n조건 상수:\n\t0\t:\t조건 없음(= Always)\n\t1\t:\t조건모듈의 모든 값이 RESULT_FALSE일때\n\t2\t:\t조건모듈의 모든 값이 RESULT_TRUE일때\n\t3\t:\t조건 모듈중에서 하나라도 RESULT_FALSE일때\n\t4\t:\t조건 모듈중에서 하나라도 RESULT_TRUE일때"
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				4
#	else
#		define _NAME					"IfElse.dev"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"조건모듈(0번키)이 주어진 조건상수(3번키)에 참이면 액션모듈(1번키)를 실행하고, 조건이 거짓이면 거짓액션모듈(2번키)를 실행합니다.\n조건 상수:\n\t0\t:\t조건 없음(= Always)\n\t1\t:\t조건모듈의 모든 값이 RESULT_FALSE일때\n\t2\t:\t조건모듈의 모든 값이 RESULT_TRUE일때\n\t3\t:\t조건 모듈중에서 하나라도 RESULT_FALSE일때\n\t4\t:\t조건 모듈중에서 하나라도 RESULT_TRUE일때"
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				4
#	endif
#else
#	define _NAME						"IfElse"
#	define _DEVELOPER					"haku"
#	define _REVISION					1
#	define _VERSION						"0.0.1a"
#	define _COMMENT						"조건모듈(0번키)이 주어진 조건상수(3번키)에 참이면 액션모듈(1번키)를 실행하고, 조건이 거짓이면 거짓액션모듈(2번키)를 실행합니다.\n조건 상수:\n\t0\t:\t조건 없음(= Always)\n\t1\t:\t조건모듈의 모든 값이 RESULT_FALSE일때\n\t2\t:\t조건모듈의 모든 값이 RESULT_TRUE일때\n\t3\t:\t조건 모듈중에서 하나라도 RESULT_FALSE일때\n\t4\t:\t조건 모듈중에서 하나라도 RESULT_TRUE일때"
#	define	_DATE						"2012-04-14"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					4
#endif
