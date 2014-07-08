#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"ElementExtractor.dev.dbg"
#		define _DEVELOPER				"haku"
#		define _REVISION				1
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"콜렉터(0번키)의 주어진 인덱스(1번키)를 -> 키셀렉터(2번키)로부터 추출된 모든 키에다 할당합니다.\n만약 인덱스(1번키)가 콜렉터(0번키)의 길이보다 큰값이면 push가 동작되며, 0일 경우에는 pushFront가 동작됩니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				3
#	else
#		define _NAME					"ElementExtractor.dev"
#		define _DEVELOPER				"haku"
#		define _REVISION				1 
#		define _VERSION					"0.0.1a"
#		define _COMMENT					"콜렉터(0번키)의 주어진 인덱스(1번키)를 -> 키셀렉터(2번키)로부터 추출된 모든 키에다 할당합니다.\n만약 인덱스(1번키)가 콜렉터(0번키)의 길이보다 큰값이면 push가 동작되며, 0일 경우에는 pushFront가 동작됩니다."
#		define	_DATE					"2012-04-14"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				3
#	endif
#else
#	define _NAME						"ElementExtractor"
#	define _DEVELOPER					"haku"
#	define _REVISION					1
#	define _VERSION						"0.0.1a"
#	define _COMMENT						"콜렉터(0번키)의 주어진 인덱스(1번키)를 -> 키셀렉터(2번키)로부터 추출된 모든 키에다 할당합니다.\n만약 인덱스(1번키)가 콜렉터(0번키)의 길이보다 큰값이면 push가 동작되며, 0일 경우에는 pushFront가 동작됩니다."
#	define	_DATE						"2012-04-14"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					3
#endif
