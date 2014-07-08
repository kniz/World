#ifdef DEVELOPER

#include "../../NEDebugManager.hpp"
#include "../../define/define.hpp"

namespace NE
{
	NE_DLL NEDebugManager::Flag::Flag()
		: NEObject()
	{
		release();
	}

	NE_DLL NEDebugManager::Flag::Flag(const TCHAR& source)
		: NEObject()
	{
		_flag = source;
	}

	NE_DLL NEDebugManager::Flag::Flag(const Flag& source)
		: NEObject(source)
	{
		_flag = source._flag;
	}

	NE_DLL NEDebugManager::Flag::~Flag()
	{
		
	}
	
	const NEDebugManager::Flag NE_DLL &NEDebugManager::Flag::operator=(const Flag& source)
	{
		return _assign(source);
	}

	bool NE_DLL NEDebugManager::Flag::operator==(const Flag& source) const
	{
		if(this == &source) return true;
		if(getFlag() != source.getFlag()) return false;

		return true;
	}

	bool NE_DLL NEDebugManager::Flag::operator!=(const Flag& source) const
	{
		return !(operator==(source));
	}
	
	TCHAR NE_DLL NEDebugManager::Flag::getFlag() const
	{
		return _flag;
	}

	void NE_DLL NEDebugManager::Flag::setFlag(TCHAR flag)
	{
		_flag = flag;
	}

	bool NE_DLL NEDebugManager::Flag::isLogShown() const
	{
		return (_flag & _LOG) != 0;
	}

	void NE_DLL NEDebugManager::Flag::setLogShown(bool enable)
	{
		if(enable)
			_flag = _flag | _LOG;
		else
			_flag = _flag & (~_LOG);
	}

	bool NE_DLL NEDebugManager::Flag::isConsoleShown() const
	{
		return (_flag & _CONSOLE) != 0;
	}

	void NE_DLL NEDebugManager::Flag::setConsoleShown(bool enable)
	{
		if(enable)
			_flag = _flag | _CONSOLE;
		else
			_flag = _flag & (~_CONSOLE);
	}

	bool NE_DLL NEDebugManager::Flag::isMessageBoxShown() const
	{
		return (_flag & _MESSAGEBOX) != 0;
	}

	void NE_DLL NEDebugManager::Flag::setMessageBoxShown(bool enable)
	{
		if(enable)
			_flag = _flag | _MESSAGEBOX;
		else
			_flag = _flag & (~_MESSAGEBOX);
	}

	bool NE_DLL NEDebugManager::Flag::isDebugWindowShown() const
	{
		return (_flag & _DEBUGWINDOW) != 0;
	}

	void NE_DLL NEDebugManager::Flag::setDebugWindowShown(bool enable)
	{
		if(enable)
			_flag = _flag | _DEBUGWINDOW;
		else
			_flag = _flag & (~_DEBUGWINDOW);
	}

	void NE_DLL NEDebugManager::Flag::release()
	{
		_flag = _DEFAULT_MODULE_FLAG;
	}

	type_result NE_DLL NEDebugManager::Flag::isValid() const
	{
		if(_flag < 0 || _flag > (_MESSAGEBOX | _CONSOLE | _DEBUGWINDOW | _LOG)) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &NEDebugManager::Flag::clone() const
	{
		return *(new NEDebugManager::Flag(*this));
	}

	NEBinaryFileSaver NE_DLL &NEDebugManager::Flag::serialize( NEBinaryFileSaver& saver) const
	{
		return saver << _flag;
	}

	NEBinaryFileLoader NE_DLL &NEDebugManager::Flag::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _flag;
	}

	NEType::Type NE_DLL NEDebugManager::Flag::getType() const
	{
		return NEType::NEDEBUG_MANAGER;
	}
	
	const NEDebugManager::Flag& NEDebugManager::Flag::_assign(const Flag& source)
	{
		if(this == &source) return *this;
		
		setFlag(source.getFlag());
		
		return *this;
	}
}

#endif
