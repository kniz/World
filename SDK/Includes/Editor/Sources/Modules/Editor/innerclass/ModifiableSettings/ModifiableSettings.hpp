class NE_DLL ModifiableSettings : public NEObject
{
public:
	ModifiableSettings();
	ModifiableSettings(const ModifiableSettings& source);

public:
	virtual ~ModifiableSettings();

public:
	const ModifiableSettings& operator=(const ModifiableSettings& source);
	bool operator==(const ModifiableSettings& source) const;
	bool operator!=(const ModifiableSettings& source) const;

public:
	virtual void release();
	virtual type_result isValid() const;
	virtual NEObject& clone() const;
	NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual NEType::Type getType() const;

public:
	const NETString& getPanelDirectory() const;
	type_result setPanelDirectory(const NETString& panel_directory);
	bool isLoadedFromINI() const;
	void setLoadFromINI(bool enable);

protected:
	type_result _fixWhenDirectoryHasNotSlashAtTheEnd(NETString& directory_string_to_be_validate) const;


private:
	const ModifiableSettings& _assign(const ModifiableSettings& source);

protected:
	NETString _panel_directory;
	bool _is_loading_from_ini;
};
