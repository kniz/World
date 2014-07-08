//	---------------------------------------------------------------------------------
//	클래스명:	NEExportable::ModuleHeader
//	설명	:	모듈의 헤더를 나타낸다.
//	관계	:	기반클래스.			Identifier
//				소유되는 클래스.	NEModule
//	특성	:	중첩클래스.
//	알고리즘:	
//	사용방법:	
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//				2011-07-09	이태훈	추가		버전 호환성 추가
//												version_compatibilities에 들어가 있는 
//												버전들은 하위 버전으로써, 이 모듈로도
//												실행이 가능하다는 뜻이다.
//	---------------------------------------------------------------------------------
class NE_DLL ModuleHeader : public Header
{
	//	생성자:
public:
	ModuleHeader();
	ModuleHeader(const ModuleHeader& source);

	//	소멸자:
public:
	virtual ~ModuleHeader();

	//	연산자 중첩:
public:
	const ModuleHeader& operator=(const ModuleHeader& source);
	bool operator==(const ModuleHeader& source) const;
	bool operator!=(const ModuleHeader& source) const;
	
public:
	NETStringSet& getModuleDependencies();
	const NETStringSet& getModuleDependencies() const;
	NEIntSet& getRevisionCompatibilities();
	const NEIntSet& getRevisionCompatibilities() const;
	type_count getMaxErrorCodeCount() const;
	void setMaxErrorCodeCount(type_count error_code);

	//	인터페이스:
	//		상속:
	//			NEObject:
public:
	virtual void release();
	virtual type_result isValid() const;
	virtual NEObject& clone() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual NEType::Type getType() const;

	//	내부함수:
private:	
	const ModuleHeader& _assign(const ModuleHeader& source);

	//	멤버변수:
protected:
	NETStringSet _module_dependencies; // 이 모듈이 의존하는 모듈
	NEIntSet _revision_compatibilities; // 호환 가능한 버전. 여기에 표시된 하위 버전은, 이 모듈로도 사용이 가능하다는 뜻.
	int _max_errorcode_count;
};
