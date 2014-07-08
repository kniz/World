#include "NESwitchComponent.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"

namespace NE
{
	NE_DLL NESwitchComponent::NESwitchComponent()
		: NEComponent()
	{
		_is_switch_on = false;
	}

	NE_DLL NESwitchComponent::NESwitchComponent(const NESwitchComponent& source)
		: NEComponent(source)
	{
		_is_switch_on = source._is_switch_on;
	}

	NE_DLL NESwitchComponent::~NESwitchComponent()
	{

	}

	const NESwitchComponent NE_DLL &NESwitchComponent::operator=(const NESwitchComponent& source)
	{
		NEComponent::operator=(source);

		_is_switch_on = source._is_switch_on;

		return *this;
	}

	bool NE_DLL NESwitchComponent::operator==(const NESwitchComponent& source) const
	{
		if(this == &source) return true;
		if(NEComponent::operator!=(source)) return false;
		if(_is_switch_on != source._is_switch_on) return false;

		return true;
	}

	bool NE_DLL NESwitchComponent::operator!=(const NESwitchComponent& source) const
	{
		return ! (operator==(source));
	}

	bool NE_DLL NESwitchComponent::isSwitchOn() const
	{
		return _is_switch_on;
	}

	void NE_DLL NESwitchComponent::setSwitch(bool enable)
	{
		_is_switch_on = enable;
	}

	void NE_DLL NESwitchComponent::release()
	{
		NEComponent::release();

		_is_switch_on = false;
	}

	NEType::Type NE_DLL NESwitchComponent::getType() const
	{
		return NEType::NESWITCH_COMPONENT;
	}

	NEBinaryFileSaver NE_DLL &NESwitchComponent::serialize(NEBinaryFileSaver& saver) const
	{
		NEComponent::serialize(saver);

		return saver << _is_switch_on;
	}

	NEBinaryFileLoader NE_DLL &NESwitchComponent::serialize(NEBinaryFileLoader& loader)
	{
		NEComponent::serialize(loader);

		return loader >> _is_switch_on;
	}
}
