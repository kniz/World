#pragma once

#include "../NEPanelSet/NEPanelSet.hpp"
#include "../NEPanelList/NEPanelList.hpp"

namespace NE
{
	class NE_DLL NEPanelManager : public NEModule
	{
		//	내부클래스:
	public:
#include "innerclass/DLLHeader/DLLHeader.hpp"
#include "innerclass/DLLHeaderList/DLLHeaderList.hpp"
	
		//	생성자:
	public:
		NEPanelManager();
		NEPanelManager(const NEPanelManager& source);

		//	소멸자:
	public:
		virtual ~NEPanelManager();

		//	접근자:
	public:
		virtual NEPanel& getPanel(const NEExportable::Identifier& identifer)= 0;
		virtual const NEPanel& getPanel(const NEExportable::Identifier& identifer) const = 0;
		virtual const DLLHeaderList& getPanelHeaderList() const = 0;
		virtual NEPanelSet& getPanelSet() = 0;
		virtual const NEPanelSet& getPanelSet() const = 0;

		//	인터페이스:
		//		상속:
		//			NEOject:
	public:
		virtual NEType::Type getType() const;
		
	protected:
		NEString& _getPanelEntryPointStringOfDLL() const; // NETString, NEWString이 아님에 주의하라
	};	
}
