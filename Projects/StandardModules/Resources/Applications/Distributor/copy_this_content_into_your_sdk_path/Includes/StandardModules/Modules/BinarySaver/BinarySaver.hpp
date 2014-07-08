#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	class NE_DLL BinarySaver : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		BinarySaver();
		BinarySaver(const BinarySaver& source);

	public:
		virtual ~BinarySaver();

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
