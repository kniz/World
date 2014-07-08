#include "../../NEScriptManager.hpp"
#include "../../../Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEScriptManager::ScriptHeader::ScriptHeader()
		: SuperClass()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEScriptManager::ScriptHeader::ScriptHeader(const ThisClass& source)
		: SuperClass(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEScriptManager::ScriptHeader::~ScriptHeader()
	{

	}



	const NEScriptManager::ScriptHeader NE_DLL &NEScriptManager::ScriptHeader::operator=(const ScriptHeader& source)
	{
		SuperClass::operator=(source);

		return _assign(source);
	}

	bool NE_DLL NEScriptManager::ScriptHeader::operator==(const ScriptHeader& source) const
	{
		if(this == &source) return true;
		if(SuperClass::operator!=(source)) return false;
		if(_max_scriptcode_index != source._max_scriptcode_index) return false;
		if(_max_namecode_index != source._max_namecode_index) return false;
		if(_max_groupcode_index != source._max_groupcode_index) return false;
		if(_max_prioritycode_index != source._max_prioritycode_index) return false;
		if(_max_node_length != source._max_node_length) return false;
		if(_max_module_length != source._max_module_length) return false;
		if(_max_key_length != source._max_key_length) return false;

		return true;
	}

	bool NE_DLL NEScriptManager::ScriptHeader::operator!=(const ScriptHeader& source) const
	{
		return !(operator==(source));
	}

	const NEScriptManager::ScriptHeader& NEScriptManager::ScriptHeader::_assign(const ScriptHeader& source)
	{
		if(this == &source) return *this;

		_max_scriptcode_index = source._max_scriptcode_index;
		_max_namecode_index = source._max_namecode_index;
		_max_groupcode_index = source._max_groupcode_index;
		_max_prioritycode_index = source._max_prioritycode_index;
		_max_node_length = source._max_node_length;
		_max_module_length = source._max_module_length;
		_max_key_length = source._max_key_length;

		return *this;
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::setMaxNameCodeIndex(type_index max_name_code_index)
	{
		if(max_name_code_index < NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_namecode_index = max_name_code_index;

		return RESULT_SUCCESS;
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::getMaxNameCodeIndex() const
	{
		return _max_namecode_index;
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::getMaxScriptCodeIndex() const
	{
		return _max_scriptcode_index;
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::setMaxScriptCodeIndex(type_index max_script_code_index)
	{
		if(max_script_code_index < NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : 주어진 스크립트 코드로 변경할 수 없습니다.\n\t스크립트 코드 : %d", max_script_code_index);
			return RESULT_TYPE_WARNING;
		}

		_max_scriptcode_index = max_script_code_index;

		return RESULT_SUCCESS;		
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::setMaxGroupCodeIndex(type_index max_group_code_index)
	{
		if(max_group_code_index < NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_groupcode_index = max_group_code_index;

		return RESULT_SUCCESS;		
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::getMaxGroupCodeIndex() const
	{
		return _max_groupcode_index;
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::setMaxPriorityCodeIndex(type_index max_priority_code_index)
	{
		if(max_priority_code_index < NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_prioritycode_index = max_priority_code_index;

		return RESULT_SUCCESS;	
	}

	type_index NE_DLL NEScriptManager::ScriptHeader::getMaxPriorityCodeIndex() const
	{
		return _max_prioritycode_index;
	}

	void NE_DLL NEScriptManager::ScriptHeader::release()
	{
		SuperClass::release();

		_release();
	}

	type_result NE_DLL NEScriptManager::ScriptHeader::isValid() const
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result)) return result;
		if(_max_scriptcode_index < NE_INDEX_ERROR) return RESULT_TYPE_ERROR;
		if(_max_namecode_index < NE_INDEX_ERROR) return RESULT_TYPE_ERROR;
		if(_max_groupcode_index < NE_INDEX_ERROR) return RESULT_TYPE_ERROR;
		if(_max_prioritycode_index < NE_INDEX_ERROR) return RESULT_TYPE_ERROR;
		if(_max_node_length < 0) return RESULT_TYPE_ERROR;
		if(_max_module_length < 0) return RESULT_TYPE_ERROR;
		if(_max_key_length < 0) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &NEScriptManager::ScriptHeader::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver	<< _max_scriptcode_index << _max_namecode_index << _max_groupcode_index << _max_prioritycode_index
						<< _max_node_length << _max_module_length << _max_key_length;
	}

	NEBinaryFileLoader NE_DLL &NEScriptManager::ScriptHeader::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		return loader	>> _max_scriptcode_index >> _max_namecode_index >> _max_groupcode_index >> _max_prioritycode_index
						>> _max_node_length >> _max_module_length >> _max_key_length;
	}

	NEObject NE_DLL &NEScriptManager::ScriptHeader::clone() const
	{
		return *(new ThisClass(*this));
	}

	void NEScriptManager::ScriptHeader::_release()
	{
		_max_scriptcode_index = NE_INDEX_ERROR;
		_max_namecode_index = NE_INDEX_ERROR;
		_max_groupcode_index = NE_INDEX_ERROR;
		_max_prioritycode_index = NE_INDEX_ERROR;
		_max_node_length = 0;
		_max_module_length = 0;
		_max_key_length = 0;
	}

	type_result NEScriptManager::ScriptHeader::setMaxNodeLength(type_index max_node_length)
	{
		if(max_node_length < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_node_length = max_node_length;
		return RESULT_SUCCESS;
	}

	NE::type_index NEScriptManager::ScriptHeader::getMaxNodeLength() const
	{
		return _max_node_length;
	}

	type_result NEScriptManager::ScriptHeader::setMaxModuleLength(type_index max_module_length)
	{
		if(max_module_length < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_module_length = max_module_length;
		return RESULT_SUCCESS;
	}

	type_index NEScriptManager::ScriptHeader::getMaxModuleLength() const
	{
		return _max_module_length;
	}

	type_result NEScriptManager::ScriptHeader::setMaxKeyLength(type_index max_key_length)
	{
		if(max_key_length < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_key_length = max_key_length;
		return RESULT_SUCCESS;
	}

	NE::type_index NEScriptManager::ScriptHeader::getMaxKeyLength() const
	{
		return _max_key_length;
	}
}