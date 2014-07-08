//	---------------------------------------------------------------------------------
//	파일명	:	commonType.hpp
//	설명	:	노드 엔진에서의 객체의 타입을 나타낸다.
//	메모	:	노드엔진이 파악할 수 있는, 혹은 파악해야하는 모든 타입을 이곳에 정의한다
//	히스토리:	2011-05-29	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	namespace NEType
	{
		//	enum:
		//		NEType: NEObject가 갖는 변수형(type)에 사용하는 나열형
		//			타입번호:
		//				타입번호란, 타입이 실제로 프로세스 상에서 판단되는 int 형의 숫자를 의미한다.
		//				총 6자리수로 정해져있다.
		//			식별 가능한 타입:
		//				노드엔진 커널 및 Editor에서 정의된 객체들을 위한 타입으로, 이미 그 숫자가 
		//				정해져 있어, 같은 노드엔진 버전을 사용하는 프로세스에서 공통적으로 정의되는
		//				타입을 말한다.
		//				특정 모듈내에서만 통용되는, 타입번호가 존재할 수 있으며 Customized된 이 타입은
		//				식별 가능한 타입이 아니라고 정의한다.
		//			유효숫자로 계층구조 판단 알고리즘:
		//				개요:
		//					타입 Brother와 BigBrother 타입, LittleBrother타입이 존재할 때,
		//					BigBrother 타입과 LittleBrother타입이 그대로 일치하는 타입이라면, BigBrother타입은 LittleBrother 
		//					타입의 일종 혹은 같은 타입이라고 한다.
		//					그런데 추상적인 개념으로, Brother 타입은 BigBrother와 LittleBrother모두의 상위 개념이라고 할 수 있다.
		//					유효숫자로 계층구조 판단 알고리즘이란, 이와같은 추상적인 개념의 계층을 타입번호만을 이용하여 
		//					어느쪽이 다른쪽의 어느 한 종류인지 (is-a 관계) 판단하는 알고리즘을 말한다.
		//				필요성:
		//					특정 모듈에서 정의된 식별 불가능한 타입을 인식하기 위해서 필요하다.
		//					시나리오 1:
		//						특정 모듈 MyModule에서 정의된 식별 불가능한 타입 A 라고 하자.
		//						이 A는 커널 내에 존재하는 클래스 b(타입번호 B)로부터 상속받은 클래스다. 
		//						실 데이터(멤버변수)는 클래스 b를 그대로 따르되 함수만 새로 정의되었다.
		//						위와 같은 클래스가 MyModule에는 복수개 존재하며, 각각 클래스는 구별이 가야 하므로,
		//						unique 해야 한다.
		//						위와 같은 경우, A를 커널에서 인식이 가능하도록 하고 싶으나,	특정 모듈 내부에서는
		//						타입번호 b라고 인식이 되고 싶다.
		//				핵심알고리즘:
		//					유효숫자를 뽑아내어, Parent 타입번호의 max_boundary를 구한다.
		//					그리고 Parent타입번호 < 주어진 타겟 타입번호 < max_boundary 라면 is-a 관계라고 판단한다.
		//				제약조건:
		//					1. 0은 유효숫자로 간주할 수 없다. 따라서 123000 의 타입번호의 유효숫자는 123이 된다.
		//					2. 식별 불가능한 타입이 지정될 공간을 제공해야 하므로, 마지막 1의 자리는 항상 0으로 두어야 한다.
		//					3. OBJECT타입은 첫째자리에 해당되며, 4Byte int가 21억이므로 실 사용 자릿수는 9가 된다. (1억)
		//					4. 하나의 타입 밑에 10개 이상의 타입이 오면 곤란해진다. (불가능한 건 아니다)

		enum Type
		{
			TYPE_LENGTH											= 9, // 자릿수를 의미한다.
			//	타입:
			TYPE_START											= 000000000,
			//		Unknown:
			UNDEFINED											= 000000000, // undefined는 에러가 발생해서 0이 들어간 것을 의미한다
			//		Object:	100 000 000	~	199 999 999
			NEOBJECT											= 100000000,
			//			innerclass:	110 000 010	~	11[9 9]99 999	(서브타입은 갯수 10이상으로 인한 2자리 사용)
			NEINNERCLASS										= 110000000,			
			MODULE_DLL_HEADER									= 110100000,
			SCRIPT_HEADER										= 110200000,
			NENODE_DEPTH_UNIT									= 110300000, 
			NEMODULE_DEPTH_UNIT									= 110400000, 
			PANEL_MANAGER_HEADER								= 110500000, 
			SCRIPT_SELECTOR_CALLSTACK							= 110600000, 
			NESCRIPTEDITOR_BANKS									= 110800000,
			KERNAL_SETTINGS										= 110900000,
			KERNAL_MODIFIABLE_SETTINGS							= 111100000,
			KERNAL_FACTORY										= 111200000,			
			EDITOR_FACTORY										= 111300000,
			//				NodeManager:
			LOCALSTACK											= 111400000,
			//				Identifier:	111 500 000	~	111 599 999
			IDENTIFIER											= 111500000,
			//					Header:	111	510	000	~	111	519	999
			HEADER												= 111510000,
			MODULE_HEADER										= 111511000,
			EDITOR_MODIFIABLE_SETTINGS							= 111600000,
			NEBINDER_BASE										= 111700000,
			NENODE_BINDER										= 111710000,
			NEMODULE_BINDER										= 111720000,
			NEKEY_BINDER										= 111730000,
			//				Module:
			BASECONNECTOR										= 111800000,
			NEKEY_NAME_BINDER									= 111900000,
			ARGUMENT											= 112100000,
			ARGUMENTS											= 112200000,
			//				
			//		Collector:	120 000 000	~	129	999	999
			//			NEArrayTemplate:	121 000 000	~	121	999	999
			NECOLLECTOR_TEMPLATE								= 120000000,
			NEARRAY_TEMPLATE									= 121000000,
			NEBOOLEAN_SET										= 121010000,
			NEBYTE_SET											= 121020000,
			NECHAR_SET											= 121030000,
			NESTRING											= 121031000,			
			NEDOUBLE_SET										= 121040000,
			NEFLOAT_SET											= 121050000,
			NEINT64_SET											= 121060000,
			NEINT_SET											= 121070000,
			NECODE_SET											= 121071000,
			NESHORT_SET											= 121080000,
			NEUBYTE_SET											= 121090000,
			NEUSHORT_SET										= 121110000,
			NEUINT_SET											= 121120000,
			NEWCHAR_SET											= 121130000,
#ifdef _UNICODE
			NETCHAR_SET											= NEWCHAR_SET,
#else
			NECHAR_SET											= NECHAR_SET,
#endif
			NEWSTRING											= 121131000,
#ifdef _UNICODE
			NETSTRING 											= NEWSTRING,
#else
			NETSTRING 											= NESTRING,
#endif
			NESHORTCUTSET										= 121150000,
			NESCRIPT_SHORTCUTSET								= 121151000,
			NENAME_SHORTCUTSET									= 121152000,
			NEGROUP_SHORTCUTSET									= 121153000,
			NEPRIORITY_SHORTCUTSET								= 121154000,
			NESTRING_SET										= 121160000,
			NEWSTRING_SET										= 121170000,
#ifdef _UNICODE
			NETSTRING_SET 										= NEWSTRING_SET,
#else
			NETSTRING_SET 										= NESTRING_SET,
#endif
			NEKEY_CODESET										= 121190000,
			NEMODULE_CODESET									= 121210000,
			NENODE_CODESET										= 121220000,
			NEROOT_NODE_CODESET									= 121221000,
			//			NEPointerArray:	122 000 000	~	122	999	999
			NEPOINTER_ARRAY_TEMPLATE							= 122000000,
			//			NEPointerArray with PolyMorphism:	123 000 000	~	123	999	999
			NEPOINTER_ARRAY_WITH_POLYMORPHISM_TEMPLATE			= 123000000,
			NEKEYSET											= 123100000,
			NEMANAGED_KEYSET									= 123110000,
			NEPANELSET											= 123200000,
			NECOMPONENT_SET										= 123300000,
			//				NEModuleSet:	122 300 000	~	123 999 999
			NEMODULESET											= 123300000,
			NEMANAGED_MODULE_SET								= 123310000,
			//			NELIST:	123 000 000	~	123	999	999
			NELIST_TEMPLATE										= 124000000,
			//				NENodeList:	123 100 000	~	123 199 999
			NENODE_LIST											= 124100000,
			NESTRING_LIST										= 124200000,
			NEWSTRING_LIST										= 124300000,
			NEMODULE_DEPTH_LIST									= 124400000,
			NENODE_DEPTH_LIST									= 124500000,
			//			NEPointerList: 
			NEPOINTER_LIST_TEMPLATE								= 125000000,
			NESHORTCUT											= 125100000,
			//			NEPointerListWithPolyMorphism:	125 000 000	~	125 999 999
			NEPOINTER_LIST_WITH_POLY_MORPHISM_TEMPLATE			= 126000000,
			NEMODULE_LIST										= 126100000,
			NEPANEL_LIST										= 126200000,
			//			NEIndexedArrayTemplate:	127 000 000 ~	127 999 999
			NEINDEXED_ARRAY_TEMPLATE							= 127000000,
			NEINDEXED_NODESET									= 127100000,
			NEPOINTER_INDEXED_ARRAY_TEMPLATE					= 128000000,
			NEPOINTER_INDEXED_ARRAY_WITH_POLYMORPHISM_TEMPLATE	= 129000000,
			NEINDEXED_KEYSET									= 129100000,
			NEINDEXED_MODULESET									= 129200000,			
			//		Unit:	130 000 000	~	139 999 999
			NEUNIT												= 130000000,
			//			ManufacturedUnit: 131 000 000 ~	131 999 999
			NEEXCUTABLE_UNIT									= 131000000,
			//				NamedUnit:	131 100 000	~	131	199	999
			NENAMED_UNIT										= 131100000,
			//					Module:	131 110 000	~	131 119 999
			NEMODULE											= 131110000,
			NEINI_MANAGER										= 131110100,
			NEMODULE_MANAGER									= 131110200,
			NEENLISTABLE_MANAGER								= 131110300,
			NENODE_MANAGER										= 131110310,
			NESCRIPT_MANAGER									= 131110320,
			NESCRIPT_EDITOR										= 131110330,
			NEDEBUG_MANAGER										= 131110400,
			KERNAL												= 131110500,
			EDITOR												= 131110600,
			NEPANEL_MANAGER										= 131110700,
			NEEVENT_HANDLER										= 131110900,
			NEKEY_MANAGER										= 131111100,
			//					Node:	131 120 000	~	131 129	999
			NENODE												= 131120000,
			//				NEKey:	131 200 000	~	131	299	999
			NEKEY												= 132000000,
			//						TemplateClass:	131 210 000 ~	131 21[9 9]00,	9가 넘으므로 두자리 사용
			NEBOOLEAN_KEY										= 132101000,
			NECHAR_KEY											= 132102000,
			NEWCHAR_KEY											= 132103000,
#ifdef _UNICODE
			NETCHAR_KEY											= NEWCHAR_KEY,
#else
			NETCHAR_KEY											= NECHAR_KEY,
#endif
			NEBYTE_KEY											= 132104000,
			NEUBYTE_KEY											= 132105000,
			NESHORT_KEY											= 132106000,
			NEUSHORT_KEY										= 132107000,
			NEINT_KEY											= 132108000,
			NEUINT_KEY											= 132109000,
			NEINT64_KEY											= 132111000,
			NEFLOAT_KEY											= 132112000,
			NEDOUBLE_KEY										= 132113000,
			NESTRING_KEY										= 132114000,
			NEWSTRING_KEY										= 132115000,
#ifdef _UNICODE
			NETSTRING_KEY										= NEWSTRING_KEY,
#else
			NETSTRING_KEY										= NESTRING_KEY,
#endif
			NEBOOLEAN_SET_KEY									= 132116000,
			NEBYTE_SET_KEY										= 132117000,
			NEUBYTE_SET_KEY										= 132118000,			
			NESHORT_SET_KEY										= 132119000,
			NEUSHORT_SET_KEY									= 132121000,
			NEINT_SET_KEY										= 132122000,
			NECODE_SET_KEY										= 132123000,			
			NEUINT_SET_KEY										= 132124000,
			NEINT64_SET_KEY										= 132125000,
			NEFLOAT_SET_KEY										= 132126000,
			NEDOUBLE_SET_KEY									= 132127000,
			NESTRING_SET_KEY									= 132128000,
			NEWSTRING_SET_KEY									= 132129000,
#ifdef _UNICODE
			NETSTRING_SET_KEY									= NEWSTRING_SET_KEY,
#else
			NETSTRING_SET_KEY									= NESTRING_SET_KEY,
#endif
			NEMODULE_CODESET_KEY								= 132131000,
			NENODE_CODESET_KEY									= 132132000,
			//			Selector:	131 220 000	~	131 229 999
			NENODE_SELECTOR_BASE								= 132200000,
			NENODE_SELECTOR										= 132210000,
			NEMODULE_SELECTOR									= 132211000,
			NEKEY_SELECTOR										= 132211100,
			//			NEPanel:	132 000 000	~	132 999 999
			NEPANEL												= 133000000,
			//				NEDialog:	132 100 000	~	132 199	999
			NEDIALOG											= 133100000,
			//		NEComponent:	150 000 000	~	159 999 999
			NECOMPONENT											= 150000000,
			NETEXT_COMPONENT									= 151000000,
			//			NEListComponent::	152 000 000	~	152 999 999
			NELIST_COMPONENT									= 152000000,
			NECHECKLIST_COMPONENT								= 152100000,
			NEMODIFIABLE_LIST_COMPONENT							= 152200000,
			NESWITCH_COMPONENT									= 153000000,
			NEBUTTON_COMPONENT									= 154000000,			
			TYPE_END											= 999999999,
		};
		bool NE_DLL isValidHierachy(int super_type, int sub_type);
		int _getValidNumber(int type);
		int _getMaxBoundary(int valid_number);
		LPCTSTR NE_DLL getTypeName(NEType::Type type);
	}
}
