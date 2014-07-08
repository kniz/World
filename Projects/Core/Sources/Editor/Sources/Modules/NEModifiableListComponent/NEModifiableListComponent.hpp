#pragma once

#include "../NEListComponent/NEListComponent.hpp"

namespace NE
{
	class NE_DLL NEModifiableListComponent : public NEListComponent
	{
	public:
		NEModifiableListComponent();
		NEModifiableListComponent(const NEModifiableListComponent& source);

	public:
		~NEModifiableListComponent();

	public:
		const NEModifiableListComponent& operator=(const NEModifiableListComponent& source);
		bool operator==(const NEModifiableListComponent& source) const;
		bool operator!=(const NEModifiableListComponent& source) const;

	public:
		NETString& getText();
		const NETString& getText() const;
		type_result setText(const NETString& source);
		type_result removeSelectedContentFromContents();
		type_result insertTextInputedToContents();

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual	NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	private:
		void _release();
		const NEModifiableListComponent& _assign(const NEModifiableListComponent& source);

	protected:
		NETString _text;
	};
}
