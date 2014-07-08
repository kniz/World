#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL BinaryLoader : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		BinaryLoader();
		BinaryLoader(const BinaryLoader& source);

	public:
		virtual ~BinaryLoader();

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
