#include "../../NEStandardPanelManager.hpp"

namespace NE
{
	NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::StandardPanelDLLHeader()
		: NEPanelManager::DLLHeader()
	{
		release();
	}

	NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::StandardPanelDLLHeader(const StandardPanelDLLHeader& source)
		: NEPanelManager::DLLHeader()
	{
		_assign(source);
	}

	NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::~StandardPanelDLLHeader()
	{

	}

	bool NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::isLoadable() const
	{
		return _loadable;
	}

	void NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::setLoadable(bool loadable)
	{
		_loadable = loadable;
	}

	NETString NE_DLL &NEStandardPanelManager::StandardPanelDLLHeader::getPath()
	{
		return _path;
	}

	const NETString NE_DLL &NEStandardPanelManager::StandardPanelDLLHeader::getPath() const
	{
		return _path;
	}

	const HINSTANCE NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::getInstance() const
	{
		return _instance;
	}

	HINSTANCE NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::getInstance()
	{
		return _instance;
	}

	void NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::setInstance(HINSTANCE new_instance)
	{
		_instance = new_instance;
	}

	NEPanelManager::PanelEntryPoint NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::getPanelEntryPoint()
	{
		return _entrypoint;
	}

	const NEPanelManager::PanelEntryPoint NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::getPanelEntryPoint() const
	{
		return _entrypoint;
	}

	void NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::setPanelEntryPoint(PanelEntryPoint new_entry_point)
	{
		_entrypoint = new_entry_point;
	}

	void NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::release()
	{
		_loadable = false;
		_path.release();
		_instance = NE_NULL;
		_entrypoint = NE_NULL;
	}
	
	NEBinaryFileSaver NE_DLL &NEStandardPanelManager::StandardPanelDLLHeader::serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}

	NEBinaryFileLoader NE_DLL &NEStandardPanelManager::StandardPanelDLLHeader::serialize(NEBinaryFileLoader& loader)
	{
		return loader;
	}

	type_result NE_DLL NEStandardPanelManager::StandardPanelDLLHeader::isValid() const
	{
		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NEStandardPanelManager::StandardPanelDLLHeader::clone() const
	{
		return *(new StandardPanelDLLHeader(*this));
	}

	const NEStandardPanelManager::StandardPanelDLLHeader NE_DLL &NEStandardPanelManager::StandardPanelDLLHeader::_assign(const StandardPanelDLLHeader& source)
	{
		if(this == &source) return *this;
		
		_loadable = source._loadable;
		_path = source._path;
		_instance = source._instance;
		_entrypoint = source._entrypoint;
		
		return *this;
	}	
}

