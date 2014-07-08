//	---------------------------------------------------------------------------------
//	DLL명	:	FileAccess.dll
//	설명	:	파일 입출력을 수행한다.
//				지원되는 접근 모드는 다음과 같다.
//					1. 바이너리 모드
//					2. 순차 모드
//				각 모드별로 저장 과 로드가 가능하다.
//	관계	:	기반 패키지.	FileSystem
//				외부 포함.	<fstream>
//							<iostream>
//	특성	:	
//	클래스	:	NEBinaryAccess
//					NEBinaryFileSaver
//					NEBinaryFileLoader
//				NESequencialFileSaver
//				NESequencialFileLoader
//	메모	:	1	(!중요!)	
//					MBCS로 사용할경우, 일어등의 파일명을 사용해 저장할경우
//					파일이 깨지는 현상이 보임. (파일 내부는 일본어도 작성가능)
//					MBCS 및 유니코드 호환하는 프로그램에서 사용할경우 파일명을
//					영문으로 할것을 권장함.
//				2	빌드시, WBCS와 MBCS를 둘다 지원한다.
//					predefine 중 _UNICODE가 정의되어있으면 WBCS로 빌드한다.
//	히스토리:	2011-06-04	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../Modules/NEBinaryFileLoader/NEBinaryFileLoader.hpp"
#include "../Modules/NEBinaryFileSaver/NEBinaryFileSaver.hpp"
#include "../Modules/NESequencialFileLoader/NESequencialFileLoader.hpp"
#include "../Modules/NESequencialFileSaver/NESequencialFileSaver.hpp"

#ifndef FILEACCESS_EXPORTS
#	ifdef CORES_BUILD_MODE
#		ifdef DEVELOPER
#			ifdef _DEBUG
#				ifdef _UNICODE
#					pragma comment(lib, "../../../Binaries/Core/FileAccess.dev.dbg.lib")
#				else
#					pragma comment(lib, "../../../Binaries/Core/FileAccess.dev.dbg.mbcs.lib")
#				endif
#			else
#				ifdef _UNICODE
#					pragma comment(lib, "../../../Binaries/Core/FileAccess.dev.lib")
#				else
#					pragma comment(lib, "../../../Binaries/Core/FileAccess.dev.mbcs.lib")
#				endif
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "../../../Binaries/Core/FileAccess.lib")
#			else
#				pragma comment(lib, "../../../Binaries/Core/FileAccess.lib")
#			endif
#		endif
#	else
#		ifdef DEVELOPER
#			ifdef _DEBUG
#				ifdef _UNICODE
#					pragma comment(lib, "FileAccess.dev.dbg.lib")
#				else
#					pragma comment(lib, "FileAccess.dev.dbg.mbcs.lib")
#				endif
#			else
#				ifdef _UNICODE
#					pragma comment(lib, "FileAccess.dev.lib")
#				else
#					pragma comment(lib, "FileAccess.dev.mbcs.lib")
#				endif
#			endif
#		else
#			ifdef _UNICODE
#				pragma comment(lib, "FileAccess.lib")
#			else
#				pragma comment(lib, "FileAccess.lib")
#			endif
#		endif
#	endif
#endif
