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
		NETArgument<NEModuleSelector> arg_button;
		
	protected:
		virtual type_result _onExecute();
		virtual type_result _onFetchArguments(NEArgumentList& tray);

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;
	
	protected:
		Button& _castToButton(NEModule& module);
	};
}