//	값은 커널 생성시에만 기본적으로 주어지며, 커널내의 주요 변수들은 이 값들로
//	초기화된다.
//	디폴트 세팅은 팩토리로부터만 생성되며, 일단 커널이 생성되면 변경 할 수 없다.
//	이건 외부로부터(소스코드 및 INI) 로부터 변경되어지는 세팅이다.
class NE_DLL ModifiableSettings : public Settings
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
	NETString& getLocale();
	const NETString& getLocale() const;
	type_result setLogDirectory(const NETString& log_directory);
	const NETString& getLogDirectory() const;
	type_result setScriptDirectory(const NETString& script_directory);
	const NETString& getScriptDirectory() const;
	type_result setNodeDirectory(const NETString& node_directory);
	const NETString& getNodeDirectory() const;
	NEDebugManager::Flag& getDebugFlag();
	const NEDebugManager::Flag& getDebugFlag() const;

private:
	const ModifiableSettings& _assign(const ModifiableSettings& source);

protected:
	NETString _locale;
	NETString _log_directory;
	NETString _script_directory;
	NETString _node_directory;
	NEDebugManager::Flag _flag;
};
