#pragma once

#include "../NEListComponent/NEListComponent.hpp"

namespace NE
{
	class NE_DLL NECheckListComponent : public NEListComponent
	{
	public:
		NECheckListComponent();
		NECheckListComponent(const NECheckListComponent& source);

	public:
		~NECheckListComponent();

	public:
		const NECheckListComponent& operator=(const NECheckListComponent& source);
		bool operator==(const NECheckListComponent& source) const;
		bool operator!=(const NECheckListComponent& source) const;

	public:		
		const NEBooleanSet& getCheckSet() const;
		void check(type_index index, bool is_checked);

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual	NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	private:
		void _release();
		const NECheckListComponent& _assign(const NECheckListComponent& source);

	protected:		
		NEBooleanSet _checkset;
	};
}
