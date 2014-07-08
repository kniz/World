//	---------------------------------------------------------------------------------
//	클래스명:	NEListTemplate
//	설명	:	LinkedList의 형태로 데이터를 관리하는 클래스.
//	관계	:	기반클래스.			NECollectorTemplate
//				중첩하는 클래스.	Iterator
//	특성	:	LinkedList의 특성을 그대로 구현한다. 각 엘리먼트는 추가/삽입/삭제의
//				부하가 적은 반면, "검색"에 취약하다.
//				Iterator은 외부에서 사용이 가능하다.
//	알고리즘:	중첩된 클래스. Iterator은 다음 엘리먼트를 가리키는, NEListTemplate의 최소단위다.
//				이 Iterator을 이용해서 List를 관리한다.
//				만약 포인터를 삽입했을 경우, 해당 포인터로부터 가상복사생성자인 clone
//				을 호출해서 DeepCopy 한다.
//	사용방법:	정의 방법
//					:	템플릿 인자 T의 조건
//							조건 1.	NEObject를 상속해야한다. 
//									NEObject::clone()를 사용하기 때문이다.
//							조건 2. 
//				bool pointerUseNewInstance란?
//					:	false일때 T가 포인터일 경우, 포인터가 새로운 인스턴스를 가리키도록
//						하지않고, shallowcopy만을 사용하겠다는 의미다.
//						true일때는 NEPointerList.hpp를 참고하라.
//				기본적으로 NECollectorTemplate의 함수를 모두 사용가능하다. (참조 할 것)
//				기본 인터페이스
//					1. push(T*)			:	포인터의 형태로 삽입이 가능하다.
//					2. pushFront(T*)	:	포인터의 형태로 삽입이 가능하다.
//					3. push(NEListTemplate&)	:	리스트 전부를 통째로 삽입한다.
//					4. pushFront(NEListTemplate&)
//					5. getIterator()		:	Iterator을 외부에서 접근한다. const로만 사용할 것을
//											권장한다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NECollectorTemplate/NECollectorTemplate.hpp"
#include "../../Interfaces/NESpecifiedInsertable/NESpecifiedInsertable.hpp"

namespace NE
{
	template <typename T, bool pointerUseNewInstance = false, NEType::Type type = NEType::NELIST_TEMPLATE>
	class NEListTemplate : public NECollectorTemplate<T>, NESpecifiedInsertable<T>
	{
		typedef NECollectorTemplate<T> SuperClass;
		typedef NEListTemplate<T, pointerUseNewInstance, type> ThisClass;
		//	내부클래스:
	public:
#include "innerclass/Iterator/Iterator.hpp"

		//	생성자:
	public:
		NEListTemplate();	
		NEListTemplate(const NEListTemplate<T, pointerUseNewInstance, type>& source);

		//	소멸자:
	public:
		virtual ~NEListTemplate();

		//	연산자 중첩:
	public:
		const NEListTemplate<T, pointerUseNewInstance, type>& operator=(const NEListTemplate<T, pointerUseNewInstance, type>& source); 
		NEListTemplate<T, pointerUseNewInstance, type> operator+(const NEListTemplate<T, pointerUseNewInstance, type>& source) const;
		bool operator==(const NEListTemplate<T, pointerUseNewInstance, type>& source) const;
		bool operator!=(const NEListTemplate<T, pointerUseNewInstance, type>& source) const;
		const NEListTemplate<T, pointerUseNewInstance, type>& operator+=(const NEListTemplate<T, pointerUseNewInstance, type>& source);

		//	인터페이스:
		//		상속:
		//			NECollectorTemplate:
	public:		
		virtual const T& getElement(type_index index) const; 
		virtual T& getElement(type_index index); 
		virtual type_result setElement(type_index index, const T& source);  		
		virtual type_index insert(type_index index, const T& source);
		virtual type_index remove(type_index index);
		virtual type_index find(const T& source) const;
		virtual type_index push(const T& source);
		virtual type_index pop();
		//			NEObject:
	public:
		virtual NEObject& clone() const;
		virtual type_result isValid() const; 
		virtual void release(); 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const; 		
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEType::Type getType() const;

		//		고유 인터페이스:
	public:
		type_index pushFront(const T& source);
		type_index popFront();
		type_result push(const NEListTemplate<T, pointerUseNewInstance, type>& source);
		type_result pushFront(const NEListTemplate<T, pointerUseNewInstance, type>& source);
		Iterator* getIterator(type_index index);
		const Iterator* getIterator(type_index index) const;

		//	내부함수:
	private:
		const NEListTemplate<T, pointerUseNewInstance, type>& _assign(const NEListTemplate<T, pointerUseNewInstance, type>& source);
		void _release();
		type_count _getUnitCount() const;
		Iterator* _getBeforeTail();

		//	멤버변수:
	private:
		Iterator* _head;
	};
}

#include "NEListTemplate.inl"
#include "NEPointerListTemplate.hpp"
#include "NEPointerListWithPolyMorphismTemplate.hpp"
