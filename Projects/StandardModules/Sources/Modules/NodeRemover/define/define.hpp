#define _START_OF_FLAG			0
#define _ALWAYS					0	// (= _HAS_FALSE_AND_TRUE_BOTH)
#define	_EVERYTHING_IS_FALSE	1
#define _EVERYTHING_IS_TRUE		2
#define _HAS_FALSE				3
#define _HAS_TRUE				4
#define _END_OF_FLAG			5

#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"NodeRemover"
#		define _DEVELOPER				"haku"
#		define _REVISION				1
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"0번 셀렉터에 해당되는 노드를 전부 삭제합니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				1
#	else
#		define _NAME					"NodeRemover"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"0번 셀렉터에 해당되는 노드를 전부 삭제합니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				1
#	endif
#else
#	define _NAME						"NodeRemover"
#	define _DEVELOPER					"haku"
#	define _REVISION					1
#	define _VERSION						"0.0.1a"
#	define _COMMENT						"0번 셀렉터에 해당되는 노드를 전부 삭제합니다."
#	define	_DATE						"2012-04-14"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					1
#endif
