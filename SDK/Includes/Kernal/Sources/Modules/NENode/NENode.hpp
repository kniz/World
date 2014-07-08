//	---------------------------------------------------------------------------------
//	클래스명:	NENode
//	설명	:	모듈셋을 가지고 있는, "특정 서비스를 모아둠으로써 역할을 수행하는 객체"
//				를 나타낸다. 
//				모듈이 함수라면, 노드는 클래스의 개념으로 보면 된다.
//	관계	:	기반클래스.	NENamedUnit
//	특성	:	NodeManager에 friend 선언. NodeManager를 통해서 모든 private 멤버변수
//				를 수정할 수 있다.
//	사용방법:	execute()	:	모듈셋의 모든 모듈을 순차적으로 실행한다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEModuleCodeSet/NEModuleCodeSet.hpp"
#include "../NENamedUnit/NENamedUnit.hpp"
#include "../NEIntSet/NEIntSet.hpp"
#include "../../Commons/Templates/NEEnlistableSetTemplate/NEEnlistableSetTempate.hpp"

namespace NE
{
	//	스크립트에 저장되는 그룹코드가 담기는 객체.
	//	한번 스크립트 만들어지면 그룹코드는 그대로 유지되므로 Array를
	//	사용한다.
	//
	//	주의: NEIndexSet과는 다른 것으로, NEIndexSet은 노드의 인덱스를
	//	저장하므로 변경이 쉬운 List를 사용한다.

	template
	class NE_DLL NEEnlistableSetTemplate<NENamedUnit>;

	class NE_DLL NENode : public NEEnlistableSetTemplate<NENamedUnit>
	{
		typedef NEEnlistableSetTemplate<NENamedUnit> SuperClass;
		typedef NENode ThisClass;

		friend class NENodeCodeSet;
		friend class NERootNodeCodeSet;
		friend class NEEnlistableManager;
		friend class NEIndexedNodeSet;

		//	생성자:
	public:		
		NENode();
		NENode(const NENode& source);

		//	소멸자:
	public:
		virtual ~NENode();

		//	연산자 중첩:
	public:
		const NENode& operator=(const NENode& source);
		bool operator==(const NENode& source) const;
		bool operator!=(const NENode& source) const;

		//	인터페이스:
		//		접근자:
	public:
		type_result setNameCode(type_code new_namecode);
		const NEIntSet& getGroupCode() const;
		type_result setGroupCode(const NEIntSet& new_groupcodeset);
		type_code getPriority() const;
		type_result setPriority(type_code new_priority);
		NEModuleCodeSet& getModuleSet();
		const NEModuleCodeSet& getModuleSet() const;
		NEKeyCodeSet& getKeySet();
		const NEKeyCodeSet& getKeySet() const;
		bool isRootNode() const;
		NENodeCodeSet& getOwner();
		const NENodeCodeSet& getOwner() const;

		//		상속:
		//			NEUnit:
	public:
		virtual type_result execute();

		//			NEObject:
	public:
		virtual NEType::Type getType() const;
		virtual void release();
		virtual type_result isValid() const;
		virtual NEObject& clone() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	protected:
		virtual type_result _onEnlisted();
		type_result _onUnlisted();

		//	내부함수:
	private:
		void _release();
		const NENode& _assign(const NENode& source);

		//	멤버변수:
	protected:
		NEModuleCodeSet _modulecodeset;
		NEKeyCodeSet _keycodeset;
		type_code _priority;
		NEIntSet _groupcodeset;
		bool _is_rootnode;
		NENodeCodeSet* _owner;
	};
}
