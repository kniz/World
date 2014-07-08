#define _START_OF_FLAG		0
#define _DONT_CARE			1	//	default
#define _DO_NOT_OVERWRITE	2
#define _OVERWRITE_ONLY		3
#define _END_OF_FLAG		4

#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"BinarySaver"
#		define _DEVELOPER				"haku"
#		define _REVISION				1
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"경로(0번키)에 해당되는 파일을 flag(1번키)를 적용하여, NodeManager를 저장합니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				2
#	else
#		define _NAME					"BinarySaver"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"경로(0번키)에 해당되는 파일을 flag(1번키)를 적용하여, NodeManager를 저장합니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				2
#	endif
#else
#	define _NAME						"BinarySaver"
#	define _DEVELOPER					"haku"
#	define _REVISION					1
#	define _VERSION						"0.0.1a"
#	define _COMMENT						"경로(0번키)에 해당되는 파일을 flag(1번키)를 적용하여, NodeManager를 저장합니다."
#	define	_DATE						"2012-04-14"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					2
#endif
