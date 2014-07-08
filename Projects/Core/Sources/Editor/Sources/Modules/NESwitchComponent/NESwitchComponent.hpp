#pragma once

#include "../NEComponent/NEComponent.hpp"

namespace NE
{
	class NE_DLL NESwitchComponent : public NEComponent
	{
	public:
		NESwitchComponent();
		NESwitchComponent(const NESwitchComponent& source);

	public:
		~NESwitchComponent();

	public:
		const NESwitchComponent& operator=(const NESwitchComponent& source);
		bool operator==(const NESwitchComponent& source) const;
		bool operator!=(const NESwitchComponent& source) const;

	public:
		bool isSwitchOn() const;
		void setSwitch(bool enable);
		
	public:
		virtual void release();
		virtual	NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		
	protected:
		bool _is_switch_on;
	};
}
