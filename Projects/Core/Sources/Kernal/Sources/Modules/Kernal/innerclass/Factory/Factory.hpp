class NE_DLL Factory : public NEObject, public NEInitializable
{
public:
	Factory();
	Factory(const Settings& base_settings);
	Factory(const Factory& source);

public:
	virtual ~Factory();

public:
	const Factory& operator=(const Factory& source);
	bool operator==(const Factory& source) const;
	bool operator!=(const Factory& source) const;

public:
	NEExportable::Identifier& getNodeManagerIdentifier();
	const NEExportable::Identifier& getNodeManagerIdentifier() const;
	NEExportable::Identifier& getScriptManagerIdentifier();
	const NEExportable::Identifier& getScriptManagerIdentifier() const;
	Kernal::ModifiableSettings& getDefaultSettings();
	const Kernal::ModifiableSettings& getDefaultSettings() const;
	
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
	Kernal create();
	
protected:
	const Factory& _assign(const Factory& source);

protected:
	NEExportable::Identifier _node_manager_identifier;
	NEExportable::Identifier _script_manager_identifier;
	Kernal::ModifiableSettings _settings;
};
