#pragma once

#include "../NEComponentSet/NEComponentSet.hpp"

namespace NE
{
	class NEDialog;

	class NE_DLL NEPanel : public NEExecutableUnit, public NEExportable
	{
	public:
		#include "innerclass/BaseConnector/BaseConnector.hpp"	

	public:
		friend class NEPanelManager;

	public:
		NEPanel();
		NEPanel(NEModule& module);
		NEPanel(const NEPanel& source);

	public:
		~NEPanel();

	public:
		const NEPanel& operator=(const NEPanel& source);
		bool operator==(const NEPanel& source) const;
		bool operator!=(const NEPanel& source) const;

	public:
		type_result setModule(NEModule& module);
		void disconnectModule();
		NEModule& getModule();
		const NEModule& getModule() const;
		NEComponentSet& getComponentSet();
		const NEComponentSet& getComponentSet() const;

		//	모든 컴포넌트에게 메세지가 도착하는 함수:
	public:
		virtual type_result onUpdate(type_index component_index);
		virtual type_result onLoad(type_index component_index);
		virtual type_result onFocus(type_index component_index);
		virtual type_result onUnload(type_index component_index);
		virtual type_result onUnfocus(type_index component_index);
		virtual type_result onDialogReturned(type_index component_index, NEDialog& dialogue);
		virtual type_result onDisabled(type_index component_index);
		virtual type_result onEnabled(type_index component_index);	
		virtual type_result onUnload(); // NEDialog에서 필요하므로, virtual 선언
		virtual type_result onLoad(); // NEDialog에서 필요하므로, virtual 선언
		virtual type_result onUpdate();		
		virtual type_result onFocus();		
		virtual type_result onUnfocus();
		virtual type_result onDialogReturned(NEDialog& dialogue);
		virtual type_result onDisabled();
		virtual type_result onEnabled();

	public:
		virtual type_result execute();

	public:	
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEType::Type getType() const;
		virtual void release();
		virtual type_result isValid() const;
		
	private:
		const NEPanel& _assign(const NEPanel& source);
		void _release();

	protected:
		NEComponentSet _componentset;
		NEModule* _module;
	};
}
