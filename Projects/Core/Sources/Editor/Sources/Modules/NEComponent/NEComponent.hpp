#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NEPanel;
	class NEDialog;

	class NE_DLL NEComponent : public NEUnit
	{
		friend class NEPanel;

	public:
		NEComponent();
		NEComponent(const NETString& name);
		NEComponent(const NEComponent& source);

	public:
		virtual ~NEComponent();

	public:
		const NEComponent& operator=(const NEComponent& source);
		bool operator==(const NEComponent& source) const;
		bool operator!=(const NEComponent& source) const;

	public:
		const NETString& getComment() const;
		NETString& getComment();
		const NETString& getCaption() const;
		NETString& getCaption();

	public:
		virtual type_result execute();

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	protected:
		virtual type_result _onDialogueReturned(NEPanel& panel, NEDialog& dialogue);
		virtual type_result _onUpdate(NEPanel& panel);
		virtual type_result _onFocus(NEPanel& panel);
		virtual type_result _onUnfocus(NEPanel& panel);
		virtual type_result _onLoad(NEPanel& panel);
		virtual type_result _onUnload(NEPanel& panel);		
		virtual type_result _onDisabled(NEPanel& panel);
		virtual type_result _onEnabled(NEPanel& panel);

	private:
		const NEComponent& _assign(const NEComponent& source);

	protected:	 
		NETString _caption;
		NETString _comment;
	};
}
