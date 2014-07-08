#include "NETextComponent.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"

namespace NE
{
	NE_DLL NETextComponent::NETextComponent()
		: NEComponent()
	{
		_release();
	}
	NE_DLL NETextComponent::NETextComponent(const NETextComponent& source)
		: NEComponent(source)
	{
		_text = source._text;
		_is_text_fixed = source._is_text_fixed;
	}
	NE_DLL NETextComponent::~NETextComponent()
	{

	}
	const NETextComponent NE_DLL &NETextComponent::operator=(const NETextComponent& source)
	{
		//	pre:
		//		파라메터 체크:
		if(this == &source) return *this;
		//		상위클래스 호출:
		NEComponent::operator=(source);



		//	main:
		_text = source._text;
		_is_text_fixed = source._is_text_fixed;



		//	post:
		return *this;
	}
	bool NE_DLL NETextComponent::operator==(const NETextComponent& source) const
	{
		if(this == &source) return true;
		if(NEComponent::operator==(source) == false) return false;		
		if(_text != source._text) return false;
		if(_is_text_fixed != source._is_text_fixed) return false;

		return true;
	}
	bool NE_DLL NETextComponent::operator!=(const NETextComponent& source) const
	{
		return !(operator==(source));
	}

	bool NE_DLL NETextComponent::isTextFixed() const
	{
		return _is_text_fixed;
	}

	void NE_DLL NETextComponent::setTextFixed(bool is_text_fixed)
	{
		_is_text_fixed = is_text_fixed;
	}

	NETString NE_DLL NETextComponent::getText() const
	{
		return NETString(_text);
	}

	type_result  NE_DLL NETextComponent::setText(const NETString& source)
	{
		if( !_is_text_fixed )
		{
			_text = source;
			return RESULT_SUCCESS;
		}
		else
		{
			EDITOR_INFORMATION(" : ")
			return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION | RESULT_INVALID_DATA | RESULT_ACCESS_DENIED;
		}
	}

	void NE_DLL NETextComponent::release()
	{
		NEComponent::release();

		_release();
	}
	type_result NE_DLL NETextComponent::isValid() const
	{
		type_result result = NEComponent::isValid();
		if(NEResult::hasError(result)) return result;
		result = _text.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}
	NEType::Type NE_DLL NETextComponent::getType() const
	{
		return NEType::NETEXT_COMPONENT;
	}
	NEBinaryFileSaver NE_DLL &NETextComponent::serialize(NEBinaryFileSaver& saver) const
	{
		NEComponent::serialize(saver);

		return saver << _text;
	}
	NEBinaryFileLoader NE_DLL &NETextComponent::serialize(NEBinaryFileLoader& loader)
	{
		NEComponent::serialize(loader);

		return loader >> _text;
	}

	void NETextComponent::_release()
	{
		_text.release();
		_is_text_fixed = false;
	}
}
