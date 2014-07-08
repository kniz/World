//	----------------------------------------------------------------------------
//	클래스명:	NEPanelSet
//	설명	:	복수의 NEModule를 deepcopy가 가능하도록 NEArrayTemplate<T*, true>를 통해
//				정의된 클래스.
//	관계	:	기반클래스.	NEArrayTemplate<NEPanel*, true>
//	특성	:	serialize시, NEModule의 타입을 보고 인스턴스를 생성이 가능하다.
//	알고리즘:	
//	사용방법:	NEArrayTemplate를 참고하라.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	----------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEPanel/NEPanel.hpp"

namespace NE
{
	template
	class NE_DLL NEArrayTemplate<NEPanel*, true, NEPanel*, NEType::NEPANELSET>;
	typedef NEArrayTemplate<NEPanel*, true, NEPanel*, NEType::NEPANELSET> NEPanelSet;
}
