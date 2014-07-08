#pragma once

#include "../NEComponent/NEComponent.hpp"

namespace NE
{
	class NE_DLL NEListComponent : public NEComponent
	{
	public:
		NEListComponent();
		NEListComponent(const NEListComponent& source);

	public:
		~NEListComponent();

	public:
		const NEListComponent& operator=(const NEListComponent& source);
		bool operator==(const NEListComponent& source) const;
		bool operator!=(const NEListComponent& source) const;

	public:
		const NETStringSet& getContents() const;
		type_index getSelectedContentIndex() const;
		void selectContent(type_index index_of_content);

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual	NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		
	private:
		void _release();
		const NEListComponent& _assign(const NEListComponent& source);

	protected:
		NETStringSet _contents;
		type_index _index;
	};
}
