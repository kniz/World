//	---------------------------------------------------------------------------------
//	클래스명:	NEKeySelectorTemplate
//	설명	:	키 선택자. 
//				노드 선택자, 모듈 선택자를 각각 하나씩 가지고 있으며, 노드 선택자가 
//				가져온 노드를 타겟으로 삼아 모듈을 선택(Select)한다.
//				노드 선택자의 종류 * 모듈 선택자의 종류 만큼의 클래스가 존재하게 된다.
//	관계	:	기반클래스.	NEKey
//	특성	:	1	노드선택자를 멤버변수로 가지고 있다.
//				2	!주의!	부분 serialize를 지원하지 않는다!
//							자세한 사항은 NENodeSelector의 헤더를 참조.
//	알고리즘:	파생클래스의 알고리즘을 따른다.
//	사용방법:	getNode()로 노드를 선택한다.
//				getModule()로 노드를 선택한다.
//				이 때, getModule()을 실행하면 내부에서 getNode()를 실행하므로 둘을
//				섞어서 사용하면 안된다.
//	메모	:	
//	히스토리:	2011-08-04	이태훈	작성
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEModuleSelectorTemplate/NEModuleSelectorTemplate.hpp"
#include "../../Units/NEKeyBinder/NEKeyBinder.hpp"

namespace NE
{		
	template <typename NodeSelector, NEType::Type type> 
	class NEKeySelectorTemplate : public NodeSelector
	{
	public:
		typedef NEKeySelectorTemplate<NodeSelector, type> ThisClass;
		typedef NodeSelector SuperClass;
		typedef ThisClass Trait;

		//	생성자:
	public:
		NEKeySelectorTemplate(const NETString& keyname = "");
		NEKeySelectorTemplate(NEType::Type manager_type, const NETString& keyname = "");
		NEKeySelectorTemplate(const NEKeySelectorTemplate& source);

		//	소멸자:
	public:
		virtual ~NEKeySelectorTemplate();

		//	연산자 오버로딩:
	public:
		const NEKeySelectorTemplate& operator=(const NEKeySelectorTemplate& source);
		const NEKeySelectorTemplate& operator=(const NEKey& source);
		bool operator==(const NEKeySelectorTemplate& source) const;
		bool operator!=(const NEKeySelectorTemplate& source) const;

	public:
		Trait& getValue() { return *this; }	//	NEKey에 대한 클래스 템플릿 호환을 위해 만들어둔다.
		const NETString& getKeyName() const { return _keyname; }
		void setKeyName(const NETString& new_name);
		//	인터페이스:	
		//		상속:
		//			NEKeySelectorInterface:
	public:
		virtual type_result initializeReferingPoint()
		{
			SuperClass::initializeReferingPoint();		
			_key_index = NE_INDEX_ERROR;
			_is_key_returned_once = false;
			_binder.release();

			return RESULT_SUCCESS;
		}
		virtual type_result bind();

	public:
		virtual type_result assign(const NEKey& source);
		virtual type_result extend(const NEKey& source);
		virtual bool isEqualTo(const NEKey& source) const;

	public:
		//			NEObject:
		virtual void release();
		virtual NEObject& clone() const;
		virtual NEType::Type getType() const;
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		type_index getKeyIndex() const;
		NEKey& getKey();
		NEKey& peekKey();
		const NEKey& peekKey() const;
		NEKeyBinder& getBinder();
		const NEKeyBinder& getBinder() const;
		type_bool& isUsingAutoBinding();
		type_bool isUsingAutoBinding() const;
		
	protected:
		void _release();
		const NEKeySelectorTemplate<NodeSelector, type>& _assign(const NEKeySelectorTemplate<NodeSelector, type>& source);
		NEKey& _getKeyByBinder();

	private:
		NEKey& _findKeyByName(NEKeyCodeSet& keyset);

		//	멤버변수:
	private:
		type_index _key_index;
		NETString _keyname;
		NEKeyBinder	_binder;
		type_bool _use_auto_binding;
		type_bool _is_key_returned_once;
	};

	template <typename NodeSelector, NEType::Type type>
	NEKey& NE::NEKeySelectorTemplate<NodeSelector, type>::_findKeyByName(NEKeyCodeSet& keyset)
	{	
		//	pre:
		if(_key_index > NE_INDEX_ERROR) return keyset[_key_index];


		//	main:
		for(; _key_index < keyset.getLength() ;_key_index++)
			if(keyset[_key_index].getName() == _keyname)				
				return keyset[_key_index];

		NEKey* nullpoint = 0;
		return *nullpoint;
	}

}

#include "NEKeySelectorTemplate.inl"