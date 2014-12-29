#include "NEModuleSelectorTemplate.hpp"

namespace NE
{	
	template <typename NodeSelector, NEType::Type type>
	NEModule* NEModuleSelectorTemplate<NodeSelector, type>::_recent = NE_NULL;

	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEModuleSelectorTemplate<NodeSelector, type>::NEModuleSelectorTemplate(const NETString& keyname)
		: NodeSelector(keyname)
	{
		_release();
		_module_codes.getCodeType().setCodeType(NECodeType::ME);
	}


	template <typename NodeSelector, NEType::Type type>
	NE::NEModuleSelectorTemplate<NodeSelector, type>::NEModuleSelectorTemplate(NEType::Type manager_type, const NETString& keyname)
		: NENodeSelector(manager_type, keyname)
	{
		_release();
		_module_codes.getCodeType().setCodeType(NECodeType::ME);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEModuleSelectorTemplate<NodeSelector, type>::NEModuleSelectorTemplate(const NEModuleSelectorTemplate& source)
		: NodeSelector(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEModuleSelectorTemplate<NodeSelector, type>::~NEModuleSelectorTemplate()
	{

	}



	template <typename NodeSelector, NEType::Type type>
	const NEModuleSelectorTemplate<NodeSelector, type> &NEModuleSelectorTemplate<NodeSelector, type>::operator=(const NEModuleSelectorTemplate& source)
	{
		NodeSelector::operator=(source);

		return _assign(source);
	}


	template <typename NodeSelector, NEType::Type type>
	const NEModuleSelectorTemplate<NodeSelector, type> &NEModuleSelectorTemplate<NodeSelector, type>::operator=(const NEKey& source)
	{
		assign(source);

		return *this;
	}


	template <typename NodeSelector, NEType::Type type>
	bool NEModuleSelectorTemplate<NodeSelector, type>::operator==(const NEModuleSelectorTemplate& source) const
	{
		if(this == &source) return true;
		if(NodeSelector::operator!=(source)) return false;
		if(_module_depthlist != source._module_depthlist) return false;
		if(_module_codes != source._module_codes) return false;
		if(_is_returned_once != source._is_returned_once) return false;
		if(_binder != source._binder) return false;
		if(_use_auto_binding != source._use_auto_binding) return false;

		return true;
	}



	template <typename NodeSelector, NEType::Type type>
	bool NEModuleSelectorTemplate<NodeSelector, type>::operator!=(const NEModuleSelectorTemplate& source) const
	{
		return !(operator==(source));
	}


	template <typename NodeSelector, NEType::Type type>
	NEModule& NEModuleSelectorTemplate<NodeSelector, type>::getModule()
	{	
		//	배경:	모듈셀럭터의 검색모드는 노드셀렉터의 검색모드와 동일하다.
		//			따로 검색모드를 고려하지 않는다.

		//	pre:
		//		바인더로부터 가져올 수 있는가:
		if(_binder.isBinded())
			return _getModuleByBinder();	//	바인더로부터 가져오는 것을 1순위로 한다.
		//		널 레퍼런스:
		NEModule* null_pointer = NE_NULL;		
		const NECodeType& module_type = getModuleCodesType();
		if(module_type == NECodeType::UNDEFINED)
		{
			KERNAL_ERROR(" : ")
			return *null_pointer;
		}
		if(module_type == NECodeType::RECENT) 
		{
			if( ! _is_returned_once)
			{
				_is_returned_once = ! _is_returned_once;
				return *_recent;//return Kernal::getInstance().getNodeManager().getLocalStack().getRecentModule();
			}
			else 
			{
				_is_returned_once = ! _is_returned_once;
				return *null_pointer;
			}
		}
		if(module_type == NECodeType::ME)
		{
			if( ! _is_returned_once)
			{
				_is_returned_once = ! _is_returned_once;
				return Kernal::getInstance().getNodeManager().getLocalStack().getRecentModule();
			}
			else 
			{
				_is_returned_once = ! _is_returned_once;
				return *null_pointer;
			}
		}
		//		관련 멤버변수 검사:
		if(module_type != NECodeType::ALL)
			if (_module_codes.getLength() <= 0) 
				return *null_pointer;



		//	main:
		//		반환할 노드의 포인터 생성:
		NEModule& selected = _getNextByNoLimit();

		//		조건1-1:	찾은 노드의 포인터가 NULL 이라면
		if( ! &selected )
		{	//	예상치 못한 종료:	탐색을 끝마칠때는 항상 콜스택을 비워줘야만 한다. 모듈의 포인터를 담고있으므로,
			//						이 값을 보존하고 다음 프레임으로 넘어갈 때에는, 모듈의 주소가 변경될 수 있기 때문이다.
			//		콜스택(= 위치정보 ) 초기화:
			_module_depthlist.release();

			//		더미노드 반환:
			return *null_pointer; // 0,0에는 더미 모듈이 들어가있다
		}
		else
		{	//	정상적으로 노드 반환:
			_recent = &selected;
			
			if(_use_auto_binding && ! _binder.isBinded())
				bind();

			return selected;
		}		
	}	



	//	---------------------------------------------------------------------------------
	//	설명:		현재 놓여져 있는 가장 최근의 모듈을 반환한다.
	//				기본적으로, 최근에 getModule()로부터 나온 모듈이 존재하게 된다.
	//	히스토리:	2011-07-17	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEModule& NEModuleSelectorTemplate<NodeSelector, type>::peekModule() 
	{	
		//	pre:
		if(_binder.isBinded())
			return _binder.getBinded();
		//		널 레퍼런스:
		NEModule* null_pointer = NE_NULL;
		const NECodeType& module_type = getModuleCodesType();
		if(module_type == NECodeType::UNDEFINED)
		{
			KERNAL_ERROR(" : ")
				return *null_pointer;
		}
		//		타입 판단:
		if(module_type == NECodeType::ME) return Kernal::getInstance().getNodeManager().getLocalStack().getRecentModule();
		if(module_type == NECodeType::RECENT) return *_recent;
		//		멤버변수 검사:
		if(_module_depthlist.getLength() <= 0)
		{
			return *null_pointer;
		}



		//	main:
		//		타겟팅:
		NEModuleDepthUnit& recent = _module_depthlist.getElement(_module_depthlist.getLengthLastIndex());



		//	post:
		return _translateModuleFrom(peekNode(), recent);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-03	이태훈	작성
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	const NEModule& NEModuleSelectorTemplate<NodeSelector, type>::peekModule() const
	{	
		//	pre:
		if(_binder.isBinded())
			return _binder.getBinded();
		//		널 레퍼런스:
		NEModule* null_pointer = NE_NULL;
		const NECodeType& module_type = getModuleCodesType();
		if(module_type == NECodeType::UNDEFINED)
		{
			KERNAL_ERROR(" : ")
				return *null_pointer;
		}
		//		타입 판단:
		if(module_type == NECodeType::RECENT) return Kernal::getInstance().getNodeManager().getLocalStack().getRecentModule();
		//		멤버변수 검사:
		if(_module_depthlist.getLength() <= 0)
		{
			return *null_pointer;
		}



		//	main:
		//		타겟팅:
		const NEModuleDepthUnit& recent = _module_depthlist.getElement(_module_depthlist.getLengthLastIndex());



		//	post:
		return _translateModuleFrom(peekNode(), recent);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-18	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	template <typename NodeSelector, NEType::Type type>
	type_result NEModuleSelectorTemplate<NodeSelector, type>::initializeModuleSelectorReferingPoint()
	{
		_module_depthlist.release();
		_is_returned_once = false;
		_node_id = NE_INDEX_ERROR;

		return RESULT_SUCCESS;
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEObject& NEModuleSelectorTemplate<NodeSelector, type>::clone() const
	{
		return *(new NEModuleSelectorTemplate(*this));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	void NEModuleSelectorTemplate<NodeSelector, type>::release()
	{			
		NodeSelector::release();

		return _release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	type_result NEModuleSelectorTemplate<NodeSelector, type>::isValid() const
	{		
		type_result result = _module_codes.isValid();
		if(NEResult::hasError(result)) return result;
		result = _module_depthlist.isValid();
		if(NEResult::hasError(result)) return result;
		result = NodeSelector::isValid();
		if(NEResult::hasError(result)) return result;
		result = isValid();
		if(NEResult::hasError(result)) return result;
		const NECodeType& module_type = getModuleCodesType();
		if(module_type == NECodeType::UNDEFINED) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA;
		result = _binder.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEBinaryFileSaver &NEModuleSelectorTemplate<NodeSelector, type>::serialize(NEBinaryFileSaver& saver) const
	{
		NodeSelector::serialize(saver);

		return saver << _module_codes << _module_depthlist << _is_returned_once << _binder << _use_auto_binding << _node_id;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEBinaryFileLoader &NEModuleSelectorTemplate<NodeSelector, type>::serialize(NEBinaryFileLoader& loader)
	{
		NodeSelector::serialize(loader);

		return loader >> _module_codes >> _module_depthlist >> _is_returned_once >> _binder >> _use_auto_binding >> _node_id;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	NEKey끼리 캐스팅 없이 덧셈 할당을 실행한다. operator+=와 같다.
	//				셀렉터키는 해당되지 않는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	type_result NEModuleSelectorTemplate<NodeSelector, type>::assign(const NEKey& source)
	{
		if(this == &source) return RESULT_SUCCESS;
		if( ! isEqualTypeWith(source)) return RESULT_TYPE_ERROR;

		*this = static_cast<const NEModuleSelectorTemplate&>(source);

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	NEKey끼리 캐스팅 없이 덧셈 할당을 실행한다. operator+=와 같다.
	//				셀렉터키는 해당되지 않는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	type_result NEModuleSelectorTemplate<NodeSelector, type>::extend(const NEKey& source)
	{
		return RESULT_TYPE_ERROR;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	서로 같은 값을 가졌는지를 판단한다.
	//				먼저 타입을 확인하고, 같은 타입일 경우 operator==를 호출한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	bool NEModuleSelectorTemplate<NodeSelector, type>::isEqualTo(const NEKey& source) const
	{
		if( ! isEqualTypeWith(source)) return false;

		return operator==( static_cast<const NEModuleSelectorTemplate&>(source) );		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	const NEModuleSelectorTemplate<NodeSelector, type> &NEModuleSelectorTemplate<NodeSelector, type>::_assign(const NEModuleSelectorTemplate& source)
	{
		//	pre:
		if(this == &source) return *this;

		//	main:
		NodeSelector::operator=(source);
		_module_codes = source._module_codes;
		_module_depthlist = source._module_depthlist;
		_is_returned_once = source._is_returned_once;
		_binder = source._binder;
		_use_auto_binding = source._use_auto_binding;

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	NodeSelector에게 다음 노드를 가져오도록 한다.
	//	동작조건:
	//	메모	:	만약 더이상 조건에 맞는 노드가 없거나 검색제한(_countlimit)를 넘었다면
	//				더미노드가 반환된다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NENode* NEModuleSelectorTemplate<NodeSelector, type>::_getNextNode()
	{
		//	이 노드는 모든 모듈을 다 돌아본 것이 된다. (= 다음 노드를 가져오자 )
		NENode* to_return = &getNode();
		if( ! to_return ) return NE_NULL;
		if(to_return->getType() == NEType::UNDEFINED) return NE_NULL;

		_node_id = to_return->getId();
		//	탐색할 모듈셋 Queue(DepthList) 초기화:
		_initializeModuleDepthList(*to_return);

		return to_return;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	가져온 노드로부터 모듈을 하나씩 검색하면서 주어진 조건(멤버변수)에 
	//				적당한지 판단한다.
	//				모듈을 루프형식으로 할것인지, Boundary형식으로 할것인지는 전적으로
	//				노드셀렉터에게 달린 문제다.
	//	동작조건:	NodeSelector에 노드가 1개 이상 검색되어야 한다.
	//	메모	:	루프형식과 Boundary형식에 대해서는 NENodeSelectorByName.hpp를 참고하라.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEModule& NEModuleSelectorTemplate<NodeSelector, type>::_getNextByNoLimit()
	{	//	배경:
		//		일반검색 모드:	찾은 위치를 저장하고, 다음에 그 위치부터 검색을 실시한다
		//						인덱스0부터 검색해서, 끝에 도달하면 NULL을 반환한다.

		//		뒤늦은 포인터 방식:
		//			뒤늦은 포인터 방식은, 탐색을 위해서 _getNextByNoLimit()에 들어왔을때의
		//			최근 작업을 로드하는데, 이 최근작업(= 포인터)가 이전에 작업했던 위치를
		//			가리키고 있는 것을 말한다.
		//			앞선 포인터 방식은 "함수 진입시, 항상 포인터가 새로운 요소를 가리키고
		//			있음" 인데 반해서,
		//			뒤늦은 포인터 방식은 "함수 진입시, 일단 포인터를 다음으로 물리고 시작
		//			한다" 라고 하는 특징이 있다.
		//		왜 뒤늦은 포인터 방식을 사용하는가?:
		//			peekModule에서 앞선 포인터 방식이 불리하기 때문이다.
		//			앞선 포인터 방식에서 모듈셋을 전부 탐색한 경우에는 "pop"을 하게 되는데
		//			이 경우, peekModule이 불가능해진다. (이미 이전에 작업했던 모듈은 pop되었
		//			으므로)
		//		peekModule이란?:
		//			peek는 현재 상태에서 가장 최근(스택에서 최상단)의 것을 살펴보는 것을 말한다.
		//			뒤늦은 포인터에서 peek는 가장 최근에 getModule()한 모듈이 나오게 된다.

		//	pre:
		//		널 레퍼런스:		
		NEModule* null_pointer = NE_NULL;



		//	main:					
		//		모듈검색 실시:
		NENode* peeked = &peekNode();			
		while(1)
		{
			if(_module_depthlist.getLength() <= 0)
			{
				//	모듈이 더 없다면: 새로운 노드를 가져온다
				//		조건3:	 새로운 노드가 없다면				
				if(peeked = _getNextNode(), ! peeked)
					return *null_pointer;
			}
			else 
				if(peeked && peeked->getId() != _node_id)
					_initializeModuleDepthList(*peeked);

			NEModuleDepthUnit& unit = _module_depthlist[0];

			if(_isThereAnyModule(*peeked, unit))
			{
				NEModule& m = _translateModuleFrom(*peeked, unit);
				unit.module_index++;
				if(_isPassedFilter(m))
					return m;
			}
			else
				_module_depthlist.popFront();
		}		
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	찾아낸 모듈이 주어진 조건(멤버변수)에 맞는지 판단한다.
	//				조건은 OR 연산으로 실시한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	bool NEModuleSelectorTemplate<NodeSelector, type>::_isPassedFilter(NEModule& target) const
	{
		//	pre:
		if( ! &target ) return false;
		const NECodeType& module_type = getModuleCodesType();
		if(module_type == NECodeType::ALL) return true;

		//	main:
		for(type_index n=0; n < _module_codes.getLength() ;n++)
		{
			type_code code = _module_codes.getElement(n).getCode();
			
			switch(module_type.getCodeType())
			{			
			case NECodeType::NAME:
			case NECodeType::SCRIPT:
				if(target.getCodes(module_type)[0].getCode() == code) // 가운데 ==를 !=로 바꾸면 AND연산이 된다. 
					return true;
				break;

			case NECodeType::RECENT:
			default:
				KERNAL_ERROR(" : ")
					return false;
			}			
		}

		return false;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEType::Type NEModuleSelectorTemplate<NodeSelector, type>::getType() const
	{								
		return type;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-03	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	void NEModuleSelectorTemplate<NodeSelector, type>::setModuleCodes(const NECodeSet& new_module_codeset)
	{
		_module_codes = new_module_codeset;
		
		initializeReferingPoint();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-03	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	const NECodeSet& NEModuleSelectorTemplate<NodeSelector, type>::getModuleCodes() const
	{
		return _module_codes;
	}



	template <typename NodeSelector, NEType::Type type>
	void NEModuleSelectorTemplate<NodeSelector, type>::_release()
	{
		_module_codes.release();
		_module_depthlist.release();
		_is_returned_once = false;
		_binder.release();
		_use_auto_binding = false;
		_node_id = NE_INDEX_ERROR;
	}



	template <typename NodeSelector, NEType::Type type>
	type_result NE::NEModuleSelectorTemplate<NodeSelector, type>::initializeReferingPoint()
	{
		type_result result = initializeNodeSelectorReferingPoint();

		return result |= initializeModuleSelectorReferingPoint();
	}



	template <typename NodeSelector, NEType::Type type>
	type_result NEModuleSelectorTemplate<NodeSelector, type>::bind()
	{
		//	pre:
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}	
		const NECodeType& module_type = getModuleCodesType();
		if(module_type == NECodeType::UNDEFINED)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		if(module_type == NECodeType::ME)
		{
			if(manager.isSubClassOf(NEType::NENODE_MANAGER))
			{
				NENodeManager& noder = static_cast<NENodeManager&>(manager);
				NENodeManager::LocalStack& localstack = noder.getLocalStack();
				_binder._real_index = localstack.getRecentModuleRealIndex();
				_binder._comparing_id = localstack.getRecentModule().getId();
				_binder._manager_type = getManagerType();
				return RESULT_SUCCESS;
			}
			
			KERNAL_ERROR(" : RECENT 타입을 바인딩할때는 manager가 노드 매니져여야만 가능합니다.");
			return RESULT_TYPE_ERROR;
		}
		if(module_type == NECodeType::RECENT)
		{
			KERNAL_ERROR("현재 버전으로는 RECENT로 Binder를 생성할 수 없습니다");
			return RESULT_TYPE_ERROR;
		}
		//		멤버변수 검사:
		if(_module_depthlist.getLength() <= 0)
			return RESULT_TYPE_ERROR;



		//	main:
		//		Real Index 획득:
		//		타겟팅:
		NEModuleDepthUnit& recent = _module_depthlist[0];
		NEModuleCodeSet& moduleset = _translateModuleCodeSet(peekNode(), recent);
		if( ! &moduleset)
		{
			KERNAL_ERROR(" : DepthList가 손상되었습니다.");
			return RESULT_TYPE_ERROR;
		}
		//		Binder 정의:
		//			Real Index:	module_index는 현재가 아니라 다음에 "가져올" 인덱스 따라서 -1을 해줘야 한다.
		type_index real_index = moduleset.getInnerElement(recent.module_index-1);
		_binder._real_index = real_index;
		//			Id:
		NEModule& module = manager._getModuleSet().getElement(real_index);
		if( ! &module)
		{
			_binder.release();
			return RESULT_TYPE_ERROR;
		}
		_binder._comparing_id = module.getId();



		//	post:
		//		Binder 초기화:
		_binder._manager_type = getManagerType();
		return RESULT_SUCCESS;
	}

	template <typename NodeSelector, NEType::Type type>
	const NEModuleBinder& NEModuleSelectorTemplate<NodeSelector, type>::getBinder() const
	{
		return _binder;
	}

	template <typename NodeSelector, NEType::Type type>
	NEModuleBinder& NEModuleSelectorTemplate<NodeSelector, type>::getBinder()
	{
		return _binder;
	}

	template <typename NodeSelector, NEType::Type type>
	NEModule& NEModuleSelectorTemplate<NodeSelector, type>::_getModuleByBinder()
	{
		NEModule* nullpoint = 0;
		NEModule& to_return = _is_returned_once ? *nullpoint : _binder.getBinded();
		_is_returned_once = !_is_returned_once;
		return to_return;
	}

	template <typename NodeSelector, NEType::Type type>
	type_bool& NEModuleSelectorTemplate<NodeSelector, type>::isUsingAutoBinding()
	{
		return _use_auto_binding;
	}
	template <typename NodeSelector, NEType::Type type>
	type_bool NEModuleSelectorTemplate<NodeSelector, type>::isUsingAutoBinding() const
	{
		return _use_auto_binding;
	}											 

	template <typename NodeSelector, NEType::Type type>
	type_result NEModuleSelectorTemplate<NodeSelector, type>::_initializeModuleDepthList(const NENode& new_one_to_be_searched)
	{
		//	pre:
		_module_depthlist.release();


		//	main:		
		//		내가 소유한 모듈셋을 먼저 담는다:
		_module_depthlist.push(NEModuleDepthUnit(NEModuleDepthUnit::FROM_MODULE_CODE_SET_OF_NODE));
		//		키셋에 모듈셋키가 있다면, 뒤에 담는다:
		const NEKeyCodeSet& ks = new_one_to_be_searched.getKeySet();
		for(int n=0; n < ks.getLength() ;n++)
		{
			const NEKey& key = ks[n];
			if(key.isSubClassOf(NEType::NEMODULE_CODESET_KEY))
				_module_depthlist.push(NEModuleDepthUnit(n));
		}

		return RESULT_SUCCESS;
	}


	template <typename NodeSelector, NEType::Type type>
	NEModule& NEModuleSelectorTemplate<NodeSelector, type>::_translateModuleFrom(NENode& node, const NEModuleDepthUnit& unit)
	{
		NEModuleCodeSet& ms = _translateModuleCodeSet(node, unit);
		NEModule* nullpoint = 0;
		if( ! &ms) return *nullpoint;

		return ms[unit.module_index];
	}

	template <typename NodeSelector, NEType::Type type>
	const NEModule& NEModuleSelectorTemplate<NodeSelector, type>::_translateModuleFrom(const NENode& node, const NEModuleDepthUnit& unit) const
	{
		const NEModuleCodeSet& ms = _translateModuleCodeSet(node, unit);
		const NEModule* nullpoint = 0;
		if( ! &ms) return *nullpoint;

		return ms[unit.module_index];
	}

	template <typename NodeSelector, NEType::Type type>
	NEModuleCodeSet& NEModuleSelectorTemplate<NodeSelector, type>::_translateModuleCodeSet(NENode& node, const NEModuleDepthUnit& unit)
	{
		//	pre:
		NEModuleCodeSet* nullpoint = 0;
		if( ! &node) return *nullpoint;
		if(unit.key_index_to_be_moduleset == NEModuleDepthUnit::FROM_MODULE_CODE_SET_OF_NODE)
			return node.getModuleSet();
		NEKeyCodeSet& ks = node.getKeySet();			
		if(	unit.key_index_to_be_moduleset > ks.getLengthLastIndex()						||
			! ks[unit.key_index_to_be_moduleset].isSubClassOf(NEType::NEMODULE_CODESET_KEY)	) 
			return *nullpoint;


		//	post:
		return static_cast<NEModuleCodeSetKey&>(ks[unit.key_index_to_be_moduleset]).getValue();			
	}

	template <typename NodeSelector, NEType::Type type>
	const NEModuleCodeSet& NE::NEModuleSelectorTemplate<NodeSelector, type>::_translateModuleCodeSet(const NENode& node, const NEModuleDepthUnit& unit) const
	{
		//	pre:
		const NEModuleCodeSet* nullpoint = 0;
		if( ! &node) return *nullpoint;
		if(unit.key_index_to_be_moduleset == NEModuleDepthUnit::FROM_MODULE_CODE_SET_OF_NODE)
			return node.getModuleSet();
		const NEKeyCodeSet& ks = node.getKeySet();
		if(	unit.key_index_to_be_moduleset > ks.getLengthLastIndex()						||
			! ks[unit.key_index_to_be_moduleset].isSubClassOf(NEType::NEMODULE_CODESET_KEY)	) 
			return *nullpoint;


		//	post:
		return static_cast<const NEModuleCodeSetKey&>(ks[unit.key_index_to_be_moduleset]).getValue();			
	}

	template <typename NodeSelector, NEType::Type type>
	bool NE::NEModuleSelectorTemplate<NodeSelector, type>::_isThereAnyModule( const NENode& node, const NEModuleDepthUnit& unit ) const
	{
		const NEModuleCodeSet& ms = _translateModuleCodeSet(node, unit);
		if( ! &ms) return false;

		return unit.module_index <= ms.getLengthLastIndex();
	}
}