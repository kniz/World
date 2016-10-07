#pragma once

//	include:
#include "../NETCollector/NETCollector.inl"

namespace NE
{
	template<typename T>
	class NETReservedCollector : public NETCollector<T>
	{
		NE_DECLARE_INTERFACE_ONLY(NETReservedCollector<T>, NETCollector<T>)

		//	Constructors:
	public:
		NETReservedCollector();
		NETReservedCollector(type_index size);
		NETReservedCollector(const This& source);
		virtual ~NETReservedCollector();	

		//	Operators:
	public:
		const This& operator=(const This& source); 
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;	

		//	Virtuals:
	public:
		//		NETReservedCollector:
		virtual type_result create(type_index new_size) = 0;
		virtual type_result resize(type_index new_size) = 0;		
		//		NEObject:
		virtual void release(); 
		virtual type_result isValid() const; 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		type_index getSize() const;
		type_index getSizeLastIndex() const;
		type_bool isEqualElement(const This& rhs) const;

	private: 
		const This& _assign(const This& source);
		void _release();

		//	Members:
	protected:
		type_index _size;
	}; 
}