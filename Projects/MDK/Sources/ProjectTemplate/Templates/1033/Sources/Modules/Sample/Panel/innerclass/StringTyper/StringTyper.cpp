#include "../../[!output panel_name].hpp"
#include "../../../Execute/[!output module_name].hpp"

namespace NE
{
	type_result NE_DLL [!output panel_name]::StringTyper::_onUpdate(NEPanel& panel)
	{
		[!output module_name]& module = static_cast<[!output module_name]&>(panel.getModule());

		module.getConnector().getHelloWorld().getValue() = getText();

		return RESULT_SUCCESS;
	}

	type_result NE_DLL [!output panel_name]::StringTyper::_onFocus(NEPanel& panel)
	{
		[!output module_name]& module = static_cast<[!output module_name]&>(panel.getModule());

		setText( module.getConnector().getHelloWorld().getValue() );

		return RESULT_SUCCESS;
	}

	type_result NE_DLL [!output panel_name]::StringTyper::_onLoad(NEPanel& panel)
	{
		[!output module_name]& module = static_cast<[!output module_name]&>(panel.getModule());

		_onFocus(panel);
		
		_comment = _T("hello world! comment here!");
		_caption = _T("caption here!");

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &[!output panel_name]::StringTyper::clone() const
	{
		return *(new StringTyper(*this));
	}
}
