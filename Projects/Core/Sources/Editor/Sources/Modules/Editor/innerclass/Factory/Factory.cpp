#include "../../Editor.hpp"
#include "../../define/define.hpp"

namespace NE
{
	NE_DLL Editor::Factory::Factory()
		: NEObject()
	{
		initialize();
	}

	NE_DLL Editor::Factory::Factory(const Editor::Factory& source)
		: NEObject(source)
	{
		_assign(source);
	}

	NE_DLL Editor::Factory::~Factory()
	{

	}

	const Editor::Factory NE_DLL &Editor::Factory::operator=(const Editor::Factory& source)
	{
		if(this == &source) return *this;
		
		return _assign(source);
	}

	bool NE_DLL Editor::Factory::operator==(const Editor::Factory& source) const
	{
		if(this == &source) return true;
		if(_panel_manager_identifier != source._panel_manager_identifier) return false;
		if(_script_editor_identifier != source._script_editor_identifier) return false;
		if(_event_handler_identifier != source._event_handler_identifier) return false;
		if(_settings != source._settings) return false;

		return true;
	}

	bool NE_DLL Editor::Factory::operator!=(const Editor::Factory& source) const
	{
		return ! operator==(source);
	}

	type_result NE_DLL Editor::Factory::initialize()
	{
		//	pre:
		release();



		//	main:
		//		_default_settings:
		_panel_manager_identifier.getName() = _T(_DEFAULT_PANEL_MANAGER_IDENTIFIER_NAME);
		_panel_manager_identifier.getDeveloper() = _T(_DEFAULT_PANEL_MANAGER_IDENTIFIER_DEVELOPER);
		_panel_manager_identifier.setRevision(_DEFAULT_PANEL_MANAGER_IDENTIFIER_REVISION);
		_script_editor_identifier.getName() = _T(_DEFAULT_SCRIPT_EDITOR_IDENTIFIER_NAME);
		_script_editor_identifier.getDeveloper() = _T(_DEFAULT_SCRIPT_EDITOR_IDENTIFIER_DEVELOPER);
		_script_editor_identifier.setRevision(_DEFAULT_SCRIPT_EDITOR_IDENTIFIER_REVISION);
		_event_handler_identifier.getName() = _T(_DEFAULT_EVENT_HANDLER_IDENTIFIER_NAME);
		_event_handler_identifier.getDeveloper() = _T(_DEFAULT_EVENT_HANDLER_IDENTIFIER_DEVELOPER);
		_event_handler_identifier.setRevision(_DEFAULT_EVENT_HANDLER_IDENTIFIER_REVISION);

		return RESULT_SUCCESS;
	}

	void NE_DLL Editor::Factory::release()
	{
		_panel_manager_identifier.release();
		_script_editor_identifier.release();
		_event_handler_identifier.release();
		_settings.release();
	}

	NEType::Type NE_DLL Editor::Factory::getType() const
	{
		return NEType::EDITOR_FACTORY;
	}

	type_result NE_DLL Editor::Factory::isValid() const
	{
		type_result result = _panel_manager_identifier.isValid();
		if(NEResult::hasError(result)) return result;
		result = _script_editor_identifier.isValid();
		if(NEResult::hasError(result)) return result;
		result = _event_handler_identifier.isValid();
		if(NEResult::hasError(result)) return result;
		result = _settings.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &Editor::Factory::clone() const
	{
		return *(new Factory(*this));
	}

	NEBinaryFileSaver NE_DLL &Editor::Factory::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _panel_manager_identifier << _script_editor_identifier << _event_handler_identifier << _settings;
	}

	NEBinaryFileLoader NE_DLL &Editor::Factory::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _panel_manager_identifier >> _script_editor_identifier >> _event_handler_identifier >> _settings;
	}

	Editor NE_DLL Editor::Factory::create()
	{
		//	main:
		Editor editor;
		editor._panel_manager_identifier = _panel_manager_identifier;
		editor._script_editor_identifier = _script_editor_identifier;
		editor._event_handler_identifier = _event_handler_identifier;
		editor._settings = _settings;
		editor._default_settings = _settings;

		return editor;
	}

	NEExportable::Identifier NE_DLL &Editor::Factory::getPanelManagerIdentifier()
	{
		return _panel_manager_identifier;
	}

	const NEExportable::Identifier NE_DLL &Editor::Factory::getPanelManagerIdentifier() const
	{
		return _panel_manager_identifier;
	}

	NEExportable::Identifier NE_DLL &Editor::Factory::getScriptEditorIdentifier()
	{
		return _script_editor_identifier;
	}

	const NEExportable::Identifier NE_DLL &Editor::Factory::getScriptEditorIdentifier() const
	{
		return _script_editor_identifier;
	}

	NEExportable::Identifier NE_DLL &Editor::Factory::getEventHandlerIdentifier()
	{
		return _event_handler_identifier;
	}

	const NEExportable::Identifier NE_DLL &Editor::Factory::getEventHandlerIdentifier() const
	{
		return _event_handler_identifier;
	}

	Editor::ModifiableSettings NE_DLL &Editor::Factory::getDefaultSettings()
	{
		return _settings;
	}

	const Editor::ModifiableSettings NE_DLL &Editor::Factory::getDefaultSettings() const
	{
		return _settings;
	}
	
	const Editor::Factory& Editor::Factory::_assign(const Factory& source)
	{
		if(this == &source) return *this;
		
		_panel_manager_identifier = source._panel_manager_identifier;
		_script_editor_identifier = source._script_editor_identifier;
		_event_handler_identifier = source._event_handler_identifier;
		
		return *this;
	}
}
