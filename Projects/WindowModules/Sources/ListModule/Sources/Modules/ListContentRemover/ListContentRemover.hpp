#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ListContentRemover : public NEModule
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		ListContentRemover();
		ListContentRemover(const ListContentRemover& source);

	public:
		virtual ~ListContentRemover();

	public:


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
