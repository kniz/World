#pragma once

#include "../../../includes/include.hpp"

namespace NE
{
	class NE_DLL [!output panel_name] : public NEPanel
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"
		#include "innerclass/StringTyper/StringTyper.hpp"
		
	public:
		[!output panel_name]();
		[!output panel_name](const [!output panel_name]& source);

	public:
		virtual ~[!output panel_name]();
		
	public:
		type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;		
	};
}
