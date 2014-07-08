#include "NECheckListComponent.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"

namespace NE
{
	NE_DLL NECheckListComponent::NECheckListComponent()
		: NEListComponent()
	{
		_release();
	}	

	NE_DLL NECheckListComponent::NECheckListComponent(const NECheckListComponent& source)
		: NEListComponent(source)
	{
		_assign(source);
	}

	NE_DLL NECheckListComponent::~NECheckListComponent()
	{

	}

	const NECheckListComponent NE_DLL &NECheckListComponent::operator=(const NECheckListComponent& source)
	{
		NEListComponent::operator=(source);

		return _assign(source);
	}

	bool NE_DLL NECheckListComponent::operator==(const NECheckListComponent& source) const
	{
		if(this == &source) return true;
		if(NEListComponent::operator!=(source)) return false;
		if(_contents != source._contents) return false;
		if(_checkset != source._checkset) return false;

		return true;
	}

	bool NE_DLL NECheckListComponent::operator!=(const NECheckListComponent& source) const
	{
		return ! (operator==(source));
	}

	void NE_DLL NECheckListComponent::check(type_index index, bool is_checked)
	{
		if(	index < 0								||
			index > _contents.getLengthLastIndex()	)
			return;

		_checkset[index] = is_checked;
		selectContent(index);
	}

	const NEBooleanSet NE_DLL &NECheckListComponent::getCheckSet() const
	{
		return _checkset;
	}

	void NE_DLL NECheckListComponent::release()
	{
		NEListComponent::release();

		return _release();
	}

	type_result NE_DLL NECheckListComponent::isValid() const
	{
		type_result result = NEListComponent::isValid();
		result = _checkset.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	NEType::Type NE_DLL NECheckListComponent::getType() const
	{
		return NEType::NECHECKLIST_COMPONENT;
	}

	NEBinaryFileSaver NE_DLL &NECheckListComponent::serialize(NEBinaryFileSaver& saver) const
	{
		NEListComponent::serialize(saver);

		return saver << _contents << _checkset;
	}

	NEBinaryFileLoader NE_DLL &NECheckListComponent::serialize(NEBinaryFileLoader& loader)
	{
		NEListComponent::serialize(loader);

		return loader >> _contents >> _checkset;
	}

	void NECheckListComponent::_release()
	{
		_contents.release();
		_checkset.release();
	}

	const NECheckListComponent& NECheckListComponent::_assign(const NECheckListComponent& source)
	{
		if(this == &source) return *this;

		_contents = source._contents;
		_checkset = source._checkset;

		return *this;
	}
}
