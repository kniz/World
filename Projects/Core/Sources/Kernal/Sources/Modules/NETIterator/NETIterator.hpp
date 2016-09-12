#pragma once

#include "NETIterator.inl"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NETIterator<T>, template <typename T>)

	template <typename T>
	NETIterator<T>& NETIterator<T>::operator++()
	{
		return static_cast<This&>(Super::operator++());
	}

	template <typename T>
	NETIterator<T>& NETIterator<T>::operator+(type_count step_for_next)
	{
		return static_cast<This&>(Super::operator+(step_for_next));
	}

	template <typename T>
	T& NETIterator<T>::operator*()
	{
		return (T&) get();
	}

	template <typename T>
	const T& NETIterator<T>::operator*() const
	{
		return (const T&) get();
	}

	template <typename T>
	T& NETIterator<T>::operator->()
	{
		return (T&) get();
	}

	template <typename T>
	const T& NETIterator<T>::operator->() const
	{
		return (const T&) get();
	}
}