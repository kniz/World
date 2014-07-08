class NE_DLL Flag : public NEObject
{
public:
	Flag();
	Flag(const TCHAR& source);
	Flag(const Flag& source);

public:
	virtual ~Flag();
	
public:
	const Flag& operator=(const Flag& source);
	bool operator==(const Flag& source) const;
	bool operator!=(const Flag& source) const;

public:
	virtual TCHAR getFlag() const;
	virtual void setFlag(TCHAR flag);
	virtual bool isLogShown() const;
	virtual void setLogShown(bool enable);
	virtual bool isConsoleShown() const;
	virtual void setConsoleShown(bool enable);
	virtual bool isMessageBoxShown() const;
	virtual void setMessageBoxShown(bool enable);
	virtual bool isDebugWindowShown() const;
	virtual void setDebugWindowShown(bool enable);

public:
	virtual NEType::Type getType() const;
	virtual void release();
	virtual type_result isValid() const;
	virtual NEObject& clone() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	
private:
	const Flag& _assign(const Flag& source);
	void _release();

protected:
	//	왜 TCHAR가 아니라 TCHAR여야 하는가?:
	//		UNICODE컴파일시, INI를 유니코드로 저장하기 때문에 INI가 WBCS인지 MBCS인지 알수
	//		없다. _flag는 INI로부터 데이터를 가져오므로 그에 맞춰서 데이터를 정할 필요가
	//		있다.
	TCHAR _flag;
};
