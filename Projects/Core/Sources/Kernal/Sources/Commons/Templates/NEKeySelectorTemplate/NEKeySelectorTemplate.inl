namespace NE
{	
	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEKeySelectorTemplate<NodeSelector, type>::NEKeySelectorTemplate(const NETString& keyname)
		: NodeSelector(keyname)
	{
		_release();
	}



	template <typename NodeSelector, NEType::Type type>
	NEKeySelectorTemplate<NodeSelector, type>::NEKeySelectorTemplate(NEType::Type manager_type, const NETString& keyname)
		: NodeSelector(manager_type, keyname)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEKeySelectorTemplate<NodeSelector, type>::NEKeySelectorTemplate(const NEKeySelectorTemplate& source)
		: NodeSelector(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	NEKeySelectorTemplate<NodeSelector, type>::~NEKeySelectorTemplate()
	{

	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-12	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	const NEKeySelectorTemplate<NodeSelector, type> &NEKeySelectorTemplate<NodeSelector, type>::operator=(const NEKeySelectorTemplate& source)
	{	
		if(this == &source) return *this;

		NodeSelector::operator=(source);
		
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-12	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	bool NEKeySelectorTemplate<NodeSelector, type>::operator==(const NEKeySelectorTemplate& source) const
	{	
		if(this == &source) return true;
		if(NodeSelector::operator!=(source)) return false;
		if(_key_index != source._key_index) return false;
		if(_use_auto_binding != source._use_auto_binding) return false;
		if(_is_key_returned_once != source._is_key_returned_once) return false;
		if(_keyname != source._keyname) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-12	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	bool NEKeySelectorTemplate<NodeSelector, type>::operator!=(const NEKeySelectorTemplate& source) const
	{	
		return !(operator==(source));
	}



	template <typename NodeSelector, NEType::Type type>
	type_index NEKeySelectorTemplate<NodeSelector, type>::getKeyIndex() const
	{
		return _key_index;
	}


	template <typename NodeSelector, NEType::Type type>
	void NEKeySelectorTemplate<NodeSelector, type>::setKeyName(const NETString& new_name)
	{
		initializeReferingPoint();
		_keyname = new_name;
	}


	template <typename NodeSelector, NEType::Type type>
	NEKey& NEKeySelectorTemplate<NodeSelector, type>::getKey()
	{
		//	pre:
		if(_binder.isBinded())
			return _getKeyByBinder();
		//		널 레퍼런스:
		NEKey* null_pointer = NE_NULL;
		//		바인딩 체크:
		if(_binder.isBinded())
			if(_is_key_returned_once++)
				return *null_pointer;
			else	
				return _binder.getBinded();


		//	main:		
		//		이전에 하던 노드 복구:
		NENode* peeked = 0;
		_key_index != NE_INDEX_ERROR ? peeked = &peekNode() : peeked = &getNode();	//	전에 하던 위치가 있다면 복구한다
		//		탐색 시작:
		while(&peeked)
		{
			NEKeyCodeSet& ks = peeked->getKeySet();
			for(_key_index++; _key_index < ks.getLength() ;_key_index++)
				if(ks[_key_index].getName() == _keyname)
				{
					_is_key_returned_once = true;
					if(_use_auto_binding && ! _binder.isBinded())
						bind();

					return ks[_key_index];
				}
			
			peeked = &getNode();
			_key_index = NE_INDEX_ERROR;
		}
		
			
		//	post:
		//		if you found:
		_is_key_returned_once = false;
		return *null_pointer;		
	}



	template <typename NodeSelector, NEType::Type type>
	NEKey& NEKeySelectorTemplate<NodeSelector, type>::peekKey()
	{
		//	pre:
		if(_binder.isBinded())
			return _binder.getBinded();
		//		널 레퍼런스:
		NEKey* null_pointer = NE_NULL;
		//		타겟팅:
		NENode& node = peekNode();
		if( ! &node) return *null_pointer;
		if(_key_index > node.getKeySet().getLengthLastIndex()) return *null_pointer;

		return node.getKeySet()[_key_index];
	}



	template <typename NodeSelector, NEType::Type type>
	const NEKey& NEKeySelectorTemplate<NodeSelector, type>::peekKey() const
	{
		//	pre:
		if(_binder.isBinded())
			return _binder.getBinded();
		//		널 레퍼런스:
		NEKey* null_pointer = NE_NULL;
		//		타겟팅:
		const NENode& node = peekNode();
		if( ! &node) return *null_pointer;
		if(_key_index > node.getKeySet().getLengthLastIndex()) return *null_pointer;

		return node.getKeySet()[_key_index];
	}



	template <typename NodeSelector, NEType::Type type>
	type_result NEKeySelectorTemplate<NodeSelector, type>::assign(const NEKey& source)
	{
		if(this == &source) return RESULT_SUCCESS;
		if( ! isEqualTypeWith(source)) return RESULT_TYPE_ERROR;

		*this = static_cast<const NEKeySelectorTemplate&>(source);

		return RESULT_SUCCESS;
	}



	template <typename NodeSelector, NEType::Type type>
	type_result NEKeySelectorTemplate<NodeSelector, type>::extend(const NEKey& source)
	{
		return RESULT_TYPE_ERROR;
	}


	template <typename NodeSelector, NEType::Type type>
	bool NEKeySelectorTemplate<NodeSelector, type>::isEqualTo(const NEKey& source) const
	{
		if( ! isEqualTypeWith(source)) return false;

		return operator==( static_cast<const NEKeySelectorTemplate&>(source) );		
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	void NEKeySelectorTemplate<NodeSelector, type>::release()
	{
		NodeSelector::release();

		_release();
	}



	template <typename NodeSelector, NEType::Type type>
	NEType::Type NEKeySelectorTemplate<NodeSelector, type>::getType() const
	{
		return type;
	}



	template <typename NodeSelector, NEType::Type type>
	NEObject& NEKeySelectorTemplate<NodeSelector, type>::clone() const
	{
		return *(new NEKeySelectorTemplate(*this));
	}



	template <typename NodeSelector, NEType::Type type>
	NEBinaryFileSaver& NEKeySelectorTemplate<NodeSelector, type>::serialize(NEBinaryFileSaver& saver) const
	{
		NodeSelector::serialize(saver);

		return saver << _key_index << _binder << _use_auto_binding << _is_key_returned_once << _keyname;
	}



	template <typename NodeSelector, NEType::Type type>
	NEBinaryFileLoader& NEKeySelectorTemplate<NodeSelector, type>::serialize(NEBinaryFileLoader& loader)
	{
		NodeSelector::serialize(loader);

		return loader >> _key_index >> _binder >> _use_auto_binding >> _is_key_returned_once >> _keyname;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector, NEType::Type type>
	type_result NEKeySelectorTemplate<NodeSelector, type>::isValid() const
	{
		//	pre:
		//		상위 클래스 메소드:
		type_result result = NodeSelector::isValid();
		if(NEResult::hasError(result) == true) return result;
		//		멤버변수의 최소 검사:
		if(_keyname.getLength() <= 0) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA | RESULT_WRONG_BOUNDARY;
		

		//	post:
		return RESULT_SUCCESS;
	}
	
	template <typename NodeSelector, NEType::Type type>
	const NEKeySelectorTemplate<NodeSelector, type>& NEKeySelectorTemplate<NodeSelector, type>::_assign(const NEKeySelectorTemplate<NodeSelector, type>& source)
	{
		if(this == &source) *this;

		NodeSelector::operator=(source);
		_keyname = source._keyname;
		_binder = source._binder;
		_use_auto_binding = source._use_auto_binding;
		_is_key_returned_once = source._is_key_returned_once;

		return *this;
	}
	
	template <typename NodeSelector, NEType::Type type>
	void NEKeySelectorTemplate<NodeSelector, type>::_release()
	{		
		_key_index = NE_DEFAULT;
	}


	template <typename NodeSelector, NEType::Type type>
	type_result NEKeySelectorTemplate<NodeSelector, type>::bind()
	{
		//	pre:
		//		타겟팅:
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}	
		NENode& node = peekNode();
		if( ! &node ) return RESULT_TYPE_ERROR;


		//	main:
		NEKeyCodeSet& ks = node.getKeySet();
		if(_key_index > ks.getLengthLastIndex())
			return RESULT_TYPE_ERROR;
		//		Binder 정의:
		//			Real Index:		
		_binder._real_index = ks.getInnerElement(_key_index);
		//			Id:
		NEKey& key = manager._getKeySet().getElement(_binder._real_index);
		if( ! &key)
		{
			_binder.release();
			return RESULT_TYPE_ERROR;
		}
		_binder._comparing_id = key.getId();


		//	post:
		_binder._manager_type = getManagerType();
		return RESULT_SUCCESS;
	}


	template <typename NodeSelector, NEType::Type type>
	NEKeyBinder& NEKeySelectorTemplate<NodeSelector, type>::getBinder()
	{
		return _binder;
	}

	template <typename NodeSelector, NEType::Type type>
	const NEKeyBinder& NEKeySelectorTemplate<NodeSelector, type>::getBinder() const
	{
		return _binder;
	}

	template <typename NodeSelector, NEType::Type type>
	type_bool NEKeySelectorTemplate<NodeSelector, type>::isUsingAutoBinding() const
	{
		return _use_auto_binding;
	}

	template <typename NodeSelector, NEType::Type type>
	type_bool& NEKeySelectorTemplate<NodeSelector, type>::isUsingAutoBinding()
	{
		return _use_auto_binding;
	}

	template <typename NodeSelector, NEType::Type type>
	NEKey& NEKeySelectorTemplate<NodeSelector, type>::_getKeyByBinder()
	{
		NEKey* nullpoint = 0;		
		NEKey& to_return = _is_key_returned_once ? *nullpoint : _binder.getBinded();
		_is_key_returned_once = !_is_key_returned_once;
		return to_return;
	}
}