//	---------------------------------------------------------------------------------
//	클래스명:	NETList
//	설명	:	LinkedList의 형태로 데이터를 관리하는 클래스.
//	관계	:	기반클래스.			NETCollector
//				중첩하는 클래스.	Iterator
//	특성	:	LinkedList의 특성을 그대로 구현한다. 각 엘리먼트는 추가/삽입/삭제의
//				부하가 적은 반면, "검색"에 취약하다.
//				Iterator은 외부에서 사용이 가능하다.
//	알고리즘:	중첩된 클래스. Iterator은 다음 엘리먼트를 가리키는, NETList의 최소단위다.
//				이 Iterator을 이용해서 List를 관리한다.
//				만약 포인터를 삽입했을 경우, 해당 포인터로부터 가상복사생성자인 clone
//				을 호출해서 DeepCopy 한다.
//	사용방법:	정의 방법
//					:	템플릿 인자 T의 조건
//							조건 1.	NEObject를 상속해야한다. 
//									NEObject::clone()를 사용하기 때문이다.
//							조건 2. 
//				type_bool pointerUseNewInstance란?
//					:	false일때 T가 포인터일 경우, 포인터가 새로운 인스턴스를 가리키도록
//						하지않고, shallowcopy만을 사용하겠다는 의미다.
//						true일때는 NEPointerList.hpp를 참고하라.
//				기본적으로 NETCollector의 함수를 모두 사용가능하다. (참조 할 것)
//				기본 인터페이스
//					1. push(T*)			:	포인터의 형태로 삽입이 가능하다.
//					2. pushFront(T*)	:	포인터의 형태로 삽입이 가능하다.
//					3. push(NETList&)	:	리스트 전부를 통째로 삽입한다.
//					4. pushFront(NETList&)
//					5. getIterator()		:	Iterator을 외부에서 접근한다. const로만 사용할 것을
//											권장한다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#pragma message("NETList.inl - 1")
#include "../NETCollector/NETCollector.inl"
#pragma message("NETList.inl - 2")
#include "../../Commons/Interfaces/NESpecifiedInsertable/NESpecifiedInsertable.hpp"
#pragma message("NETList.inl - 3")

namespace NE
{
	template <typename T, type_bool pointerUseNewInstance = false>
	class NETList : public NETCollector<T>, public NESpecifiedInsertable<T>
	{
		//	Why did you typedef this useless one:
		//		if I use existing class template name, that macro
		//		would accept the comma between template argument as 
		//		macro's one.
		//		That means, it'll think that an user passes 3 
		//		argument, not 2.
		//		In conclusion, this's just a prevention.
		typedef NETList<T, pointerUseNewInstance> _This;

		NE_DECLARE_CLASS_ONLY(_This, NETCollector<T>)


		//	innerclasses:
	protected:
		struct Node 
		{
			T value;
			Node* next;
			Node* back;
		};

		//	생성자:
	public:
		NETList();	
		NETList(const This& source);

		//	소멸자:
	public:
		virtual ~NETList();

		//	연산자 중첩:
	public:
		const This& operator=(const This& source); 
		This operator+(const This& source) const;
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;
		const This& operator+=(const This& source);

		//	인터페이스:
		//		상속:
		//			NETCollector:
	public:
		virtual NETCIterator<T> getIterator(type_index index) const;
		virtual NETIterator<T> getIterator(type_index index);
		virtual type_index insert(const NETCIterator<T>& where, const T& source);
		virtual type_index remove(type_index index);
		virtual type_index match(const T& source) const;
		virtual type_index push(const T& source);
		virtual type_index pop();
		//			NEObject:
	public:
		virtual type_result isValid() const; 
		virtual void release(); 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const; 		
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//		고유 인터페이스:
	public:
		type_index pushFront(const T& source);
		type_index popFront();
		type_result push(const This& source);
		type_result pushFront(const This& source);

		//	내부함수:
	private:
		const This& _assign(const This& source);
		void _release();
		type_count _getUnitCount() const;
		Node* _getBeforeTail();

		//	멤버변수:
	private:
		Node* _head;
	};
}

#include "NETListWithBinder.inl"