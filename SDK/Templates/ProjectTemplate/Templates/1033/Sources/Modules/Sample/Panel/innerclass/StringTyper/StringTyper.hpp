class NE_DLL StringTyper : public NETextComponent
{
public:
	virtual type_result _onUpdate(NEPanel& panel);
	virtual type_result _onLoad(NEPanel& panel);
	virtual type_result _onFocus(NEPanel& panel);

public:
	virtual NEObject& clone() const;
};
