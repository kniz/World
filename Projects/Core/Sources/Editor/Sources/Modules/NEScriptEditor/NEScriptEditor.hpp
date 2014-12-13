#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NEScriptEditor : public NEEnlistableManager
	{
		typedef NEEnlistableManager SuperClass;
		typedef NEScriptEditor ThisClass;
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/Banks/Banks.hpp"

	public:
		NEScriptEditor();
		NEScriptEditor(const NEScriptEditor& source);

	public:
		virtual ~NEScriptEditor();

	public:
		virtual NEType::Type getType() const;

	public:
		virtual NEScriptHeader& getScriptHeader() = 0;
		virtual const NEScriptHeader& getScriptHeader() const = 0;
		virtual NERootNodeCodeSet& getScriptNodes() = 0;
		virtual const NERootNodeCodeSet& getScriptNodes() const = 0; 
		virtual const Banks& getBanks() const = 0;
		virtual Banks& getBanks() = 0;
			
	public:
		virtual type_result synchronizeFrom(const NEScriptManager& source) = 0;
		virtual type_result synchronizeTo(NEScriptManager& scripter) const = 0;

	public:
		virtual type_result insertNameCode(type_code new_namecode) = 0;
		virtual type_result insertGroupCode(type_code new_groupcode) = 0;
		virtual type_result insertPriorityCode(type_code new_prioritycode) = 0;
		virtual type_result removeNameCode(type_code namecode) = 0;
		virtual type_result removeGroupCode(type_code groupcode) = 0;
		virtual type_result removePriorityCode(type_code prioritycode) = 0;
		
	protected:
		NEScriptHeader& _getScriptHeaderFrom(NEScriptManager& scripter) const;
		NERootNodeCodeSet& _getScriptNodesFrom(NEScriptManager& scripter) const;
		NEIndexedKeySet& _getKeySetFrom(NEScriptManager& scripter) const;
	};
}
