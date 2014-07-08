#pragma once

#include "../WND/Window/Window.hpp"

namespace NE
{
	class NE_DLL WNDSpy : public NEModule
	{
	public:
		WNDSpy();
		WNDSpy(const WNDSpy& source);

	public:
		virtual ~WNDSpy();

	protected:
		Window& _castToWindow(NEModule& module);
	};
}