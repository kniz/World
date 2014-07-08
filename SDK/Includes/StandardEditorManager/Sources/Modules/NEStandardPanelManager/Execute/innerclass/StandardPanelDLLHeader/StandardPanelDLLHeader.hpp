class NE_DLL StandardPanelDLLHeader : public NEPanelManager::DLLHeader
{
	//	생성자:
public:
	StandardPanelDLLHeader();
	StandardPanelDLLHeader(const StandardPanelDLLHeader& source);

	//	소멸자:
public:
	~StandardPanelDLLHeader();

	//	인터페이스:
	//		접근자:
public:
	virtual bool isLoadable() const;
	virtual void setLoadable(bool loadable);
	virtual NETString& getPath();
	virtual const NETString& getPath() const;
	virtual const HINSTANCE getInstance() const;
	virtual HINSTANCE getInstance();
	virtual void setInstance(HINSTANCE new_instance);
	virtual const PanelEntryPoint getPanelEntryPoint() const;
	virtual PanelEntryPoint getPanelEntryPoint();
	virtual void setPanelEntryPoint(PanelEntryPoint new_entry_point);
	//		상속:
	//			NEObject:
public:
	virtual void release();
	virtual type_result isValid() const;
	virtual NEObject& clone() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	
private:
	const StandardPanelDLLHeader& _assign(const StandardPanelDLLHeader& source);
	
protected:
	bool _loadable;
	NETString _path;
	HINSTANCE _instance;
	PanelEntryPoint _entrypoint;
};
