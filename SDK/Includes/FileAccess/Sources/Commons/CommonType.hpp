//	---------------------------------------------------------------------------------
//	파일명	:	FileAccessCommonType.h
//	설명	:	FileAccess에서 사용하는 공통 타입 및 선언들
//	메모	:
//	히스토리:	2011-01-08	이태훈	작성
//				2011-06-04	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

namespace NE
{
	enum NEFileSaverFlag
	{
		NEFILESAVERFLAG_OVERWRITE = 0, // 기본값
		NEFILESAVERFLAG_APPEND_AT_END_OF_FILE,		
		NEFILESAVERFLAG_DO_NOT_OVERWRITE,
		NEFILESAVERFLAG_EXISTED_ONLY
	};
}
