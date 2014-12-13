#include "NEStandardScriptManager.hpp"
#include "../define/define.hpp"

namespace NE
{
	/*
		C4355경고 무시:
			경고가 나오는 이유:
				일반적으로, this 포인터를 넘기면, 넘긴쪽에서 생성자가 초기화되지
				않았는데도, 넘겨받은 쪽에서 사용할 여지가 있기 때문이다.
			무시하는 이유:
				아래와 같은 경우, 절대로 "생성자에서 호출 하지 않으"므로 사용한다.
	*/
#pragma warning(push)	
#pragma warning(disable:4355)
	NE_DLL NEStandardScriptManager::NEStandardScriptManager()
		: NEScriptManager(), _scriptset(*this)	//	C4355 Warning.
	{	
		_release();
	}

	NE_DLL NEStandardScriptManager::NEStandardScriptManager(const NEStandardScriptManager& source)
		: NEScriptManager(source), _scriptset(*this)	//	C4355 Warning.
	{
		_assign(source);
	}
#pragma warning(pop)

	NE_DLL NEStandardScriptManager::~NEStandardScriptManager()
	{
		_release();
	}

	NETString NE_DLL NEStandardScriptManager::getScriptFilePath() const
	{
		return _loaded_script_path;
	}

	const NEScriptHeader NE_DLL &NEStandardScriptManager::getScriptHeader() const
	{
		return _script_header;
	}

	const NERootNodeCodeSet NE_DLL &NEStandardScriptManager::getScriptNodes() const
	{
		return _scriptset;
	}

	type_result NE_DLL NEStandardScriptManager::initialize()
	{
		SuperClass::initialize();
		const NEScriptHeader& header = getScriptHeader();
		type_result result = header.isValid();
		if(NEResult::hasError(result))
		{
			ALERT_ERROR(" : ScriptManager의 Header가 손상되었습니다. 초기화를 중단합니다.");
			return RESULT_TYPE_ERROR;
		}



		//	main:		
		//		왜 rootNodecodeSet을 먼저 정의하는가:
		//			내부에서 release를 호출하는데, 실제 데이터가 존재하는 _getNodeSet이 먼저
		//			초기화되면, RootCodeSet은 대글링포인터가 되버리기 때문이다.
		//		스크립트셋을 초기화:
		_getScriptNodes().release();
		//		버퍼를 스크립트 헤더에 맞게 초기화:
		result |= _getNodeSet().create(header.getMaxNodeLength());
		result |= _getModuleSet().create(header.getMaxModuleLength());
		result |= _getKeySet().create(header.getMaxKeyLength());
		//		숏컷을 초기화:		
		result |= _createShortCutSetAndFillWithShortCuts(_getScriptShortCutSet(), header.getMaxScriptCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getNameShortCutSet(), header.getMaxNameCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getGroupShortCutSet(), header.getMaxGroupCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getPriorityShortCutSet(), header.getMaxPriorityCodeIndex() + 1);		

		return result;
	}

	const NEExportable::ModuleHeader NE_DLL &NEStandardScriptManager::getHeader() const
	{
		static NEExportable::ModuleHeader _header;
		
		if(_header.isValid() != RESULT_SUCCESS)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getVersion()  = _T(_VERSION);			
			_header.getComment() = _T(_COMMENT);
			_header.setMaxErrorCodeCount(NEStandardScriptManager::END_OF_ERROR_CODE - 1);
		}
		
