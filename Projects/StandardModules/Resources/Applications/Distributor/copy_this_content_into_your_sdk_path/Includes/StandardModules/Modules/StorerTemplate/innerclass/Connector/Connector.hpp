class NE_DLL Connector : public NEModule::BaseConnector
{
public:
	Connector();

public:
	~Connector();

public:
	virtual type_result connect(NEKeySet& keyset);

public:
	KeyClass& getStorage();
	const KeyClass& getStorage() const;

protected:
	KeyClass* _storage;
};