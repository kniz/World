#include "NEComponent.hpp"
#include "../NEDialog/NEDialog.hpp"

namespace NE
{
	NE_DLL NEComponent::NEComponent()
		: NEUnit()
	{
		
	}
	NE_DLL NEComponent::NEComponent(const NEComponent& source)
		: NEUnit(source)
	{
		_assign(source);
	}
	NE_DLL NEComponent::~NEComponent()
	{

	}
	const NEComponent NE_DLL &NEComponent::operator=(const NEComponent& source)
	{
		return _assign(source);
	}
	bool NE_DLL NEComponent::operator==(const NEComponent& source) const
	{
		if(this == &source) return true;
		if(_caption != source._caption) return false;
		if(_comment != source.getComment()) return false;

		return true;
	}
	bool NE_DLL NEComponent::operator!=(const NEComponent& source) const
	{
		return !(operator==(source));
	}
	void NE_DLL NEComponent::release()
	{
		_caption.release();
		_comment.release();
	}
	type_result NE_DLL NEComponent::isValid() const
	{
		type_result result = _caption.isValid();
		if(NEResult::hasError(result)) return result;
		result = _comment.isValid();
		if(NEResult::hasError(result)) return result;
		
		return RESULT_SUCCESS;
	}
	NEBinaryFileSaver& NEComponent::serialize(NEBinaryFileSaver& saver) const
	{
		NEUnit::serialize(saver);

		return saver << _caption << _comment;
	}
	NEBinaryFileLoader& NEComponent::serialize(NEBinaryFileLoader& loader)
	{
		NEUnit::serialize(loader);

		return loader >> _caption >> _comment;
	}
	type_result NE_DLL NEComponent::execute()
	{
		return RESULT_SUCCESS;
	}
	type_result NEComponent::_onLoad(NEPanel& panel)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;
	}
	type_result NEComponent::_onUnload(NEPanel& panel)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;
	}
	type_result NEComponent::_onUpdate(NEPanel& panel)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;
	}
	type_result NEComponent::_onFocus(NEPanel& panel)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;
	}
	type_result NEComponent::_onUnfocus(NEPanel& panel)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;
	}
	type_result NEComponent::_onDialogueReturned(NEPanel& panel, NEDialog& dialogue)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;	
	}
	type_result NEComponent::_onDisabled(NEPanel& panel)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;	
	}
	type_result NEComponent::_onEnabled(NEPanel& panel)
	{
		return RESULT_SUCCESS | RESULT_NOT_IMPLEMENTED;	
	}
	const NEComponent& NEComponent::_assign(const NEComponent& source)
	{
		if(this == &source) return *this;

		_caption = source._caption;
		_comment = source._comment;

		return *this;
	}

	const NETString& NEComponent::getComment() const
	{
		return _comment;
	}

	NETString& NEComponent::getComment()
	{
		return _comment;
	}

	const NETString& NEComponent::getCaption() const
	{
		return _caption;
	}

	NETString& NEComponent::getCaption()
	{
		return _caption;
	}
}
