class NE_DLL AndOperationSwitch : public NESwitchComponent
{
public:
	virtual NEObject& clone() const;

protected:
	virtual type_result _onLoad(NEPanel& panel);
	virtual type_result _onFocus(NEPanel& panel);
	virtual type_result _onUpdate(NEPanel& panel);
};
