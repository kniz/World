#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ElementExtractor : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		ElementExtractor();
		ElementExtractor(const ElementExtractor& source);

	public:
		virtual ~ElementExtractor();

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
		template <typename T, bool useHeap, NEType::Type type, typename WrapClass>
		type_result _assignFromCollector(NEArrayTemplate<T, useHeap, T, type>& collector, type_index index, NEKey& source, WrapClass& wraper);
	};
}
