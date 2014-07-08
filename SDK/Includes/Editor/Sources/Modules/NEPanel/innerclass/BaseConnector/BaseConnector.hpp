class NE_DLL BaseConnector
{
public:
	BaseConnector();
	BaseConnector(const BaseConnector& source);

public:
	~BaseConnector();

public:
	const BaseConnector& operator=(const BaseConnector& source);
	bool operator==(const BaseConnector& source) const;
	bool operator!=(const BaseConnector& source) const;

public:
	virtual type_result connect(NEComponentSet& componentset) = 0;
};
