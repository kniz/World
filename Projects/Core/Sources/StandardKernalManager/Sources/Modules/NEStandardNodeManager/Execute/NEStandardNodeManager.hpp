//	---------------------------------------------------------------------------------
//	클래스명:	NEStandardNodeManager
//	설명	:	노드를 관리하는 관리자 클래스.
//				노드는 물론이고, 숏컷(노드의 코드별로 리스트에 주소를 넣어서, 
//				셀렉터가 빠르게 참조 할 수 있도록 하는 기능)도 관리한다.
//				숏컷에 대해서는 NEShortCut.hpp를 참고하라.
//	관계	:	기반클래스.	NENodeManager
//	특성	:	노드엔진에 필수적으로 포함되는 모듈의 일종.
//				모듈의 독립성을 제공해야 하는 모듈매니져와는 달리, 인덱스로 노드에 접근이
//				가능하다.
//	알고리즘:	
//	사용방법:	
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//				2011-07-17	이태훈	추가
//					:	1	숏컷셋을 초기화 하고 "탐색시, 조회 순서 측정 방식"으로 숏컷의 정보를
//							조회 순서(카운트) <---> 노드의 주소 로 변환하는 serialize 코드를
//							추가했다.
//						2	순차로 노드셋과 모듈셋, 노드리스트를 탐색하는 코드를 추가했다.
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NEStandardNodeManager : public NENodeManager
	{	
		typedef NENodeManager SuperClass;
		typedef NEStandardNodeManager ThisClass;

	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/StandardLocalStack/StandardLocalStack.hpp"

		//	생성자:
	public:
		NEStandardNodeManager();
		NEStandardNodeManager(const ThisClass& source);

		//	소멸자:
	public:
		virtual ~NEStandardNodeManager();

	public:
		const NEStandardNodeManager& operator=(const ThisClass& source);
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;
			
		//	인터페이스:
		//		상속:	
		//			NENodeManager:
	public:
		virtual LocalStack& getLocalStack();
		virtual const LocalStack& getLocalStack() const;
		virtual NERootNodeCodeSet& getRootNodes();
		virtual const NERootNodeCodeSet& getRootNodes() const;		
		//			NEExportable:
	public:
		virtual type_result initialize();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;		
		//			NEUnit:
	private:
		virtual type_result execute();		
		//			NEObject:
	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEObject& clone() const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;

	protected:
		virtual type_result _onFetchModule();

	private:
		void _release();
		const NEStandardNodeManager& _assign(const ThisClass& source);
		type_result _loadScriptDataCorrspondingToNodeData(NETString& path, NEScriptManager::ScriptHeader& header) const;
		
	protected:
		StandardLocalStack _local_stack;
		NERootNodeCodeSet _nodecodeset;
	};
}
