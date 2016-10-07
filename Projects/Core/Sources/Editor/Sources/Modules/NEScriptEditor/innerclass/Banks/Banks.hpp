class NE_DLL Banks : public NETVector<NEBank*, true>, public NEInitializable
{
public:
	typedef NEScriptEditor::Banks ThisClass;
	typedef NETVector<NEBank*, true> SuperClass;

public:
	const NEBank& getBank(const NECodeType& type) const;
	NEBank& getBank(const NECodeType& type);

public:
	virtual type_result initialize();
	virtual NEType::Type getType() const;
	virtual NEObject& clone() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
};