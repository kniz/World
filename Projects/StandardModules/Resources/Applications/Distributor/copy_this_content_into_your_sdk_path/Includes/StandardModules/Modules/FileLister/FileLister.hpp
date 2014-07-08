#pragma once

#include "../../Includes/include.hpp"

namespace NE
{
	class NE_DLL FileLister : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		FileLister();
		FileLister(const FileLister& source);

	public:
		virtual ~FileLister();

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
