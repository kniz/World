#pragma once

#include "../NETClass/NETClass.hpp"
#include "../NETCollector/NETCollector.hpp"
#include "NETList.inl"

namespace NE
{
#define _LISTNAME	NETList<T>
#define _TEMPLATE	template <typename T>
#define _NAME		_LISTNAME##::Node

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		return	_value == rhs._value	&&
			_next == rhs._next		&&
			_back == rhs._back		;
	}

	_TEMPLATE
	type_bool _NAME::operator!=(const This& rhs) const
	{
		return ! operator==(rhs);
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if(	! _value.isBinded()					&&
			_back.isBinded() && _next.isBinded())
			return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	void _NAME::release()
	{
		Super::release();

		_value.release();
		_next.release();
		_back.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _value << _next << _back;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _value >> _next >> _back;
	}

	_TEMPLATE
	NETBinder<T>& _NAME::getValueBinder()
	{
		return _value;
	}

	_TEMPLATE
	const NETBinder<T>& _NAME::getValueBinder() const
	{
		return _value;
	}

	_TEMPLATE
	NETBinder<Node>& _NAME::getNextBinder()
	{
		return _next;
	}

	_TEMPLATE
	const NETBinder<Node>& _NAME::getNextBinder() const
	{
		return _next;
	}

	_TEMPLATE
	NETWeakBinder<Node>& _NAME::getBackBinder()
	{
		return _back;
	}

	_TEMPLATE
	const NETWeakBinder<Node>& _NAME::getBackBinder() const
	{
		return _back;
	}

#undef _NAME	
#define _NAME	_LISTNAME##::Iterator

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	_NAME::Iterator(_This& owner, Node& new_node)
		: Super(), _owner(owner), _node(new_node)
	{

	}			

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		//	When these binders are designating same object each other,
		//	we'll return true.
		return	_owner.get() == rhs._owner.get()	&&
			_node.get() == rhs._node.get()	;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		const T* nullpointer = NE_NULL;
		if( ! _node.isBinded())
			return *nullpointer;

		return *_node->getValueBinder();
	}

	_TEMPLATE
	T& _NAME::get()
	{
		T* nullpointer = NE_NULL;
		if( ! _node)
			return nullpointer;

		return *_node->getValueBinder();
	}

	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		//	Only end node of the either side(front and back) doesn't bind any node.
		return ! _node.isBinded();	
	}


	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		for(int n=0; n < step_for_next ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getNextBinder());
		}
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		for(int n=0; n < step_for_back ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getBackBinder());
		}
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_index _NAME::getLength() const
	{
		return _owner.isBinded() ? _owner->getLength() : 0;
	}

	_TEMPLATE
	void _NAME::release()
	{
		_owner.release();
		_node.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _owner << _node;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _owner >> _node;
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if( ! _owner.isBinded()) return RESULT_TYPE_ERROR;
		if( ! _node.isBinded()) return RESULT_TYPE_ERROR;
		if(	NEResult::hasError(_node.isValid())	)
			return RESULT_TYPE_WARNING;
		//	check valid of binded state:
		//		targetting:
		NETBinder<Node>& nexted = _node->getNextBinder();
		NETWeakBinder<Node>& backed = _node->getBackBinder();
		if( nexted.isBinded()	||
			backed.isBinded()	)
			return RESULT_TYPE_ERROR;
		if( ! _node->getValueBinder().isBinded())
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	_LISTNAME& _NAME::getOwner()
	{
		return _owner;
	}

	_TEMPLATE
	const _LISTNAME& _NAME::getOwner() const
	{
		return _owner;
	}

	_TEMPLATE
	_LISTNAME::Node& _NAME::getNode()
	{
		return _node;
	}

	_TEMPLATE
	const _LISTNAME::Node& _NAME::getNode() const
	{
		return _node;
	}

#undef _NAME	
#define _NAME	_LISTNAME::CIterator

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	_NAME::CIterator(const _This& owner, Node& new_node)
		: Super(), _owner(owner), _node(new_node)
	{

	}			

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		//	When these binders are designating same object each other,
		//	we'll return true.
		return	_owner.get() == rhs._owner.get()	&&
			_node.get() == rhs._node.get()	;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		const T* nullpointer = NE_NULL;
		if( ! _node.isBinded())
			return *nullpointer;

		return *_node->getValueBinder();
	}

	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		//	Only end node of the either side(front and back) doesn't bind any node.
		return ! _node.isBinded();	
	}

	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		for(int n=0; n < step_for_next ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getNextBinder());
		}
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		for(int n=0; n < step_for_back ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getBackBinder());
		}
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_index _NAME::getLength() const
	{
		return _owner.isBinded() ? _owner->getLength() : 0;
	}

	_TEMPLATE
	void _NAME::release()
	{
		_owner.release();
		_node.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _owner << _node;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _owner >> _node;
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if( ! _owner.isBinded()) return RESULT_TYPE_ERROR;
		if( ! _node.isBinded()) return RESULT_TYPE_ERROR;
		if(	NEResult::hasError(_node.isValid())	)
			return RESULT_TYPE_WARNING;
		//	check valid of binded state:
		//		targetting:
		NETBinder<Node>& nexted = _node->getNextBinder();
		NETWeakBinder<Node>& backed = _node->getBackBinder();
		if( nexted.isBinded()	||
			backed.isBinded()	)
			return RESULT_TYPE_ERROR;
		if( ! _node->getValueBinder().isBinded())
			return RESULT_TYPE_ERROR;
	}

	_TEMPLATE
	const _LISTNAME& _NAME::getOwner() const
	{
		return _owner;
	}

	_TEMPLATE
	const _LISTNAME::Node& _NAME::getNode() const
	{
		return _node;
	}

