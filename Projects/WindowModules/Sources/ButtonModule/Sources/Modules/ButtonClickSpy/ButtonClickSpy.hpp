#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class Button;

	class NE_DLL ButtonClickSpy : public WNDSpy
	{
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		ButtonClickSpy();
		ButtonClickSpy(const ButtonClickSpy& source);

	public:
		virtual ~ButtonClickSpy();

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual type_result execute();

	public:
		virtual NEObject& clone() const;
	
	protected:
		Button& _castToButton(NEModule& module);
	};
}