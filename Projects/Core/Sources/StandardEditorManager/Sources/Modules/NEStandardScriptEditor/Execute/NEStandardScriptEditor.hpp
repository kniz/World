#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NEStandardScriptEditor : public NEScriptEditor
	{	
	public:
		typedef NEScriptEditor SuperClass;
		typedef NEStandardScriptEditor ThisClass;

	public:
		friend class OnSynchronize;

	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/OnSynchronize/OnSynchronize.hpp"

	public:
		NEStandardScriptEditor();
		NEStandardScriptEditor(const NEStandardScriptEditor& source);

	public:
		virtual ~NEStandardScriptEditor();

	public:
		const NEStandardScriptEditor& operator=(const NEStandardScriptEditor& source);
		bool operator==(const NEStandardScriptEditor& source) const;
		bool operator!=(const NEStandardScriptEditor& source) const;

	public:
		virtual NERootNodeCodeSet& getScriptNodes();
		virtual const NERootNodeCodeSet& getScriptNodes() const;
		virtual NEScriptHeader& getScriptHeader();
		virtual const NEScriptHeader& getScriptHeader() const;
		virtual const Banks& getBanks() const;
		virtual Banks& getBanks();

	public:
		virtual type_result synchronizeFrom(const NEScriptManager& source);
		virtual type_result synchronizeTo(NEScriptManager& scripter) const;
		virtual type_result insertNameCode(type_code new_namecode);
		virtual type_result insertGroupCode(type_code new_groupcode);
		virtual type_result insertPriorityCode(type_code new_prioritycode);
		virtual type_result removeNameCode(type_code namecode);
		virtual type_result removeGroupCode(type_code groupcode);
		virtual type_result removePriorityCode(type_code prioritycode);

	public:
		virtual type_result initialize();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	private:
		virtual type_result execute();

	public:
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;
		virtual NEObject& clone() const;
		virtual void release();

	protected:
		virtual type_result _enlist(NENode& target, type_index index = NE_INDEX_ERROR);
		virtual type_result _unlist(NENode& target, type_index index = NE_INDEX_ERROR);

	protected:
		virtual type_result _onFetchModule();

	protected:
		type_result _initializeWithHeader();
		type_result _synchronizeCodesInKey(NEKey& key, NECodeType::CodeType codetype, type_code new_code, bool insertion_mode);
		type_result __synchronizeCodeSetInKey(NECodeSet& codeset, type_code new_code, bool insertion_mode);
		type_result _insertScriptCode(type_code new_scriptcode);
		type_result _removeScriptCode(type_code scriptcode);
		type_result _synchronize(OnSynchronize& handler, type_code max_code);
		type_code _searchInDeepForScriptCode(NENodeCodeSet& nodeset, NENode& target, type_code& start_scriptcode);
		type_code _searchInDeepForScriptCode(NEKeyCodeSet& node, NENode& target, type_code& start_scriptcode);		

	private:
		const NEStandardScriptEditor& _assign(const NEStandardScriptEditor& source);
		void _release();
		void _createBank(NETStringList& bank, type_index max_code_to_create);
		type_result _insertShortCutOrExpand(type_code code_to_expand);

	protected:	
		NERootNodeCodeSet _scriptset;
		NEScriptHeader _header;
		NEScriptEditor::Banks _banks;
	};
}