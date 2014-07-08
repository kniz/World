#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Enabler : public NEModule
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		Enabler();
		Enabler(const Enabler& source);

	public:
		virtual ~Enabler();

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
