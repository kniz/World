#include "../../NEListTemplate.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NEListTemplate<T*, false, type>::Iterator::Iterator(const T* source, typename NEListTemplate<T*, false, type>::Iterator* next)
		: _next(next)
	{
		T* const_casted_source = const_cast<T*>(source);
		_value = const_casted_source;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NEListTemplate<T*, false, type>::Iterator::~Iterator()
	{
		
	}

	
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename T& NEListTemplate<T*, false, type>::Iterator::getValue()
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename const T& NEListTemplate<T*, false, type>::Iterator::getValue() const
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	void NEListTemplate<T*, false, type>::Iterator::setValue(T* source)
	{
		_value = source;
	}
	
	
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename const NEListTemplate<T*, false, type>::Iterator* NEListTemplate<T*, false, type>::Iterator::getNext() const
	{
		return _next;
	}
	
	template <typename T, NEType::Type type>
	typename NEListTemplate<T*, false, type>::Iterator* NEListTemplate<T*, false, type>::Iterator::getNext()
	{
		return _next;
	}
}
