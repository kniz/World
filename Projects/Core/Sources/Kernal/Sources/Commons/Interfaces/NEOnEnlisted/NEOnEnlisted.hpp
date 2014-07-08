#pragma once

#include "../../Functions/NEResult/NEResult.hpp"

namespace NE
{	
	class NE_DLL NEOnEnlisted
	{
		friend class NEKeyCodeSet;
		friend class NEModuleCodeSet;
		friend class NENodeCodeSet;
		friend class NERootNodeCodeSet;
		friend class NENode;

	protected:		
		virtual type_result _onEnlisted() = 0;
	};
}