#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ElementInserter : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		ElementInserter();
		ElementInserter(const ElementInserter& source);

	public:
		virtual ~ElementInserter();

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;

	private:
		template <typename T, bool useHeap, NEType::Type type>
		type_result _insertToCollector(NEArrayTemplate<T, useHeap, T, type>& collector, type_index index, const T& source);
	};
}
