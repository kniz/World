#include "../../NEStandardNodeManager.hpp"
#include "../../../define/define.hpp"

namespace NE
{
	NE_DLL NEStandardNodeManager::StandardLocalStack::StandardLocalStack()
		: NENodeManager::LocalStack()
	{
		release();
	}

	NE_DLL NEStandardNodeManager::StandardLocalStack::StandardLocalStack(const StandardLocalStack& source)
		: NENodeManager::LocalStack(source)
	{
		_assign(source);
	}

	NE_DLL NEStandardNodeManager::StandardLocalStack::~StandardLocalStack()
	{

	}

	const NE_DLL NEStandardNodeManager::StandardLocalStack& NEStandardNodeManager::StandardLocalStack::operator=(const StandardLocalStack& source)
	{
		NENodeManager::LocalStack::operator=(source);
		
		return _assign(source);
	}

	bool NE_DLL NEStandardNodeManager::StandardLocalStack::operator==(const StandardLocalStack& source) const
	{
		if(this == &source) return true;
		
		if(_frame_count != source._frame_count) return false;
		if(_recent_nodeset_pointer != source._recent_nodeset_pointer) return false;
		if(_recent_moduleset_pointer != source._recent_moduleset_pointer) return false;
		if(_recent_moduleset_index != source._recent_moduleset_index) return false;
		if(_recent_result != source._recent_result) return false;
		if(_recent_priority != source._recent_priority) return false;
		if(_recent_nodeset_pointer != source._recent_nodeset_pointer) return false;
		if(_recent_nodeset_index != source._recent_nodeset_index) return false;
		
		return true;
	}

	bool NE_DLL NEStandardNodeManager::StandardLocalStack::operator!=(const StandardLocalStack& source) const
	{
		return !(operator==(source));
	}

	NENode NE_DLL &NEStandardNodeManager::StandardLocalStack::getRecentNode()
	{
		return *_recent_node_pointer;
	}

	const NENode NE_DLL &NEStandardNodeManager::StandardLocalStack::getRecentNode() const
	{
		return *_recent_node_pointer;
	}

	NEModule NE_DLL &NEStandardNodeManager::StandardLocalStack::getRecentModule()
	{
		NEModule* null_pointer = NE_NULL;
		if(!_recent_moduleset_pointer) return *null_pointer;
		if(_recent_moduleset_index < 0 || _recent_moduleset_index > _recent_moduleset_pointer->getLengthLastIndex()) return *null_pointer;

		return _recent_moduleset_pointer->getElement(_recent_moduleset_index);
	}

	const NEModule NE_DLL &NEStandardNodeManager::StandardLocalStack::getRecentModule() const
	{
		NEModule* null_pointer = NE_NULL;
		if(!_recent_moduleset_pointer) return *null_pointer;
		if(_recent_moduleset_index < 0 || _recent_moduleset_index > _recent_moduleset_pointer->getLengthLastIndex()) return *null_pointer;

		return _recent_moduleset_pointer->getElement(_recent_moduleset_index);		
	}

	NEModuleCodeSet NE_DLL &NEStandardNodeManager::StandardLocalStack::getRecentModuleSet()
	{
		return *(_recent_moduleset_pointer);
	}

	const NEModuleCodeSet NE_DLL &NEStandardNodeManager::StandardLocalStack::getRecentModuleSet() const
	{
		return *(_recent_moduleset_pointer);
	}

	NE::type_index NE_DLL NEStandardNodeManager::StandardLocalStack::getRecentModuleSetIndex() const
	{
		return	_recent_moduleset_index;
	}

	type_result NE_DLL NEStandardNodeManager::StandardLocalStack::getRecentResultCode() const
	{
		return	_recent_result;
	}

	NE::type_code NE_DLL NEStandardNodeManager::StandardLocalStack::getRecentPriorityCode() const
	{
		return _recent_priority;
	}

	NE::type_count NE_DLL NEStandardNodeManager::StandardLocalStack::getFrameCount() const
	{
		return _frame_count;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentNode(NENode& new_node)
	{
		if( ! &new_node )
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ");
			return;
		}
		
		_recent_node_pointer = &new_node;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentModuleSet(NEModuleCodeSet& new_moduleset)
	{
		//	new_moduleset은 0이 될 수도 있다
		_recent_moduleset_pointer = &new_moduleset;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentModuleSetIndex(type_index moduleset_index)
	{
		if( ! &_recent_moduleset_pointer )
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ");
			return;
		}
		if(moduleset_index < 0 || moduleset_index > _recent_moduleset_pointer->getLengthLastIndex())
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ");
			return;
		}

		_recent_moduleset_index = moduleset_index;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentResultCode(type_result new_result)
	{
		_recent_result = new_result;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentPriorityCode(type_code new_priority)
	{		
		const NEScriptHeader& header = Kernal::getInstance().getScriptManager().getScriptHeader();
		if(new_priority < 0 || new_priority > header.getMaxPriorityCodeIndex())
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ");
			return;
		}
	
		_recent_priority = _recent_priority;
	}

	void NEStandardNodeManager::StandardLocalStack::_setFrameCount(type_count new_frame_count)
	{
		if(new_frame_count < 0)
		{
			ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(_T(_NAME), _T(_DEVELOPER), _REVISION), " : ");
			return;
		}
		
		_frame_count = new_frame_count;
	}

