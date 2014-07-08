#include "NEScriptEditor.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"

namespace NE
{
	NE_DLL NEScriptEditor::NEScriptEditor()
		: SuperClass()
	{

	}
	NE_DLL NEScriptEditor::NEScriptEditor(const ThisClass& source)
		: SuperClass(source)
	{
		
	}
	NE_DLL NEScriptEditor::~NEScriptEditor()
	{

	}

	NEType::Type NE_DLL NEScriptEditor::getType() const
	{
		return NEType::NESCRIPT_EDITOR;
	}
	
	NEScriptManager::ScriptHeader& NEScriptEditor::_getScriptHeaderFrom(NEScriptManager& scripter) const
	{	
		if( ! &scripter)
		{
			ALERT_ERROR(" : ")
			NEScriptManager::ScriptHeader* null_pointer = NE_NULL;
			
			return *null_pointer;
		}
				
		return scripter._getScriptHeader();
	}

	NERootNodeCodeSet& NEScriptEditor::_getScriptNodesFrom(NEScriptManager& scripter) const
	{	
		if( ! &scripter)
		{
			ALERT_ERROR(" : ")
			NERootNodeCodeSet* null_pointer = NE_NULL;
			
			return *null_pointer;
		}
		
		return scripter._getScriptNodes();
	}

	NEIndexedKeySet& NEScriptEditor::_getKeySetFrom(NEScriptManager& scripter) const
	{
		if( ! &scripter)
		{
			ALERT_ERROR(" : ")
			NEIndexedKeySet* null_pointer = NE_NULL;

			return *null_pointer;
		}

		return scripter._getKeySet();
	}
}