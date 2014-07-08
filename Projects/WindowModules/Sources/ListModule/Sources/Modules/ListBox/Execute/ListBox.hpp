#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL ListBox : public WND
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		ListBox();
		ListBox(const ListBox& source);

	public:
		virtual ~ListBox();

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

	public:
		WND::WNDConnector& getConnector();
		const WND::WNDConnector& getConnector() const;

	public:
		type_result insertContent(const NETString& content);
		type_result removeContent(type_index index);

	protected:
		type_result _createList();
		type_result _fillContentsFromKey();

	protected:
		WNDConnector _connector;
	};
}
