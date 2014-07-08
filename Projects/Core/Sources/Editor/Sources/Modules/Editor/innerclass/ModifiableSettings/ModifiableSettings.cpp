#include "../../Editor.hpp"

namespace NE
{
	NE_DLL Editor::ModifiableSettings::ModifiableSettings()
		: NEObject()
	{

	}

	NE_DLL Editor::ModifiableSettings::ModifiableSettings(const Editor::ModifiableSettings& source)
		: NEObject(source)
	{
		_assign(source);
	}

	NE_DLL Editor::ModifiableSettings::~ModifiableSettings()
	{

	}

	const Editor::ModifiableSettings NE_DLL &Editor::ModifiableSettings::operator=(const Editor::ModifiableSettings& source)
	{
		return _assign(source);
	}

	bool NE_DLL Editor::ModifiableSettings::operator==(const Editor::ModifiableSettings& source) const
	{
		if(this == &source) return true;
		if(_panel_directory != source._panel_directory) return false;
		if(_is_loading_from_ini != source._is_loading_from_ini) return false;

		return true;
	}

	bool NE_DLL Editor::ModifiableSettings::operator!=(const Editor::ModifiableSettings& source) const
	{
		return ! (operator==(source));
	}

	void NE_DLL Editor::ModifiableSettings::release()
	{
		_panel_directory.release();
	}

	type_result NE_DLL Editor::ModifiableSettings::isValid() const
	{
		type_result result = _panel_directory.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	NEObject NE_DLL &Editor::ModifiableSettings::clone() const
	{
		return *(new ModifiableSettings(*this));
	}

	NEBinaryFileSaver NE_DLL &Editor::ModifiableSettings::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _panel_directory << _is_loading_from_ini;
	}

	NEBinaryFileLoader NE_DLL &Editor::ModifiableSettings::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _panel_directory >> _is_loading_from_ini;
	}

	NEType::Type NE_DLL Editor::ModifiableSettings::getType() const
	{
		return NEType::EDITOR_MODIFIABLE_SETTINGS;
	}

	const NETString NE_DLL &Editor::ModifiableSettings::getPanelDirectory() const
	{
		return _panel_directory;
	}

	const Editor::ModifiableSettings& Editor::ModifiableSettings::_assign(const Editor::ModifiableSettings& source)
	{
		if(this == &source) return *this;
		_panel_directory = source._panel_directory;
		_is_loading_from_ini = source._is_loading_from_ini;

		return *this;
	}

	type_result NE_DLL Editor::ModifiableSettings::setPanelDirectory(const NETString& panel_directory)
	{
		//	pre:
		if( ! &panel_directory)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}
		if(panel_directory.getLength() <= 0)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}



		//	main:
		_panel_directory = panel_directory;



		//	post:
		return _fixWhenDirectoryHasNotSlashAtTheEnd(_panel_directory);
	}

	bool NE_DLL Editor::ModifiableSettings::isLoadedFromINI() const
	{
		return _is_loading_from_ini;
	}

	void NE_DLL Editor::ModifiableSettings::setLoadFromINI(bool enable)
	{
		_is_loading_from_ini = enable;
	}

	type_result Editor::ModifiableSettings::_fixWhenDirectoryHasNotSlashAtTheEnd(NETString& directory_string_to_be_validate) const
	{
		//	pre:
		if( ! &directory_string_to_be_validate)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}
		if(directory_string_to_be_validate.getLength() <= 0)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}



		//	main:
		type_index last_index = directory_string_to_be_validate.getLengthLastIndex() - 1; // 마지막 글자는 널문자이기 때문에 -1 한다.
		TCHAR last_word = directory_string_to_be_validate[last_index];
		if(	last_word != _T('/')	&&
			last_word != _T('\\')	)
			directory_string_to_be_validate += _T("\\");		

		return RESULT_SUCCESS;
	}
}
