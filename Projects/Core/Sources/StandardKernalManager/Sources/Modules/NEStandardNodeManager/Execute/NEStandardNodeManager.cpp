#include "NEStandardNodeManager.hpp"
#include "../../NEStandardScriptManager/Execute/NEStandardScriptManager.hpp"
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
	NE_DLL NEStandardNodeManager::NEStandardNodeManager()
		: SuperClass(), _nodecodeset(*this)	//	C4355 Warning.
	{
		_release();
	}

	NE_DLL NEStandardNodeManager::NEStandardNodeManager(const ThisClass& source)
		: SuperClass(source), _nodecodeset(*this)	//	C4355 Warning.
	{
		_assign(source);
	}
#pragma warning(pop)

	NE_DLL NEStandardNodeManager::~NEStandardNodeManager()
	{
		_release();
	}
	
	const NEStandardNodeManager NE_DLL &NEStandardNodeManager::operator=(const ThisClass& source)
	{		
		SuperClass::operator=(source);
		
		return _assign(source);
	}

	bool NE_DLL NEStandardNodeManager::operator==(const ThisClass& source) const
	{
		if(this == &source) return true;
		
		if(SuperClass::operator!=(source)) return false;
		if(_local_stack != source._local_stack) return false;
		if(_nodecodeset != source._nodecodeset) return false;
		
		return true;
	}

	bool NE_DLL NEStandardNodeManager::operator!=(const ThisClass& source) const
	{
		return !(operator==(source));
	}

	NENodeManager::LocalStack NE_DLL &NEStandardNodeManager::getLocalStack()
	{
		return _local_stack;
	}

	const NENodeManager::LocalStack NE_DLL &NEStandardNodeManager::getLocalStack() const
	{
		return _local_stack;
	}

	NERootNodeCodeSet NE_DLL &NEStandardNodeManager::getRootNodes()
	{
		return _nodecodeset;
	}

	const NERootNodeCodeSet NE_DLL &NEStandardNodeManager::getRootNodes() const
	{
		return _nodecodeset;
	}

	type_result NE_DLL NEStandardNodeManager::initialize()
	{
		//	pre:
		release();		
		const NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		if( ! &scripter)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		const NEScriptManager::ScriptHeader& header = scripter.getScriptHeader();
		const NERootNodeCodeSet& scriptset = scripter.getScriptNodes();
		
		
		
		//	main:
		//		쇼컷 로드:	_initialize()에서는 숏컷이 초기화가 이루어질 뿐이다.
		//					여기서는, 스크립트의 헤더만큼 크기를 확장시킨다.
		//		RootNodeCodeSet의 크기ㅡ 정의:
		//			왜 rootNodecodeSet을 먼저 정의하는가:
		//				내부에서 release를 호출하는데, 실제 데이터가 존재하는 _getNodeSet이 먼저
		//				초기화되면, RootCodeSet은 대글링포인터가 되버리기 때문이다.
		type_result result = _nodecodeset.create(5000);
		//		버퍼 정의:
		result |= _getNodeSet().create(5000);
		result |= _getModuleSet().create(50000);
		result |= _getKeySet().create(100000);
		//		숏컷 정의:				  
		result |= _createShortCutSetAndFillWithShortCuts(_getScriptShortCutSet(), header.getMaxScriptCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getPriorityShortCutSet(), header.getMaxPriorityCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getNameShortCutSet(), header.getMaxNameCodeIndex() + 1);
		result |= _createShortCutSetAndFillWithShortCuts(_getGroupShortCutSet(), header.getMaxGroupCodeIndex() + 1);
		
		//		메인 스크립트 로드:	메인 스크립트는 1번이다.
		//			메인스크립트가 존재한다면:
		if(scriptset.getLengthLastIndex() >= _MAIN_SCRIPT_ID)
			//			메인스크립트 로드:
			_nodecodeset.push(scriptset.getElement(_MAIN_SCRIPT_ID));
		else	//	존재 하지 않는다면:
		{
			//			에러 출력:
			ALERT_INFORMATION("I201021C38 : 존재하지 않는 메인 스크립트\n스크립트 데이터에 메인스크립트를 비롯하여 어떠한 스크립트도 없습니다.\n따라서 커널은 어떠한 동작도 하지 않을 것입니다.")
			return result |= RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION | THERE_IS_NO_MAIN_SCRIPT;
		}

		return result;
	}

	const NEExportable::ModuleHeader NE_DLL &NEStandardNodeManager::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			//	아직 초기화가 안되었음
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getVersion()  = _T(_VERSION);
			_header.getComment() = _T(_COMMENT);
			_header.setMaxErrorCodeCount(NEStandardNodeManager::END_OF_ERROR_CODE - 1);

		}

		return _header;
	}

	LPCTSTR NE_DLL NEStandardNodeManager::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");
		case LOCALSTACK_IS_NOT_VALID:
			return _T("잘못된 FlagSet");
		case NODELIST_IS_NOT_VALID:
			return _T("콘솔 윈도우 로드 실패");
		case SCRIPT_SHORTCUTSET_IS_NOT_VALID:
			return _T("콘솔 윈도우 언로드 실패");
		case NAME_SHORTCUTSET_IS_NOT_VALID:
			return _T("잘못된 이름 숏컷셋");
		case GROUP_SHORTCUTSET_IS_NOT_VALID:
			return _T("잘못된 그룹 숏컷셋");
		case PRIORITY_SHORTCUTSET_IS_NOT_VALID:
			return _T("잘못된 우선권 숏컷셋");
		case THERE_IS_NO_MAIN_SCRIPT:
			return _T("메인스크립트의 부재(스크립트 No. 0)");
		case DUMMY_NODE:
			return _T("알수없는(Unknown) 노드로 인한 등록 실패");
		case NOT_NEED_TO_CHANGE:
			return _T("재등록할 필요가 없는 동일한 데이터");
		case FAIL_TO_REGISTER_SCRIPT_CODE:
			return _T("노드의 스크립트 코드를 숏컷에 등록 실패");
		case FAIL_TO_UNREGISTER_SCRIPT_CODE:
			return _T("노드의 스크립트 코드를 숏컷에 등록 해제 실패");
		case FAIL_TO_REGISTER_NAME_CODE:
			return _T("노드의 네임 코드를 숏컷에 등록 실패");
		case FAIL_TO_UNREGISTER_NAME_CODE:
			return _T("노드의 네임 코드를 숏컷에 등록 해제 실패");
		case FAIL_TO_REGISTER_GROUP_CODE:
			return _T("노드의 그룹 코드를 숏컷에 등록 실패");
		case FAIL_TO_UNREGISTER_GROUP_CODE:
			return _T("노드의 그룹 코드를 숏컷에 등록 해제 실패");
		case FAIL_TO_REGISTER_PRIORITY_CODE:
			return _T("노드의 우선권 코드를 숏컷에 등록 실패");
		case FAIL_TO_UNREGISTER_PRIORITY_CODE:
			return _T("노드의 우선권 코드를 숏컷에 등록 해제 실패");		
		case THERE_IS_NO_SCRIPT_FILE_PROPER:
			return _T("적절한 스크립트 파일 검색 실패");
		default:
			return _T("알수 없는 에러");
		}
	}

	type_result NE_DLL NEStandardNodeManager::execute()
	{
		//	pre:
		//		멤버변수 검사:
		if(_enable == false) return RESULT_SUCCESS;
		//		타겟팅:
		NEShortCutSet& priority_shortcutset = _getPriorityShortCutSet();
		NEIndexedNodeSet& nodeset = _getNodeSet();



		//	main:	우선권을 고려해서 루프를 돌며 낮은 순위로 실행한다.
		//		우선순위 별:
		int index = 0;

		for(int n=0; n < priority_shortcutset.getLength() ;n++)
		{
			//		해당 우선순위의 모든 노드를 실행:
			//			타겟팅:
			NEShortCut& priority_shortcut = priority_shortcutset[n];
			//			루핑:
			for(NEShortCut::Iterator* iterator=priority_shortcut.getIterator(0)	;
				iterator != NE_NULL										;
				iterator = iterator->getNext()							)
			{
				NENode& node = nodeset.getElement(iterator->getValue());
				node.execute();
#ifdef PRINT_INFO
				cout << "\n\n<-------노드매니져:" << index++ << " 번 노드---------->\n\n\n";			
#endif
			}
		}	



		//	post:
		//		왜 로컬스택을 초기화하는가:
		//			이전 프레임의 정보가 그대로 남아있다면, 영향을 받게되는 건 다음프레임
		//			에서 가장 처음으로 실행되는 노드가 된다.
		//			그런데, 이걸 예측하기가 힘들다. 그러므로 이런식으로는 동작되지 않도록
		//			하기 위함이 첫번째다.
		//			두번째는, 로컬스택은 포인터로 이루어져있기 때문에 이를 저장하는 것이
		//			곤란하다는데 있다.
		int frame_count_buffer = _local_stack._frame_count++;
		_local_stack.release();
		_local_stack._frame_count = frame_count_buffer;
		return RESULT_SUCCESS;
	}

	void NE_DLL NEStandardNodeManager::release()
	{
		//	왜 release 순서가 뒤바뀌어야 하는가:
		//		NENodeCodeSet이 release가 될때 내부에서 while(length) pop();을 수행하므로
		//		실제 인스턴스가 있는지 참조하려 들기 때문이다.
		//		실제 인스턴스는 SuperClass에 들어있으므로 이를 먼저 초기화 해버리면
		//		널포인트 참조가 되버려서 에러가 발생한다.
		_release();

		SuperClass::release();
	}

	type_result NE_DLL NEStandardNodeManager::isValid() const
	{
		type_result result = NEModule::isValid();
		if(NEResult::hasError(result) == true) return result | MODULE_IS_NOT_VALID;
		result = _local_stack.isValid();
		if(NEResult::hasError(result) == true) return result | LOCALSTACK_IS_NOT_VALID;
		result = _nodecodeset.isValid();
		
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NEStandardNodeManager::clone() const
	{
		return *(new ThisClass(*this));
	}

	NEBinaryFileLoader NE_DLL &NEStandardNodeManager::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		//		왜 release를 수행하는 가:
		//			scriptset이 shortcut, nodeset, bank와 모두 밀접한 관련이 있다.
		//			따라서, SuperClass에서 ShortCut부터 serialize를 수행하려는 순간
		//			에러가 발생하게 된다.
		release();		
		SuperClass::serialize(loader);		
		//		타겟팅:
		const NEScriptManager& scripter = Kernal::getInstance().getScriptManager();
		const NEScriptManager::ScriptHeader& script_header = scripter.getScriptHeader();
		const Kernal::ModifiableSettings& settings = Kernal::getInstance().getSettings();
		//		변수 정의:
		NETString script_path;
		NEScriptManager::ScriptHeader& header = NEStandardScriptManager::StandardScriptHeader(); // StandardScripter.operator==(ScriptHeader)는 안되므로, 속편하게 처음부터 레퍼런스로 잡는다
		


		//	main:
		//		데이터 및 인스턴스 로드:
		_setSynchronizationDisabled(true);


		loader >> script_path >> header >> _local_stack >> _nodecodeset;
		
		_setSynchronizationDisabled(false);

		//		스크립트 파일 확인:	현재 로드된 스크립트파일과 같은 데이터파일인지 헤더를 통해서 확인한다.		
		if(	script_path != scripter.getScriptFilePath()	||
			header != script_header						)
		{
			ALERT_WARNING("W201021C38 : 노드데이터와 일치하지 않는 잘못된 스크립트파일\n읽으려는 노드데이터와 이미 읽은 스크립트 데이터가 맞지않는 잘못된 스크립트 파일 입니다.\n커널에서는 읽으려는 노드데이터와 맞는 스크립트를 자동으로 검색하여 읽을 것입니다.\n일치하지 않는다고 판단된 기존 스크립트 파일경로 : %s", scripter.getScriptFilePath().toCharPointer())
			//		노드데이터에 알맞는 스크립트 파일을 로드:
			//			경로 설정:
			//				타겟팅:
			
			NETString path = settings.getScriptDirectory() + _T("/*.") + settings.getScriptExtractor();
			//			스크립트 폴더에^서 검색:
			type_result result = _loadScriptDataCorrspondingToNodeData(path, header);
			//			검색 결과:
			if(NEResult::CouldNotFindData(result))
				ALERT_ERROR(" : ")
		}		
		
		return loader;
	}

	NEBinaryFileSaver NE_DLL &NEStandardNodeManager::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);		
		const NEScriptManager& scripter = Kernal::getInstance().getScriptManager();	
		
		return saver << scripter.getScriptFilePath() << scripter.getScriptHeader() << _local_stack << _nodecodeset;		
	}

	void NEStandardNodeManager::_release()
	{
		_setSynchronizationDisabled(true);

		_local_stack.release();
		_nodecodeset.release();

		_setSynchronizationDisabled(false);
	}
	const NEStandardNodeManager& NEStandardNodeManager::_assign(const ThisClass& source)
	{
		if(this == &source) return *this;
		
		_local_stack  = source._local_stack;
		_nodecodeset = source._nodecodeset;
		
		return *this;
	}
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-20	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEStandardNodeManager::_loadScriptDataCorrspondingToNodeData(NETString& path, NEScriptManager::ScriptHeader& header) const
	{
		//	pre:
		//		타겟팅:		
		NEScriptManager& scripter = Kernal::getInstance().getScriptManager();		



		//	main:	데이터 로드:
		//		로드 준비:
		NEBinaryFileLoader loader;
		loader.setPath(path.toCharPointer());
		loader.setSearchLowerDirectory(true);
		//		루핑:
		while(true)
		{
			loader.findFile();
			const NEFileSystem::TaskUnit& task = loader.getLastElement();
			if( ! &task) break;
			//		헤더 비교:	파일명은 일치한다.
			loader.open();
			NEStandardScriptManager::StandardScriptHeader scriptheader;
			loader >> scriptheader;

			if(header == scriptheader)
			{			
				ALERT_INFORMATION("I201021C16 : 새로운 스크립트 파일 읽기 성공\n읽으려는 노드데이터와 맞는 스크립트 파일을 찾았습니다.\n커널에서 자동으로 스크립트 데이터를 읽을 것입니다.\n이전에 로드했던 스크립트 파일 : %s\n새로운 스크립트 파일 : %s", scripter.getScriptFilePath().toCharPointer(), task.getFilePath())

				loader.setPosition(0);
				loader >> scripter;
				loader.close();											

				return RESULT_SUCCESS;
			}

			loader.close();
		}

		ALERT_ERROR("E201021C15 : 노드데이터 파일의 스크립트 파일 검색 실패\n노드데이터 파일(*.nodedata)에 맞는 스크립트 파일(*.script)을 스크립트 디렉토리에서 검색했으나 찾지 못했습니다.\n스크립트 파일을 이동 및 삭제 했거나, 노드데이터 파일이 손상되지 않았나 확인해 보십시오.\n스크립트 디렉토리 경로 : %s\n찾아야할 스크립트 헤더:\n\t제목 : %s\n\t개발자 : %s\n\t개정횟수 : %d\n\t버전 : %s\n\t날짜 : %s\n\t설명 : %s\n\t연락처 : %s", Kernal::getInstance().getSettings().getScriptDirectory().toCharPointer(), header.getName().toCharPointer(), header.getDeveloper().toCharPointer(), header.getRevision(), header.getVersion() .toCharPointer(), header.getReleaseDate().toCharPointer(), header.getComment().toCharPointer(), header.getContact().toCharPointer())

		return RESULT_COULDNOT_FIND_DATA | THERE_IS_NO_SCRIPT_FILE_PROPER;
	}

	type_result NE_DLL NEStandardNodeManager::_onModuleFetched()
	{
		return RESULT_SUCCESS;
	}
}