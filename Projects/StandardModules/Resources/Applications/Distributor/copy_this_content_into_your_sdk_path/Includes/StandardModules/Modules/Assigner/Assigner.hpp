#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	class NE_DLL Assigner : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		Assigner();
		Assigner(const Assigner& source);

	public:
		virtual ~Assigner();

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
