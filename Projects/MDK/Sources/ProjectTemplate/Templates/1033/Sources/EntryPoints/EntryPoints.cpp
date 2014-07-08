#include "Headers.hpp"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

namespace NE
{

[!if export_execute_module]
	NEModuleList _declspec(dllexport) _stdcall _EXECUTE_ENTRYPOINT
	{		
		NEModuleList modulelist;

		modulelist.push( [!output module_name]() );

		return modulelist;
	}
[!endif]

[!if export_panel]
	NEPanelList _declspec(dllexport) _stdcall _PANEL_ENTRYPOINT
	{
		NEPanelList panellist;

		panellist.push( [!output panel_name]() );

		return panellist;
	}
[!endif]
}
