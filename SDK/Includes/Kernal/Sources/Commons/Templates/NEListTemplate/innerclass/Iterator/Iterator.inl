#include "../../NEListTemplate.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NEListTemplate<T, pointerUseNewInstance, type>::Iterator::Iterator(const T& source, typename NEListTemplate<T, pointerUseNewInstance, type>::Iterator* next)
		: _value(source), _next(next)
	{}			
	
	
	
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NEListTemplate<T, pointerUseNewInstance, type>::Iterator::~Iterator()
	{
	
	}



	//	---------------------------------------------------------------------------------
	//	설명:		_value의 접근자.
	//				그냥 public으로 빼면 되는 걸, 왜 getValue()를 사용하는가?
	//					:	Iterator과 인터페이스를 맞추기 위해서.
	//						Iterator은 NEListTemplate 외부에 노출되는 클래스인데, 이때 절대로
	//						포인터를 외부에 노출하지 않아야 한다.
	//						그래서, 포인터가 고정된 형태인 "레퍼런스" 형태로 외부에 노출
	//						시키기 위해서 getValue() 함수를 사용할 수 밖에 없다.
	//						같은 NEListTemplate가, 어느쪽에서만 getValue()를 쓰고, 다른 한쪽은 _value
	//						를 바로 써서는 안되므로 통일시켜주기 위해서 Iterator은 모두 접근자
	//						함수를 사용하는 것으로 되었다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	T& NEListTemplate<T, pointerUseNewInstance, type>::Iterator::getValue()
	{
		return _value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	const T& NEListTemplate<T, pointerUseNewInstance, type>::Iterator::getValue() const
	{
		return _value;
	}



	//	---------------------------------------------------------------------------------	
	//	메모:		Iterator* const를 해서는 안돼고, 할 필요도 없다.
	//					해서는 안돼는 이유 1. 외부에서 iterator로 사용할 경우, 포인터의 
	//					값이 변경이 되어야 하기 때문이다.
	//					할필요가 없는 이유 1. 값복사가 이루어지고 있기 때문이다.
	//					만약 리턴값이 Iterator*& 이라면 const가 필요할 것이다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	void NEListTemplate<T, pointerUseNewInstance, type>::Iterator::setValue(const T& source)
	{
		_value = source;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	typename const NEListTemplate<T, pointerUseNewInstance, type>::Iterator* NEListTemplate<T, pointerUseNewInstance, type>::Iterator::getNext() const
	{
		return _next;
	}	
	
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	typename NEListTemplate<T, pointerUseNewInstance, type>::Iterator* NEListTemplate<T, pointerUseNewInstance, type>::Iterator::getNext()
	{
		return _next;
	}	
}