#undef _NAME

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_LISTNAME), NE_MACRO_FUNNEL(_TEMPLATE))

		//	---------------------------------------------------------------------------------
		//	히스토리:	2011-07-07	이태훈	개발 완료
		//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME::NETList()
		:Super()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME::NETList(const This& source)
		:Super()
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME::~NETList()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _LISTNAME& _LISTNAME::operator=(const This& source) 
	{
		if(this == &rhs) return *this;

		//	Don't need to call Super. length will be synchronized automatically.

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME _LISTNAME::operator+(const This& source) const
	{
		//	pre:
		//		파라메터 검사:
		if(source._length <= 0)	return This(*this);



		//	main:
		//		복사:
		//			임시 버퍼 생성:
		This buffer(*this);
		//			버퍼에 데이터 축적:		
		buffer.push(source);



		// post:
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _LISTNAME::operator==(const This& source) const
	{
		//	pre:
		if(this == &source) return true;
		if(NETCollector<T>::operator==(source) == false) return false;


		//	main:
		NETIterator<T>	my_e = getIterator(),
			their_e = getIterator();
		for(; ! my_e.isEnd() ;my_e++, their_e++)
			if(	their_e.isEnd()	||
				*my_e != *their_e	)	
				return false;


		//	post:
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _LISTNAME::operator!=(const This& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _LISTNAME& _LISTNAME::operator+=(const This& source)
	{
		if(source._length == NE_NULL) return *this;

		push(source);

		return *this;	
	}


	_TEMPLATE
	NETBinder<NETIterator<T>> _LISTNAME::getIterator(type_index index)
	{
		Iterator& iterator = *(new Iterator(this, *_head));
		NETBinder<NETIterator<T>> to_return(iterator);
		type_index step_to_next = 0;
		if(	index < 0)							step_to_next = 0;
		else if( index > getLengthLastIndex())	step_to_next = getLength() + 1;
		//	why do we add 1 to index?:
		//		1 is for going next to the head. head is not counted as element.
		else									step_to_next = index + 1;

		iterator.next(step_to_next);
		return to_return;
	}

	_TEMPLATE
	NETBinder<NETCIterator<T>> _LISTNAME::getIterator(type_index index) const
	{
		CIterator& iterator = *(new CIterator(this, *_head));
		NETBinder<NETCIterator<T>> to_return(iterator);
		type_index step_to_next = 0;
		if(	index < 0)							step_to_next = 0;
		else if( index > getLengthLastIndex())	step_to_next = getLength() + 1;
		//	why do we add 1 to index?:
		//		1 is for going next to the head. head is not counted as element.
		else									step_to_next = index + 1;

		iterator.next(step_to_next);
		return to_return;
	}

	_TEMPLATE
	NETBinder<NETIterator<T>> _LISTNAME::insert(const NETCIterator<T>& where, const T& source) 
	{
		//	pre:
		//		파라메터 검사:
		NETBinder<NETIterator<T>> to_return;
		CIterator& wh = cast<CIterator>(where);
		if( ! _isValid(wh)	||
			! &source		)
			return to_return;


		//	main:
		//		targetting:
		Node& next = wh.getNode(),
			& previous = *next.getBackBinder();
		//		create new one:
		Node node = *(new Node());
		node.getValueBinder().bind(source.clone());
		node.getBackBinder().bind(previous);
		node.getNextBinder().bind(next);
		//		rebinding:
		NETBinder<Node>& previous_binder = &previous ? 
			previous.getNextBinder() : _head.getNextBinder();
		previous_binder.bind(node);
		next.getBackBinder().bind(node);


		//	post:
		//		길이 수정:	유닛을 추가했으므로, 길이 정보도 동기화 시킨다
		_length++;
		//		packaging the return:
		//			copycstr x2 + heap allocation x1
		to_return.bind(*(new Iterator(*this, node)));
		return to_return;
	}


	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NETBinder<NETIterator<T>> _LISTNAME::remove(const NETCIterator<T>& from, const NETCIterator<T>& end)
	{
		//	pre:
		//		파라메터 검사:
		NETBinder<NETIterator<T>> to_return;
		CIterator&	fr = cast<CIterator>(from),
				 &	ed = cast<CIterator>(end);		
		//		Iterator valid check:
		if( ! _isValid(fr)	||
			! _isValid(ed)	)
			return to_return;


		//	main:
		//		we need to get Length to remove.
		//
		//		Why do we have to do that?:
		//			there is 2 reasons.
		//			
		//			1. To remove those at once:
		//				if we know the length to be removed, we can do that at once
		//				by using NETBinder's characterstic. make them loose binding 
		//				cascade.
		//				All we have to do is just simple.
		//				make the before of the from iterator bind the end iterator.
		//				by doing that, from ~ ahead of end one will be terminated.
		//				but there is one problem which we don't know the length to
		//				be synchronized.
		//			
		//			2. Parameter reversed issue:
		//				if user have inputed parameter "from" and "end" reversed,
		//				It's so difficult to detect.
		//				Because they're born from the this List instance, each 
		//				isValid() can't notify what's the problem.
		//				if the problem is catched up, it's the by who can see the
		//				the whole picture of the owner, List instance.
		//				
		//				make it possible is simple, of course. please refer 
		//				NETCollector::operator<(); it've been already implemented.
		//				But this remove() became to have O(n2).
		//				So the main point of resolving this issue is optimization.
		//				
		//			So, getting the length to be removed can be used for resolving 
		//			1 and 2 problem at the same time.
		type_count length_to_remove = 0;
		to_return.bind( *(new Iterator(*this, fr.getNode())) );
		Iterator& e = *to_return;
		//		Looping:
		for(; e != end ;e++)
		{
			Node& node = *e.getNode();
			if( ! &node)
				//	Parameter reversing detected.
				return to_return;		

			length_to_remove++;
		}

		//	post:
		//		Now, e is pointing the place at the node that had existed before:
		//		Let me show you Fig.
		//		In this example, there are 4 Nodes, and user just try to remove
		//		Node B and C.
		//	
		//		Fig 1	-	At first, User wants to remove the node B pointed 
		//					by iterator where.
		//					remove() create iterator e pointing to same instance 
		//					like "where".
		//
		//			[A]	-	[B]	-	[C]	-	[D]
		//					 ^
		//					 |
		//				 where, e
		//	
		//
		//		Fig 2	-	And before the node B was removed, Iterator e which was 
		//					cloned from A point to the next.
		//					And B would be released because there is no binder who 
		//					bind it.
		//		
		//			[A]	-	[C]	-	[D]				[B] ---> Released.
		//					 ^						 ^
		//					 |						 |
		//					 e						where (this's WeakBinder, not Binder)
		//
		//		Fig 3	-	And Node C goes on..
		//	
		//			[A]	-	[D]						NULL
		//					 ^						 ^
		//					 |						 |
		//					 e						where
		//
		//		Fig 4	-	return the iterator "e".


		Node& previous = *fr.getNode().getBackBinder(),
			& next = *ed.getNode();
		//	rebinding:
		previous.getNextBinder().bind(next);	//	remove Nodes.
		next.getBackBinder().bind(previous);

		//	Node will have been already released automatically:
		//		Now, there is no String Binder to make "node" instance keep alive. 
		//		Of course, by releasing variable "node", its "Value" T might had
		//		been gotten same destiny.
		to_return.bind(e);
		return to_return;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_result _LISTNAME::isValid() const  
	{
		//	pre:
		//		상위클래스 VALID 체크:
		type_result result =Super::isValid();
		if(NEResult::hasError(result) == true) return result;
		//		멤버변수 체크:
		int count = 0;
		CIterator<T>& e = cast<CIterator<T>>(*getFirstIterator());
		if( ! &e) return RESULT_TYPE_ERROR;
		for(; ! e.isEnd() ;e++)
		{
			count++;
			if(NEResult::hasError(e.getNode().isValid()))
				return RESULT_TYPE_ERROR;

			return RESULT_SUCCESS;
		}
		if(NEResult::hasError(result)) return result;
		if(count != getLength()) return false;

		return true;
	}


	_TEMPLATE
	void  _LISTNAME::release()  
	{			
		_release();

		return Super::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileSaver  &_LISTNAME::serialize(NEBinaryFileSaver& saver) const 
	{	
		//	pre:
		NETCollector::serialize(saver);

		//	main:
		//		엘리먼트 저장:
		each([&saver](const T& e) -> type_result {
			saver << e;
			return RESULT_SUCCESS;
		});


		//	post:
		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileLoader& _LISTNAME::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:		
		release();
		NETCollector::serialize(loader);
		type_index count = _length;	
		NETCollector::release();



		//	main:
		//		길이 정보 초기화:		
		//		엘리먼트 로드:		
		for(type_index n=0; n < count ;n++)
		{
			T element = T(); // 그냥 T element()를 한다면 함수의 선언으로 컴파일러가 착각한다.

			loader >> element;
			push(element);
		}


		//	post:
		return loader;
	}

	_TEMPLATE
	const _LISTNAME& _LISTNAME::_assign(const This& source)
	{	
		//	pre:
		release();
		//	main:
		push(source);
		//	post:
		return *this;
	}

	_TEMPLATE
	type_bool _LISTNAME::_isValid(const CIterator& rhs) const
	{
		return	&rhs								&&
				! NEResult::hasError(rhs.isValid())	&&
				rhs.getOwner() == this				;
	}

	_TEMPLATE
	void  _LISTNAME::_release() 
	{	
		//	main:
		type_count length = getLength(); // pop을 하면 _length가 하나씩 줄어들므로, for문 조건식에서 오작동을 일으킨다. 그러므로 미리 size를 가져옴

		for(type_index n=0; n < length ;n++)
			pop();


		//	post:
		//		create empty Node at last position. if there isn't.
		//
		//		Why do we create this?:
		//			this's the end iterator.
		//			when we insert some element, At the last position is always 
		//			for this end iterator. 
		//			So usually, when we pop all elements, _head binder actually 
		//			will be pointing this end iterator in order for user to notify
		//			that this NETList reached to end.
		if( ! _head.getNextBinder().isBinded())
			_head.getNextBinder().bind( *(new Node()) );
	}

#undef _LISTNAME
#undef _TEMPLATE
}