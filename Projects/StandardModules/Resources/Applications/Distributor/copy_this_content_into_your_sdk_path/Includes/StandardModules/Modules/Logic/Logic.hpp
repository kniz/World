#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	class NE_DLL Logic : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/OperatorType/OperatorType.hpp"

	public:
		Logic();
		Logic(const Logic& source);

	public:
		virtual ~Logic();

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
