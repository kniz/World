#include "NEListComponent.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"

namespace NE
{
	NE_DLL NEListComponent::NEListComponent()
		: NEComponent()
	{
		_release();	
	}

	NE_DLL NEListComponent::NEListComponent(const NEListComponent& source)
		: NEComponent(source)
	{
		_assign(source);
	}

	NE_DLL NEListComponent::~NEListComponent()
	{
		
	}

	const NEListComponent NE_DLL &NEListComponent::operator=(const NEListComponent& source)
	{
		NEComponent::operator=(source);

		return _assign(source);
	}

	bool NE_DLL NEListComponent::operator==(const NEListComponent& source) const
	{
		if(this == &source) return true;
		if(NEComponent::operator!=(source)) return false;
		if(_contents != source._contents) return false;
		if(_index != source._index) return false;

		return true;
	}

	bool NE_DLL NEListComponent::operator!=(const NEListComponent& source) const
	{
		return ! (operator==(source));
	}

	const NETStringSet NE_DLL &NEListComponent::getContents() const
	{
		return _contents;
	}

	type_index NE_DLL NEListComponent::getSelectedContentIndex() const
	{
		return _index;
	}

	void NE_DLL NEListComponent::selectContent(type_index index_of_content)
	{
		//	pre:
		if(index_of_content < 0)
		{
			_index = NE_INDEX_ERROR;
			EDITOR_ERROR(" : ")
		}



		//	main:
		_index = index_of_content;
	}

	void NE_DLL NEListComponent::release()
	{
		NEComponent::release();

		return _release();
	}

	type_result NE_DLL NEListComponent::isValid() const
	{
		type_result result = NEComponent::isValid();
		if(NEResult::hasError(result)) return result;
		result = _contents.isValid();
		if(NEResult::hasError(result)) return result;
		if(_index < NE_INDEX_ERROR) return RESULT_TYPE_WARNING | RESULT_WRONG_BOUNDARY | RESULT_INVALID_DATA;

		return RESULT_SUCCESS;
	}

	NEType::Type NE_DLL NEListComponent::getType() const
	{
		return NEType::NELIST_COMPONENT;
	}

	NEBinaryFileSaver NE_DLL &NEListComponent::serialize(NEBinaryFileSaver& saver) const
	{
		NEComponent::serialize(saver);

		return saver << _contents << _index;
	}

	NEBinaryFileLoader NE_DLL &NEListComponent::serialize(NEBinaryFileLoader& loader)
	{
		NEComponent::serialize(loader);

		return loader >> _contents >> _index;
	}

	void NEListComponent::_release()
	{
		_contents.release();
		_index = NE_INDEX_ERROR;
	}

	const NEListComponent& NEListComponent::_assign(const NEListComponent& source)
	{
		if(this == &source) return *this;

		_contents = source._contents;
		_index = source._index;

		return *this;
	}
}
