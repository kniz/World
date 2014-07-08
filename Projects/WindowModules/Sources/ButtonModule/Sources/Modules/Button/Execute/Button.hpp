#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Button : public WND
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"
		#include "innerclass/ButtonConnector/ButtonConnector.hpp"
		
	public:
		Button();
		Button(const Button& source);

	public:
		virtual ~Button();

	public:
		Button::ButtonConnector& getConnector();
		const Button::ButtonConnector& getConnector() const;

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
		type_result changeCaption(const NETString& new_caption);

	protected:
		type_result _createButton();

	protected:
		ButtonConnector _connector;
	};
}
