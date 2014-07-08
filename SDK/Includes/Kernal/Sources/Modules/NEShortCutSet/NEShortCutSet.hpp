//	---------------------------------------------------------------------------------
//	클래스명:	NEShortCutSet
//	설명	:	복수의 NEShortCut를 관리하고, 셀렉터들에게 friend선언을 하도록 만들어진
//				클래스.
//	관계	:	기반클래스.	NEArrayTemplate<NEShortCut>
//	특성	:	
//	알고리즘:	
//	사용방법:	NEArrayTemplate를 참고하라.
//	메모	:	
//	히스토리:	2011-07-12	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

#include "../../Commons/Interfaces/NEEnlistable/NEEnlistable.hpp"
#include "../NEShortCut/NEShortCut.hpp"

namespace NE
{
	template 
	class NE_DLL NEArrayTemplate<NEShortCut, false, NEShortCut, NEType::NESHORTCUTSET>;

	class NE_DLL NEShortCutSet : public NEArrayTemplate<NEShortCut, false, NEShortCut, NEType::NESHORTCUTSET>, public NEEnlistable
	{
	public:
		typedef NEArrayTemplate<NEShortCut, false, NEShortCut, NEType::NESHORTCUTSET> SuperClass;
		typedef NEShortCutSet ThisClass;
		
		friend class NEEnlistableManager;

	public:
		NEShortCutSet()
			: SuperClass()
		{

		}
		NEShortCutSet(type_index size)
			: SuperClass(size)
		{

		}
		NEShortCutSet(const ThisClass& source)
			: SuperClass(source)
		{

		}

	public:
		using NEEnlistable::_enlist;
		using NEEnlistable::_unlist;	
	};
}