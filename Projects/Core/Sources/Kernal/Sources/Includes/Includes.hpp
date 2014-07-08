//	---------------------------------------------------------------------------------
//	파일명	:	Includes.hpp
//	설명	:	FileAccess를 import한다.
//				lib와 헤더를 사용한 정적 링킹을 사용한다. 
//	알고리즘:	precondition.	FileAccess은 빌드 모드에 따라서 각각 정해진 파일명
//				으로 되어있어야한다.
//				빌드 모드는 다음과 같다. (괄호 안은 해당 모드시, 정의되는 predefine)
//					-	모드	-						-	파일명	-
//					MBCS 디버그(_DEBUG)					프로젝트명.mbcs.dev.dll
//					MBCS 릴리즈							프로젝트명.mbcs.dll
//					WBCS 디버그(_DEBUG, _UNICODE)		프로젝트명.dev.dll
//					WBCS 릴리즈(_UNICODE)				프로젝트명.dll
//				
//				1.	DLL의 import와 export를 하나의 헤더파일로 처리하기 위해서는 
//						#define DLL _declspec(dllexport)
//					와 같은 define을 사용해서 처리한다.
//				2.	import하는 헤더는 _declspec(dllimport)여야 하고, 자신의 프로젝트는
//					_declspec(dllexport)여야 한다.
//					그래서 SetDLLIMPORT.hpp를 사용해서 NE_DLL을 _declspec(dllimport)
//					로 만들고, 헤더를 인클루드 한뒤, SetDLLEXPORT.hpp를 사용하여 _decl
//					spec(dllexport)로 되돌린다.
//				3.	그런데, 임의의 프로젝트를 A라고 가정하자. 그리고 A는 DLL 프로젝트라
//					한다면,	이 A에서도 FileAccess를 import 할수도 있다.
//					이경우, A는 FileAccess를 import하면서, FileAccess의 IncludeNE
//					FileSystem.hpp을 통해서 FileSystem도 import하게 되므로 이를 
//					처리할 수 있는 방법이 필요하다.
//					정리하면, 다음과 같은 import가 이루어져야 할것 이다.
//						-	A프로젝트	-	-	FileAccess	-	-	FileSystem	-
//						SetDLLIMPORT
//						Includes.hpp
//											IncludeFileSystem.hpp
//																	#include "FileSystem클래스"
//											#include "FileAccess클래스"
//						SetDLLEXPORT
//						#include "A프로젝트 클래스"
//				4.	그런데, 2번의 알고리즘대로 구현하면 중간 단계인 FileAccess에서 
//					SetDLLEXPORT가 되어버리고 만다.
//					이걸 피하기 위해, 추가적으로 하나의 #ifdef를 사용, 자신의 프로젝트
//					가 빌드하는 경우만 SetDLLEXPORT 되는 것으로 설정한다.
//									
//	메모	:	
//	히스토리:	2011-06-04	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../../Macro/Sources/Modules/DLLMacro/SetDLLIMPORT.hpp" // DLL 내부의 DLL이므로, DLLIMPORT로 선언한다.
#include "../../../FileAccess/Sources/EntryPoints/Headers.hpp" // DLLIMPORT로 헤더를 붙여넣고,
#ifdef KERNAL_EXPORTS // kernal프로젝트에서 선언된 전처리기. 그 이외의 프로젝트는 DLLIMPORT로 계속 헤더를 붙여넣는다.
#	include "../../../Macro/Sources/Modules/DLLMacro/SetDLLEXPORT.hpp" // kernal프로젝트는 여기서 STOP. NEDLLEXPORT로 나머지 클래스를 붙여넣는다.
#endif
