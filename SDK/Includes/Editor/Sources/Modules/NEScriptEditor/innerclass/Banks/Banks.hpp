class NE_DLL Banks : public NEObject
{
	typedef NEScriptEditor::Banks ThisClass;
	typedef NEObject SuperClass;

public:
	Banks();
	Banks(const Banks& source);

public:
	~Banks();

public:
	const Banks& operator=(const Banks& source);
	bool operator==(const Banks& source) const;
	bool operator!=(const Banks& source) const;

public:
	virtual const NETStringList& getScriptBank() const;
	virtual const NETStringList& getNameBank() const;
	virtual const NETStringList& getGroupBank() const;
	virtual const NETStringList& getPriorityBank() const;
	virtual NETStringList& getScriptBank();
	virtual NETStringList& getNameBank();
	virtual NETStringList& getGroupBank();
	virtual NETStringList& getPriorityBank();
	
public:
	virtual type_result isValid() const;
	virtual NEType::Type getType() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual NEObject& clone() const;
	virtual void release();

private:
	const Banks& _assign(const Banks& source);

protected:
	NETStringList _script_bank;
	NETStringList _name_bank;
	NETStringList _group_bank;
	NETStringList _priority_bank;
};
