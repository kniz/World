//	---------------------------------------------------------------------------------
//	클래스명:	NEModuleSelectorTemplate
//	설명	:	모듈 선택자. 
//				노드 선택자를 하나 가지고 있으며, 노드 선택자가 가져온 노드를 타겟으로
//				삼아 모듈을 선택(Select)한다.
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
//	히스토리:	2011-06-05	이태훈	개발 완료.
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../../Modules/NECodeSet/NECodeSet.hpp"
#include "../../../Modules/NEModuleDepthList/NEModuleDepthList.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"
#include "../../../Modules/NEModuleBinder/NEModuleBinder.hpp"

namespace NE
{		
	template <typename NodeSelector, NEType::Type type>
	class NEModuleSelectorTemplate : public NodeSelector
	{
	public:
		typedef NEModuleSelectorTemplate<NodeSelector, type> ThisClass;
		typedef NodeSelector SuperClass;
		typedef ThisClass Trait;

		//	생성자:
	public:
		NEModuleSelectorTemplate(const NETString& keyname = "");
		NEModuleSelectorTemplate(NEType::Type manager_type, const NETString& keyname = "");
		NEModuleSelectorTemplate(const NEModuleSelectorTemplate& source);

		//	소멸자:
	public:
		virtual ~NEModuleSelectorTemplate();

	public:
		const ThisClass& operator=(const ThisClass& source);
		const ThisClass& operator=(const NEKey& source);
		bool operator==(const NEModuleSelectorTemplate& source) const;
		bool operator!=(const NEModuleSelectorTemplate& source) const;

	public:
		Trait& getValue() { return *this; }	//	NEKey에 대한 클래스 템플릿 호환을 위해 만들어둔다.
		const Trait& getValue() const { return *this; }
		void setModuleCodes(const NECodeSet& new_module_codeset);		
		const NECodeSet& getModuleCodes() const;
		const NECodeType& getModuleCodesType() const;
		type_result setModuleCodesType(const NECodeType& source);

		//	인터페이스:
		//		상속:
		//			NEModuleSelectorInterface:
	public:
		virtual type_result bind();

	public:
		virtual type_result initializeReferingPoint();

	public:
		virtual type_result assign(const NEKey& source);
		virtual type_result extend(const NEKey& source);
		virtual bool isEqualTo(const NEKey& source) const;

	public:
		virtual NEObject& clone() const;
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEType::Type getType() const;

	public:
		NEModule& getModule();
		NEModule& peekModule();
		const NEModule& peekModule() const;
		type_result initializeModuleSelectorReferingPoint();
		NEModuleBinder& getBinder();
		const NEModuleBinder& getBinder() const;
		type_bool& isUsingAutoBinding();
		type_bool isUsingAutoBinding() const;

	private:
		const NEModuleSelectorTemplate& _assign(const ThisClass& source);
		void _release();
		NENode* _getNextNode();
		NEModule& _getNextByNoLimit();
		NEModule& _getModuleByBinder();
		bool _isPassedFilter(NEModule& target) const;		
		type_result _initializeModuleDepthList(const NENode& new_one_to_be_searched);
		NEModuleCodeSet& _translateModuleCodeSet(NENode& node, const NEModuleDepthUnit& unit);
		const NEModuleCodeSet& _translateModuleCodeSet(const NENode& node, const NEModuleDepthUnit& unit) const;
		bool _isThereAnyModule(const NENode& node, const NEModuleDepthUnit& unit) const;
		NEModule& _translateModuleFrom(NENode& node, const NEModuleDepthUnit& unit);
		const NEModule& _translateModuleFrom(const NENode& node, const NEModuleDepthUnit& unit) const;

	protected:
		NECodeSet _module_codes;
		NEModuleDepthList _module_depthlist;
		type_bool _is_returned_once;
		type_bool _use_auto_binding;
		NEModuleBinder _binder;
		type_id _node_id;

	private:
		static NEModule* _recent;
	};

	template <typename NodeSelector, NEType::Type type>
	type_result NE::NEModuleSelectorTemplate<NodeSelector, type>::setModuleCodesType(const NECodeType& source)
	{
		type_result result = _module_codes.getCodeType().setCodeType(source.getCodeType());

		return result |= initializeReferingPoint();		
	}

	template <typename NodeSelector, NEType::Type type>
	const NECodeType& NE::NEModuleSelectorTemplate<NodeSelector, type>::getModuleCodesType() const
	{
		return _module_codes.getCodeType();
	}
}

#include "NEModuleSelectorTemplate.inl"