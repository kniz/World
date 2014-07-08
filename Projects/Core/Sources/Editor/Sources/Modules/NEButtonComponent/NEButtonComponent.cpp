#include "NEButtonComponent.hpp"

namespace NE
{
	NE_DLL NEButtonComponent::NEButtonComponent()
		: NEComponent()
	{
		
	}

	NE_DLL NEButtonComponent::NEButtonComponent(const NEButtonComponent& source)
		: NEComponent(source)
	{
		
	}

	NE_DLL NEButtonComponent::~NEButtonComponent()
	{

	}

	NEType::Type NE_DLL NEButtonComponent::getType() const
	{
		return NEType::NEBUTTON_COMPONENT;
	}
}
