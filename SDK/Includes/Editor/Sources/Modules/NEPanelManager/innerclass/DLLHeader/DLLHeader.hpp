typedef NEPanelList (NE_FUNCTION_CALL *PanelEntryPoint)(void);

class NE_DLL DLLHeader : public NEObject
{
	//	생성자:
public:
	DLLHeader();
	DLLHeader(const DLLHeader& source);

	//	소멸자:
public:
	~DLLHeader();

public:
	bool operator==(const DLLHeader& source) const;
	bool operator!=(const DLLHeader& source) const;
	
	//	인터페이스:
	//		접근자:
public:
	virtual bool isLoadable() const = 0;
	virtual void setLoadable(bool loadable) = 0;
	virtual NETString& getPath() = 0;
	virtual const NETString& getPath() const = 0;
	virtual const HINSTANCE getInstance() const = 0;
	virtual HINSTANCE getInstance() = 0;
	virtual void setInstance(HINSTANCE new_instance) = 0;
	virtual const PanelEntryPoint getPanelEntryPoint() const = 0;
	virtual PanelEntryPoint getPanelEntryPoint() = 0;
	virtual void setPanelEntryPoint(PanelEntryPoint new_entry_point) = 0;
	//		상속:
	//			NEObject:
public:
	virtual NEType::Type getType() const;
};
