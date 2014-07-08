#pragma once

#include "../NEComponent/NEComponent.hpp"

namespace NE
{
	class NE_DLL NEButtonComponent : public NEComponent
	{
	public:
		NEButtonComponent();
		NEButtonComponent(const NEButtonComponent& source);

	public:
		~NEButtonComponent();

	public:
		using NEComponent::operator=;
		using NEComponent::operator==;
		using NEComponent::operator!=;

	public:
		virtual	NEType::Type getType() const;
	};
}
