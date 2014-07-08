class NE_DLL Factory : public NEObject, public NEInitializable
{
public:
	Factory();
	Factory(const Factory& source);

public:
	virtual ~Factory();

public:
	const Factory& operator=(const Factory& source);
	bool operator==(const Factory& source) const;
	bool operator!=(const Factory& source) const;

public:
	NEExportable::Identifier& getPanelManagerIdentifier();
	const NEExportable::Identifier& getPanelManagerIdentifier() const;
	NEExportable::Identifier& getScriptEditorIdentifier();
	const NEExportable::Identifier& getScriptEditorIdentifier() const;
	NEExportable::Identifier& getEventHandlerIdentifier();
	const NEExportable::Identifier& getEventHandlerIdentifier() const;
	ModifiableSettings& getDefaultSettings();
	const ModifiableSettings& getDefaultSettings() const;

public:
	virtual type_result initialize();

public:
	virtual void release();
	virtual NEType::Type getType() const;
	virtual type_result isValid() const;
	virtual NEObject& clone() const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;

public:
	Editor create();
	
protected:
	const Factory& _assign(const Factory& source);

protected:
	NEExportable::Identifier _panel_manager_identifier;
	NEExportable::Identifier _script_editor_identifier;
	NEExportable::Identifier _event_handler_identifier;
	Editor::ModifiableSettings _settings;
};
