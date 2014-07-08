#include "WNDSpy.hpp"

namespace NE
{
	NE_DLL WNDSpy::WNDSpy()
		: NEModule()
	{
		
	}

	NE_DLL WNDSpy::WNDSpy(const WNDSpy& source)
		: NEModule(source)
	{
	
	}

	NE_DLL WNDSpy::~WNDSpy()
	{
	
	}

	Window& WNDSpy::_castToWindow(NEModule& module)
	{
		//	pre:
		Window* null_pointer = NE_NULL;
		if( ! &module)
		{
			ALERT_ERROR(" : 널이 들어왔음")

			return *null_pointer;
		}

		static NEExportable::Identifier _identifier(_T("Window"), _T("haku"), 1);

		if(_identifier != module.getHeader())
		{
			ALERT_ERROR(" : 찾은 모듈이 윈도우 모듈이 아닙니다")

			return *null_pointer;
		}

		

		return static_cast<Window&>(module);;
	}
}