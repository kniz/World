#include "NEIteratorBase.hpp"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	NE_DEFINE_INTERFACE_ONLY(NEIteratorBase)

	NEIteratorBase& NEIteratorBase::operator++()
	{
		next();

		return *this;
	}

	const NEObject& NEIteratorBase::get() const
	{
		This* casted = const_cast<This*>(this);

		return casted->get();
	}
}