		return _header;
	}

	LPCTSTR NE_DLL NEStandardScriptManager::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");
		case SCRIPT_FILENAME_IS_NOT_VALID:
			return _T("잘못된 스크립트 파일이름");
		case SCRIPT_FILEHEADER_IS_NOT_VALID:
			return _T("잘못된 파일헤더");
		case SCRIPTSET_IS_NOT_VALID:
			return _T("잘못된 스크립트셋");
		default:
			return _T("알수 없는 에러");
		}
	}

	type_result NE_DLL NEStandardScriptManager::execute()
	{
		return RESULT_SUCCESS;
	}

	NERootNodeCodeSet NE_DLL &NEStandardScriptManager::_getScriptNodes()
	{
		return _scriptset;
	}

	NEScriptHeader NE_DLL &NEStandardScriptManager::_getScriptHeader()
	{
		return _script_header;
	}

	void NE_DLL NEStandardScriptManager::release()
	{
		//	왜 release 순서가 뒤바뀌어야 하는가:
		//		NENodeCodeSet이 release가 될때 내부에서 while(length) pop();을 수행하므로
		//		실제 인스턴스가 있는지 참조하려 들기 때문이다.
		//		실제 인스턴스는 SuperClass에 들어있으므로 이를 먼저 초기화 해버리면
		//		널포인트 참조가 되버려서 에러가 발생한다.
		_release();

		SuperClass::release();
	}

	NEObject NE_DLL &NEStandardScriptManager::clone() const
	{
		return *(new NEStandardScriptManager(*this));
	}
	
	NEBinaryFileSaver NE_DLL &NEStandardScriptManager::serialize(NEBinaryFileSaver& saver) const
	{
		//	왜 NEScriptHeader를 앞에 저장하는가:
		//		NodeManager에서 같은 스크립트 파일인지를 확인하기 위해서는, 스크립트파일의 헤더가 필요한데
		//		이 헤더가 앞에있어야 가져올수 있다.
		SuperClass::serialize(saver);

		return saver << _script_header << _scriptset;
	}

	NEBinaryFileLoader NE_DLL &NEStandardScriptManager::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		//		왜 release를 수행하는 가:
		//			scriptset이 shortcut, nodeset, bank와 모두 밀접한 관련이 있다.
		//			따라서, SuperClass에서 ShortCut부터 serialize를 수행하려는 순간
		//			에러가 발생하게 된다.
		release();
		SuperClass::serialize(loader);

		_loaded_script_path = loader.getLastElement().getFilePath(); //	스크립트경로는 serialize시 자동으로 할당된다
		
		loader >> _script_header >> _scriptset;
		
		//	post:
		//		노드매니져 부트:	숏컷의 크기를 로드한 스크립트 헤더(_script_header)로 확장
		//							하고, 메인스크립트(0)을 로드한다.
		//			이렇게 스크립트를 읽을 때마다 매번 노드매니져를 리붓하면, 오작동이 일어나지는 않나?:
		//				다음과 같은 시나리오가 "스크립트 로드시, 노드매니져 리붓"에 대한 최악의 시나리오 중의 하나다.
		//					시나리오1. 초기, A 시나리오를 로드한다.
		//					시나리오2. 노드 매니져 부트후, 여러가지 노드를 생성한다.
		//					시나리오3. 그 도중, 다른 노드데이터 파일(*.nodedata)을 로드한다.
		//					시나리오4. 노드데이터 파일을 로드하는 중, 스크립트의 헤더가 노드데이터 파일과 불일치 하고
		//								있음을 커널에서 판단한다.
		//					시나리오5. 커널은 노드데이터의 헤더와 일치하는 헤더를 갖고 있는 스크립트 파일을 검색한다.
		//					시나리오6. 검색한 스크립트 파일을 로드한다.
		//					시나리오7. *** 이때 노드매니져가 한번 부트(= 초기화) 된다. ***
		//					시나리오8. 스크립트 파일 로드후, PC가 노드매니져쪽으로 들어온다. 
		//					시나리오9. 노드매니져에서 다시 초기화를 수행하고, 노드데이터를 다시 읽기 시작한다.
		//				결국, 다소의 효율적인 손실은 있지만, 어느 시나리오에서건(= 거의) 스크립트 파일을 로드후, 노드매니져
		//				초기화 하는 방식이 더 프로그램을 유지시켜주는 방법이라는 걸 알 수 있다.
		//				스크립트 데이터를 로드후, 노드매니져를 부트하지 않으면, 존재하지 않는 스크립트에 대한 노드가 존재하게 
		//				되면서 "좀 더 확장성 있는 프로그램이 가능" 하다고 생각되었으나, 노드의 모든 원형은 스크립트 매니져에
		//				존재한다는 원칙이 깨지게 된다. 
		//				프로그램의 안정성을 위해서 로드후 바로 부트를 하는 방법이 좋다고 생각된다.

		//			타겟팅:
		NENodeManager& node_manager = Kernal::getInstance().getNodeManager();
		if(&node_manager)
			//			부트:
			node_manager.initialize(); // 여기서 ShortCut이 NEScriptHeader에 맞췃 초기화되고, 메인 스크립트가 자동으로 NodeManager로 fetch 된다.
		
		return loader;
	}

	type_result NE_DLL NEStandardScriptManager::isValid() const
	{			
		type_result result = NEScriptManager::isValid();
		if(NEResult::hasError(result) == true) return result | MODULE_IS_NOT_VALID;
		result = _loaded_script_path.isValid();
		if(NEResult::hasError(result) == true) return result | SCRIPT_FILENAME_IS_NOT_VALID;
		result = _script_filename.isValid();
		if(NEResult::hasError(result) == true) return result | SCRIPT_FILENAME_IS_NOT_VALID;
		result = _script_header.isValid();		
		if(NEResult::hasError(result) == true) return result | SCRIPT_FILEHEADER_IS_NOT_VALID;
		result = _scriptset.isValid();
		if(NEResult::hasError(result) == true) return result | SCRIPTSET_IS_NOT_VALID;

		return RESULT_SUCCESS;
	}

	void NEStandardScriptManager::_release()
	{
		_loaded_script_path.release();
		_script_filename.release();		
		_script_header.release();
		_scriptset.release();
	}

	const NEStandardScriptManager NE_DLL &NEStandardScriptManager::_assign(const NEStandardScriptManager& source)
	{
		if(this == &source) return *this;
		
		_loaded_script_path = source._loaded_script_path;
		_script_filename = source._script_filename;
		_script_header = source._script_header;
		_scriptset = source._scriptset;
		
		return *this;		
	}

	const NEStandardScriptManager NE_DLL &NEStandardScriptManager::operator=(const NEStandardScriptManager& source)
	{
		NEScriptManager::operator=(source);
		
		return _assign(source);
	}
	
	bool NE_DLL NEStandardScriptManager::operator==(const NEStandardScriptManager& source) const
	{
		if(this == &source) return true;
		if(NEScriptManager::operator!=(source)) return false;
		if(_loaded_script_path != source._loaded_script_path) return false;
		if(_script_filename != source._script_filename) return false;
		if(_script_header != source._script_header) return false;
		if(_scriptset != source._scriptset) return false;
		
		return true;
	}

	bool NE_DLL NEStandardScriptManager::operator!=(const NEStandardScriptManager& source) const
	{
		return !(operator==(source));
	}

	type_result NE_DLL NEStandardScriptManager::_onFetchModule()
	{
		return RESULT_SUCCESS;
	}

	type_result NEStandardScriptManager::_onChangeNameCode(NENode& target, type_code new_namecode)
	{
		ALERT_ERROR(" : ");
		return RESULT_TYPE_ERROR;
	}

	type_result NEStandardScriptManager::_onChangePriorityCode(NENode& target, type_code new_prioritycode)
	{
		ALERT_ERROR(" : ");
		return RESULT_TYPE_ERROR;
	}

	type_result NEStandardScriptManager::_onChangeGroupCode(NENode& target, const NEIntSet& new_groupcodeset)
	{
		ALERT_ERROR(" : ");
		return RESULT_TYPE_ERROR;
	}
}