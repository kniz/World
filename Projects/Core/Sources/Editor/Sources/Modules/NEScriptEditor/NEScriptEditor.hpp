#pragma once

#include "../../Includes/Includes.hpp"
#include "../NEBank/NEBank.hpp"

namespace NE
{
	template 
	class NE_DLL NETVector<NEBank*, true>;
	class NE_DLL NEScriptEditor : public NEEnlistableManager
	{
	public:
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
		virtual type_result insertCode(const NECode& new_code) = 0;
		virtual type_result removeCode(const NECode& code_to_remove) = 0;

	protected:
		NEScriptHeader& _getScriptHeaderFrom(NEScriptManager& scripter) const;
		NERootNodeCodeSet& _getScriptNodesFrom(NEScriptManager& scripter) const;
		NEKeyArray& _getKeySetFrom(NEScriptManager& scripter) const;
	};
}