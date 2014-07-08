class NE_DLL ButtonConnector : public WND::WNDConnector
{
public:
	ButtonConnector();

public:
	~ButtonConnector();

public:
	virtual type_result connect(NEKeyCodeSet& keyset);

public:
	NEModuleSelector& getWindowSelector();
	const NEModuleSelector& getWindowSelector() const;
	NETStringKey& getCaption();
	const NETStringKey& getCaption() const;
	NEIntKey& getMenuId();
	const NEIntKey& getMenuId() const;

protected:
	void _release();

protected:
	NEModuleSelector* _window_selector;
	NETStringKey* _caption;
	NEIntKey* _menu_id;
};