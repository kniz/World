#pragma once

#include "../WNDSpy.hpp"

namespace NE
{
	class NE_DLL MouseSpy : public WNDSpy
	{
	public:
		NEITArgument<NEModuleSelector> arg_window_selector;
		NEITArgument<NEIntKey> arg_notification_type;
		NEITArgument<NEIntKey> arg_out_cursor_x;
		NEITArgument<NEIntKey> arg_out_cursor_y;

	protected:
		virtual type_result _onFetchArguments(NEArgumentInterfaceList& tray);
		virtual type_result _onExecute();

	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;
	};
}