#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	class NE_DLL PriorityChanger : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		PriorityChanger();
		PriorityChanger(const PriorityChanger& source);

	public:
		virtual ~PriorityChanger();

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const;
	};
}
