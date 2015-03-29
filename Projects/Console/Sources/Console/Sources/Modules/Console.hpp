#pragma once

#include "../Includes/Includes.hpp"

namespace Console 
{
	class NE_DLL Console : public NE::NEModule 
	{
	public:
		NE::NETArgument<NE::NETStringKey> arg_string;

	public:
		virtual const NE::NEExportable::ModuleHeader& getHeader() const;
		virtual NEObject& clone() const;

	protected:
		virtual type_result _onFetchModule();
		virtual type_result _onFetchArguments(NE::NEArgumentList& tray);
		virtual type_result _onExecute();
	};
}