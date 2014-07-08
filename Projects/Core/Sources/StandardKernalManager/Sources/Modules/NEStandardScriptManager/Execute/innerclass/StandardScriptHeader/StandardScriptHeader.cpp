#include "../../NEStandardScriptManager.hpp"
#include "../../../define/define.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEStandardScriptManager::StandardScriptHeader::StandardScriptHeader()
		: NEScriptManager::ScriptHeader()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEStandardScriptManager::StandardScriptHeader::StandardScriptHeader(const NEStandardScriptManager::StandardScriptHeader& source)
		: NEScriptManager::ScriptHeader(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEStandardScriptManager::StandardScriptHeader::~StandardScriptHeader()
	{

	}



	const NEStandardScriptManager::StandardScriptHeader NE_DLL &NEStandardScriptManager::StandardScriptHeader::operator=(const StandardScriptHeader& source)
	{
		NEScriptManager::ScriptHeader::operator=(source);

		return _assign(source);
	}

	bool NE_DLL NEStandardScriptManager::StandardScriptHeader::operator==(const StandardScriptHeader& source) const
	{
		if(this == &source) return true;
		if(NEScriptManager::ScriptHeader::operator!=(source)) return false;
		if(_max_scriptcode_index != source._max_scriptcode_index) return false;
		if(_max_namecode_index != source._max_namecode_index) return false;
		if(_max_groupcode_index != source._max_groupcode_index) return false;
		if(_max_prioritycode_index != source._max_prioritycode_index) return false;

		return true;
	}

	bool NE_DLL NEStandardScriptManager::StandardScriptHeader::operator!=(const StandardScriptHeader& source) const
	{
		return !(operator==(source));
	}

	const NEStandardScriptManager::StandardScriptHeader& NEStandardScriptManager::StandardScriptHeader::_assign(const StandardScriptHeader& source)
	{
		if(this == &source) return *this;

		_max_scriptcode_index = source._max_scriptcode_index;
		_max_namecode_index = source._max_namecode_index;
		_max_groupcode_index = source._max_groupcode_index;
		_max_prioritycode_index = source._max_prioritycode_index;

		return *this;
	}

	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::setMaxNameCodeIndex(type_index max_name_code_index)
	{
		if(max_name_code_index < 0)
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ")
			return RESULT_TYPE_WARNING;
		}
				
		_max_namecode_index = max_name_code_index;
		
		return RESULT_SUCCESS;
	}

	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::getMaxNameCodeIndex() const
	{
		return _max_namecode_index;
	}

	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::getMaxScriptCodeIndex() const
	{
		return _max_scriptcode_index;
	}

	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::setMaxScriptCodeIndex(type_index max_script_code_index)
	{
		if(max_script_code_index < 0)
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ")
			return RESULT_TYPE_WARNING;
		}

		_max_scriptcode_index = max_script_code_index;

		return RESULT_SUCCESS;		
	}

	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::setMaxGroupCodeIndex(type_index max_group_code_index)
	{
		if(max_group_code_index < 0)
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ")
			return RESULT_TYPE_WARNING;
		}

		_max_groupcode_index = max_group_code_index;

		return RESULT_SUCCESS;		
	}
	 
	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::getMaxGroupCodeIndex() const
	{
		return _max_groupcode_index;
	}

	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::setMaxPriorityCodeIndex(type_index max_priority_code_index)
	{
		if(max_priority_code_index < 0)
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ")
			return RESULT_TYPE_WARNING;
		}

		_max_prioritycode_index = max_priority_code_index;

		return RESULT_SUCCESS;	
	}

	type_index NE_DLL NEStandardScriptManager::StandardScriptHeader::getMaxPriorityCodeIndex() const
	{
		return _max_prioritycode_index;
	}

	void NE_DLL NEStandardScriptManager::StandardScriptHeader::release()
	{
		NEScriptManager::ScriptHeader::release();
		
		_release();
	}

	type_result NE_DLL NEStandardScriptManager::StandardScriptHeader::isValid() const
	{
		type_result result = NEScriptManager::ScriptHeader::isValid();
		if(NEResult::hasError(result)) return result;
		if(_max_scriptcode_index < 0) return RESULT_TYPE_ERROR;
		if(_max_namecode_index < 0) return RESULT_TYPE_ERROR;
		if(_max_groupcode_index < 0) return RESULT_TYPE_ERROR;
		if(_max_prioritycode_index < 0) return RESULT_TYPE_ERROR;
		
		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &NEStandardScriptManager::StandardScriptHeader::serialize(NEBinaryFileSaver& saver) const
	{
		NEScriptManager::ScriptHeader::serialize(saver);
		
		return saver << _max_scriptcode_index << _max_namecode_index << _max_groupcode_index << _max_prioritycode_index;
	}

	NEBinaryFileLoader NE_DLL &NEStandardScriptManager::StandardScriptHeader::serialize(NEBinaryFileLoader& loader)
	{
		NEScriptManager::ScriptHeader::serialize(loader);
	
		return loader >> _max_scriptcode_index >> _max_namecode_index >> _max_groupcode_index >> _max_prioritycode_index;
	}

	NEObject NE_DLL &NEStandardScriptManager::StandardScriptHeader::clone() const
	{
		return *(new StandardScriptHeader(*this));
	}

	void NEStandardScriptManager::StandardScriptHeader::_release()
	{
		//	인덱스를 0으로 초기화 하는 이유:
		//		인덱스가 0이라는 건, ShortCutSet의 size가 0이 아니라 1이라는 전제조건이 
		//		필요하다는 걸 의미한다.
		//		모든 노드, 모듈은 지정하지 않으면 0으로 초기화가 되기 때문에, 0이라는 건
		//		지정되지 않음(= undefined)를 의미한다.
		//		따라서 0번의 코드값(script, scriptcode, priority, namecode, groupcode)는 항상
		//		필요하다.
		_max_scriptcode_index = 0;
		_max_namecode_index = 0;
		_max_groupcode_index = 0;
		_max_prioritycode_index = 0;
	}
}
