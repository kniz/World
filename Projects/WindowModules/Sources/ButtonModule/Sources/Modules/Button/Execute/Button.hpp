#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Button : public WND
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"
		typedef WND SuperClass;
		
		NETArgument<NEModuleSelector> arg_window_selector;
		NETArgument<NETStringKey> arg_caption;
		NETArgument<NEIntKey> arg_menu_id;

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	protected:
		virtual type_result _onExecute();
		virtual type_result _onFetchArguments(NEArgumentList& tray);
		virtual type_result _onFetchModule();

	public:
		virtual NEObject& clone() const;

	public:
		type_result changeCaption(const NETString& new_caption);

	protected:
		type_result _createButton();
	};
}
