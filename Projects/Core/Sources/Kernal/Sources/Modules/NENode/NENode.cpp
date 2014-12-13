#include "NENode.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENode::NENode()
		: SuperClass(), _is_rootnode(false), _owner(NE_NULL)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENode::NENode(const NENode& source)
		: SuperClass(source), _is_rootnode(false), _owner(NE_NULL)
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
		if(_priority < 0) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA;

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



	type_result NE_DLL NENode::setNameCode(type_code new_namecode)
	{
		//	pre:
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
		{
			_namecode = new_namecode;
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		}

		//	main:
		return manager._onChangeNameCode(*this, new_namecode);
	}
	
	
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NECodeSet NE_DLL &NENode::getGroupCode() const
	{
		return _groupcodeset;
	}

	type_result NE_DLL NENode::setGroupCode(const NECodeSet& new_groupcodeset)
	{
		//	pre:
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
		{
			_groupcodeset = new_groupcodeset;
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		}

		//	main:
		return manager._onChangeGroupCode(*this, new_groupcodeset);
	}
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_code NE_DLL NENode::getPriority() const
	{
		return _priority;
	}
	
	type_result NE_DLL NENode::setPriority(type_code new_priority)
	{
		//	pre:
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
		{
			_priority = new_priority;
			return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		}
						
		//	main:
		return manager._onChangePriorityCode(*this, new_priority);
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
		_groupcodeset.release();
		_groupcodeset.setCodeType(NECodeType::GROUP);
		_priority = 0;
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
}