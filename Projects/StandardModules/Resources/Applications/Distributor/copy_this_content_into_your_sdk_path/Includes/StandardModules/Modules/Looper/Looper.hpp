#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	class NE_DLL Looper : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		Looper();
		Looper(const Looper& source);

	public:
		virtual ~Looper();

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
