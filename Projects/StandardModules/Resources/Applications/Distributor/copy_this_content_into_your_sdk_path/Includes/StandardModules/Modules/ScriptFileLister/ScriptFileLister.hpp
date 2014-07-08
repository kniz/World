#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	class NE_DLL ScriptFileLister : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		ScriptFileLister();
		ScriptFileLister(const ScriptFileLister& source);

	public:
		virtual ~ScriptFileLister();

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