	void NE_DLL NEStandardNodeManager::StandardLocalStack::release()
	{
		_frame_count = 0;
		_recent_nodeset_pointer = NE_NULL;
		_recent_moduleset_pointer = NE_NULL;
		_recent_moduleset_index = 0;
		_recent_nodeset_pointer = NE_NULL;
		_recent_nodeset_index = 0;
		_recent_result = RESULT_NOTHING;
		_recent_node_pointer = 0;
		_recent_node_real_index = 0;
		_recent_module_real_index = 0;
		_recent_priority = 0;
	}

	NEBinaryFileLoader NE_DLL &NEStandardNodeManager::StandardLocalStack::serialize(NEBinaryFileLoader& loader)
	{
		//	왜 serialize를 하지 않는가:
		//		LocalStack은, 이전 상황을 저장하는 객체이기 때문에 로드가 필요없다.
		//		LocalStack은 매 프레임마다 초기화가 되고, 덧씌워진다.
		return loader;
	}

	NEBinaryFileSaver NE_DLL &NEStandardNodeManager::StandardLocalStack::serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}

	NEObject NE_DLL &NEStandardNodeManager::StandardLocalStack::clone() const
	{
		return *(new StandardLocalStack(*this));
	}

	type_result NE_DLL NEStandardNodeManager::StandardLocalStack::isValid() const
	{
		type_result result = NENodeManager::LocalStack::isValid();
		if(NEResult::hasError(result)) return result;
		if(_frame_count < 0) return RESULT_TYPE_ERROR;
		if(_recent_moduleset_pointer)
			if(_recent_moduleset_index < 0 || _recent_moduleset_index > _recent_moduleset_pointer->getLengthLastIndex()) return RESULT_TYPE_ERROR;
		const NEScriptHeader& header = Kernal::getInstance().getScriptManager().getScriptHeader();
		if(_recent_priority < 0 || _recent_priority > header.getMaxPriorityCodeIndex()) return RESULT_TYPE_ERROR;
		if(_recent_nodeset_pointer)
			if(_recent_nodeset_index < 0 || _recent_nodeset_index > _recent_nodeset_pointer->getLengthLastIndex()) return RESULT_TYPE_ERROR;
		
		return RESULT_SUCCESS;				
	}

	const NEStandardNodeManager::StandardLocalStack& NEStandardNodeManager::StandardLocalStack::_assign(const StandardLocalStack& source)
	{
		if(this == &source) return *this;
		
		_frame_count = source._frame_count;
		_recent_moduleset_pointer = source._recent_moduleset_pointer;
		_recent_moduleset_index = source._recent_moduleset_index;
		_recent_result = source._recent_result;
		_recent_priority = source._recent_priority;
		_recent_nodeset_pointer = source._recent_nodeset_pointer;
		_recent_nodeset_index = source._recent_nodeset_index;
		
		return *this;
	}

	NENodeCodeSet& NEStandardNodeManager::StandardLocalStack::getRecentNodeSet()
	{
		return *_recent_nodeset_pointer;
	}

	const NENodeCodeSet& NEStandardNodeManager::StandardLocalStack::getRecentNodeSet() const
	{
		return *_recent_nodeset_pointer;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentNodeSet(NENodeCodeSet& new_node_codeset)
	{
		_recent_nodeset_pointer = &new_node_codeset;
	}


	type_index NEStandardNodeManager::StandardLocalStack::getRecentNodeSetIndex() const
	{
		return _recent_nodeset_index;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentNodeSetIndex(type_index nodeset_index)
	{
		_recent_nodeset_index = nodeset_index;	
	}

	type_index NEStandardNodeManager::StandardLocalStack::getRecentNodeRealIndex() const
	{
		return _recent_node_real_index;
	}

	type_index NEStandardNodeManager::StandardLocalStack::getRecentModuleRealIndex() const
	{
		return _recent_module_real_index;
	}

	void NEStandardNodeManager::StandardLocalStack::_setRecentNodeRealIndex(type_index real_node_index)
	{
		_recent_node_real_index = real_node_index;
	}
}