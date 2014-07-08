//	---------------------------------------------------------------------------------
//	클래스명:	Kernal::KernalHeader
//	설명	:	노드엔진의 헤더를 나타낸다.
//	관계	:	기반클래스.			NEObject
//	특성	:	중첩클래스.
//	알고리즘:	
//	사용방법:	
//	메모	:	모듈의 헤더와는 다르다.
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
class NE_DLL ScriptHeader : public NEExportable::Header
{
	typedef NEExportable::Header SuperClass;
	typedef NEScriptManager::ScriptHeader ThisClass;

	//	friend 선언
	friend class ScriptManager;

	//	생성자:
public:
	ScriptHeader();
	ScriptHeader(const ThisClass& source);

	//	소멸자:
public:
	virtual ~ScriptHeader();

public:
	const ScriptHeader& operator=(const ThisClass& source);
	bool operator==(const ThisClass& source) const;
	bool operator!=(const ThisClass& source) const;

	//	인터페이스:
	//		상속:
	//			NEScriptManager::ScriptHeader:	
public:
	type_index setMaxNameCodeIndex(type_index max_name_code_index);
	type_index getMaxNameCodeIndex() const;
	type_result setMaxScriptCodeIndex(type_index max_script_code_index);
	type_index getMaxScriptCodeIndex() const;
	type_result setMaxGroupCodeIndex(type_index max_group_code_index);
	type_index getMaxGroupCodeIndex() const;
	type_result setMaxPriorityCodeIndex(type_index max_priority_code_index);
	type_index getMaxPriorityCodeIndex() const;
	type_result setMaxNodeLength(type_index max_node_length);
	type_index getMaxNodeLength() const;
	type_result setMaxModuleLength(type_index max_module_length);
	type_index getMaxModuleLength() const;
	type_result setMaxKeyLength(type_index max_key_length);
	type_index getMaxKeyLength() const;
	//			NEObject:
public:
	virtual void release();
	virtual type_result isValid() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual NEObject& clone() const;

private:
	const ScriptHeader& _assign(const ThisClass& source);
	void _release();

protected:
	type_index _max_scriptcode_index;
	type_index _max_namecode_index;
	type_index _max_groupcode_index;
	type_index _max_prioritycode_index;
	type_index _max_node_length;
	type_index _max_module_length;
	type_index _max_key_length;
};
