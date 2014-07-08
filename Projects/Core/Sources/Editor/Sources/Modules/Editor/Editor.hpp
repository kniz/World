#pragma once

#include "../NEPanelManager/NEPanelManager.hpp"
#include "../NEScriptEditor/NEScriptEditor.hpp"
#include "../NEEventHandler/NEEventHandler.hpp"
//	왜 DebugMacro는 마지막에 위치해야 하는가:
//		각 매니져클래스(예를들어 NEPanelManager.hpp)에서 Includes.hpp을 통해서 
//		DebugMacro.hpp를 가져오기 때문이다.
//		DebugMacro.hpp가 include 되고 나서 EditDebugMacro가 include 되야지 경고가 나타나지
//		않는 형태로 되어있다.
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"

namespace NE
{
	class NE_DLL Editor : public NEModule
	{	
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/ModifiableSettings/ModifiableSettings.hpp"
#include "innerclass/Factory/Factory.hpp"

	private:
		Editor();

	public:
		Editor(const Editor& source);

	public:
		virtual ~Editor();

	public:
		const Editor& operator=(const Editor& source);
		bool operator==(const Editor& source) const;
		bool operator!=(const Editor& source) const;
	
	public:
		virtual type_result initialize();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode);

	private:
		virtual type_result execute();
	public:
		virtual void release();		
		virtual NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;
		virtual NEObject& clone() const;

	public:
		const NEPanelManager& getPanelManager() const;
		NEPanelManager& getPanelManager();
		const NEScriptEditor& getScriptEditor() const;
		NEScriptEditor& getScriptEditor();
		const NEEventHandler& getEventHandler() const;
		NEEventHandler& getEventHandler();		
		const ModifiableSettings& getSettings() const;
		const ModifiableSettings& getDefaultSettings() const;
		type_result loadSettings();

	private:
		const Editor& _assign(const Editor& source);
		void _release();
		void _releaseManagerPointer();
		type_result _pointManagerInstance();
		void _initializeSettings();
		void _initializeSettingsToDefaultSettingsOrReleaseBoth();
		void _attachNewManagerInterfaceToNodeSelector();
		
	protected:
		NEPanelManager* _panel_manager;
		NEScriptEditor* _script_editor;
		NEEventHandler* _event_handler;
		
	protected:
		NEExportable::Identifier _panel_manager_identifier;
		NEExportable::Identifier _script_editor_identifier;
		NEExportable::Identifier _event_handler_identifier;
		ModifiableSettings _settings;
		ModifiableSettings _default_settings;
		bool _is_setting_initialized;
	
	public:
		static type_result setInstance(Editor& new_instance_to_set);
		static Editor& getInstance();
		static type_result saveSettings();
		
	protected:
		static Editor* _instance;
	};
}
