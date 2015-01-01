#include "NENode.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENode::NENode()
		: SuperClass(NECodeType::SCRIPT, NECodeType::NAME),
		_priority(NECodeType(NECodeType::PRIORITY)),
		_groupcodeset(NECodeType(NECodeType::GROUP))
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENode::NENode(const NENode& source)
		: SuperClass(source), _is_rootnode(false), _owner(NE_NULL),
		_priority(NECodeType(NECodeType::PRIORITY)),
		_groupcodeset(NECodeType(NECodeType::GROUP))
	{
		_assign(source);
	}

	

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENode::~NENode()
	{
		_onUnlisted();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NENode NE_DLL &NENode::operator=(const NENode& source) 
	{
		//	pre:
		//		check:
		if(this == &source) return *this;
		//		superclass:
		//			unlist:
		//				타겟팅:		
		bool is_enlisted = isEnlisted();
		//				동작:
		_onUnlisted();
		//			복사:
		SuperClass::operator=(source);
		

		//	main:
		_assign(source);


		//	post:
		//		reEnlist:
		if(is_enlisted)
			_onEnlisted();

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NENode::operator==(const NENode& source) const
	{
		if(this == &source) return true;
		if(SuperClass::operator==(source) == false) return false;
		if(_modulecodeset != source._modulecodeset) return false;
		if(_groupcodeset != source._groupcodeset) return false;
		if(_priority != source._priority) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NENode::operator!=(const NENode& source) const
	{
		return !(operator==(source));
	}



	NEModuleCodeSet NE_DLL &NENode::getModuleSet()
	{
		return _modulecodeset;
	}

	const NEModuleCodeSet NE_DLL &NENode::getModuleSet() const
	{
		return _modulecodeset;
	}

	

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NENode::execute()
	{	
		//	pre:
		if( ! isEnable()) return RESULT_SUCCESS;
		NEEnlistableManager& manager = getManager();
		if(getManager().getType() != NEType::NENODE_MANAGER)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}


		//	main:
		//		타겟팅:
		NENodeManager& noder = static_cast<NENodeManager&>(manager);
		//		로컬 스택 변경:
		noder.getLocalStack()._setRecentNode(*this);		
		//		모듈셋 실행:
		_modulecodeset.execute();

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NENode::getType() const
	{
		return NEType::NENODE;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NENode::release() 
	{
		SuperClass::release();

		return _release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NENode::isValid() const 
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result) == true) return result;
		result = _modulecodeset.isValid();
		if(NEResult::hasError(result) == true) return result;
		result = _keycodeset.isValid();
		if(NEResult::hasError(result)) return result;
		if(NEResult::hasError(result = _priority.isValid())) return result;		

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEObject NE_DLL &NENode::clone() const
	{
		return *(new NENode(*this));
	}



	//	---------------------------------------------------------------------------------
	//	메모	:	_manager는 저장하지 않는다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NENode::serialize(NEBinaryFileSaver& saver) const 
	{
		SuperClass::serialize(saver);
		
		return saver << _groupcodeset << _priority << _modulecodeset << _keycodeset << _is_rootnode;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NENode::serialize(NEBinaryFileLoader& loader) 
	{
		SuperClass::serialize(loader);
		/*
			_is_rootnode와 _manager는 인스턴스를 생성하는 곳에서 추가하게 된다:
				NERootNodeCodeList/Set :: serialize에서 각각의 ModuleSet,NodeSet,KeySet을
				로드한다. 이시점에서는 _manager가 NE_NULL로 초기화되어있기때문에,
				이 이후에 NEEnlistableManager에서 NERootNodeCode에 _manager를 set하고,
				_onEnlisted를 호출한다.
		*/
		return loader >> _groupcodeset >> _priority >> _modulecodeset >> _keycodeset >> _is_rootnode;
	}



	type_result NE_DLL NENode::setCodes(const NECodeSet& new_codes)
	{
		//	pre:
		if(new_codes.getLength() <= 0) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
				return _setCodesDirectly(new_codes);


		//	main:
		return manager._onChangeCode(*this, new_codes);
	}
	


	//	---------------------------------------------------------------------------------
	//	메모	:	_manager도 release 해버리면, 대글링포인터가 되버리고,
	//				_manager->_onUnenroll 해버리면, 존재는 하지만 등록은 되지 않은게 되버린다.
	//				이건 ManagedNodeList 입장에서 보면 동기화되지 않은것이기 때문에
	//				Node::_release에서는 순수 노드정보만 release 한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NENode::_release()
	{
		/*
			scriptcode값은 변경하면 안된다.
		*/
		_groupcodeset.release();
		_priority.create(1);
		_priority.push(NECode(0));
		_modulecodeset.release();
		_keycodeset.release();
	}



	//	---------------------------------------------------------------------------------
	//	메모	:	ManagedNodeList::_enroll과 관련된 코드는 여기에 있으면 안된다.
	//				왜냐하면 Node::_id가 이미 변경되고 나서 여기에 올수 있기 때문이다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NENode& NENode::_assign(const NENode& source)
	{	
		if(this == &source) return *this;

		_modulecodeset = source._modulecodeset;
		_priority = source._priority;
		_groupcodeset = source._groupcodeset;
		_keycodeset = source._keycodeset;
		/*
			_manager, _is_rootnode는 복사/할당이 이루어져서는 안된다:
				왜냐하면 위의 값들은 "인스턴스가 어디에 있는가에 따라" 결정되는 
				값이기 때문이다.
		*/

		return *this;
	}

	bool NENode::isRootNode() const
	{
		return _is_rootnode;
	}

	type_result NENode::_onEnlisted()
	{
		/*
			여기로 들어오기 전에 외부로부터 이미 _manager가 갱신되었다.
		*/
		if( ! _manager)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}

		_setEnlisted(true);
		getManager()._enlist(*this);

		return _keycodeset._onEnlisted();
	}
	type_result NENode::_onUnlisted()
	{
		/*
			unlist 정책:
				node만 실제로 unlist되면 된다.
				enlist와 다르게 unlist는 소멸자가 "깊이탐색"의 역할까지도
				수행하고 있으므로 소멸자에 unlist() 함수를 두고,
				unlist에서는 "자신만" 소멸하는 방법으로 모든 노드가 안전하게
				unlist를 호출하고 메모리 반환할 수 있다.
		*/
		if(	! isManaged()	||
			! isEnlisted()	)
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		_setEnlisted(false);
		getManager()._unlist(*this);

		return RESULT_SUCCESS;
	}

	NENodeCodeSet& NENode::getOwner()
	{
		return *_owner;
	}

	const NENodeCodeSet& NENode::getOwner() const
	{
		return *_owner;
	}

	const NEKeyCodeSet& NENode::getKeySet() const
	{
		return _keycodeset;
	}

	NEKeyCodeSet& NENode::getKeySet()
	{
		return _keycodeset;
	}

	const NECodeSet& NENode::getCodes(const NECodeType& type) const
	{
		switch(type.getCodeType())
		{
		case NECodeType::GROUP:		return _groupcodeset;
		case NECodeType::PRIORITY:	return _priority;
		}

		return SuperClass::getCodes(type);
	}

	type_result NENode::_setCodesDirectly(const NECodeSet& new_one)
	{
		type_result result = RESULT_SUCCESS;
		if(new_one.getLength() <= 0) return RESULT_TYPE_WARNING | RESULT_WRONG_BOUNDARY;
		const NECode& code = new_one[0];


		//	main:
		switch(new_one.getCodeType().getCodeType())
		{
			//	SCRIPT는 SuperClass에서 다뤄야 하는 영역인데, 여기서 구현하는 이유:
			//		SuperClass::setCodes는 public 함수이고, 정책상 외부에서는 
			//		SCRIPT 코드를 수정하지 못하게 되어있다.
			//		그러나 이 함수(_setCodesDirectly)는 허용된 내부(예를들면, 
			//		friend 클래스)에서 직접적으로 코드를 변경할때 사용하는 함수다. 
			//		따라서 여기에 서술해둔다.
		case NECodeType::SCRIPT:
			_getScriptCodes().pop();
			_getScriptCodes().push(code);
			break;

		case NECodeType::GROUP:		
			_groupcodeset = new_one;
			return RESULT_SUCCESS;

		case NECodeType::PRIORITY:	
			_priority.pop();
			_priority.push(code);
			return RESULT_SUCCESS;
		};

		return SuperClass::setCodes(new_one);
	}

	type_code NENode::getPriorityCode() const
	{
		if(_priority.getLength() <= 0)
		{
			KERNAL_WARNING(" : ");
			return NE_DEFAULT;
		}

		return _priority[0].getCode();
	}

	const NECodeSet& NENode::getGroupCodes() const
	{
		return _groupcodeset;
	}

	type_result NENode::setGroupCodes(const NECodeSet& new_codes)
	{
		const NECodeSet* to_send = 0x00;
		const NECodeType& type = new_codes.getCodeType();
		if(type != NECodeType::GROUP)
		{
			NECodeSet new_one((NECodeType(NECodeType::GROUP)));
			new_one = new_codes;

			return setCodes(new_one);
		}

		return setCodes(new_codes);
	}

	type_result NENode::setPriorityCode(type_code new_code)
	{
		return setCodes(NECode(new_code, NECodeType::PRIORITY));
	}
}