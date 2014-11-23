#define _NAME							"WNDDomainManipulator.dev.dbg"
#define _DEVELOPER						"kniz"
#define _REVISION						1 // 커널에서 판별하는 버전표기
#define _VERSION						"0.0.1a" // 사용자에게 보여주는 용도의 버전표기
#define _COMMENT						"지정한 윈도우(Window)를 특정 위치로 이동 시키거나, \n크기를 변하게 하거나, \n그려지는 우선순위를 변경할 수 있습니다."
#define	_DATE							"2012-05-03"
#define _DEPENDENCIES_COUNT				0
#define _KEY_NUMBER						7
#define _KEY_COMMENT_1					"변경할 Window 모듈"
#define _KEY_COMMENT_2					"이동할 왼쪽 좌표(X)"
#define _KEY_COMMENT_3					"이동할 위 좌표(Y)"
#define _KEY_COMMENT_4					"바뀌어질 윈도우의 너비(Width)"
#define _KEY_COMMENT_5					"바뀌어질 윈도우의 높이(Height)"
#define _KEY_COMMENT_6					"윈도우가 어떻게 보이게 할것인가 (보통 : 5)"
#define _KEY_COMMENT_7					"얼마나 윈도우를 상위로 할것인가를 결정한다. 상위로 가면 다른 윈도우를 덮으며 그려진다.\n0:맨위로 1:밑으로 -1:HWND_NOTOPMOST -2:HWND_TOPMOST"