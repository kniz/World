#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NameChanger : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		NameChanger();
		NameChanger(const NameChanger& source);

	public:
		virtual ~NameChanger();

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
