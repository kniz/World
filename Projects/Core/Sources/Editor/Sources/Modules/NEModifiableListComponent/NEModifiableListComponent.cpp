#include "NEModifiableListComponent.hpp"
#include "../NEDebugManager/innerclass/EditDebugMacro/EditDebugMacro.hpp"

namespace NE
{
	NE_DLL NEModifiableListComponent::NEModifiableListComponent()
		: NEListComponent()
	{
		
	}

	NE_DLL NEModifiableListComponent::NEModifiableListComponent(const NEModifiableListComponent& source)
		: NEListComponent(source)
	{
		_text = source._text;
	}

	NE_DLL NEModifiableListComponent::~NEModifiableListComponent()
	{

	}

	const NEModifiableListComponent NE_DLL &NEModifiableListComponent::operator=(const NEModifiableListComponent& source)
	{
		NEListComponent::operator=(source);

		_text = source._text;
		
		return *this;
	}

	bool NE_DLL NEModifiableListComponent::operator==(const NEModifiableListComponent& source) const
	{
		if(this == &source) return true;
		if(NEListComponent::operator!=(source)) return false;
		if(_text != source._text) return false;

		return true;
	}

	bool NE_DLL NEModifiableListComponent::operator!=(const NEModifiableListComponent& source) const
	{
		return ! (operator==(source));
	}

	void NE_DLL NEModifiableListComponent::release()
	{
		NEListComponent::release();

		_text.release();
	}

	type_result NE_DLL NEModifiableListComponent::isValid() const
	{
		type_result result = NEListComponent::isValid();
		if(NEResult::hasError(result)) return result;
		result = _text.isValid();
		if(NEResult::hasError(result)) return result;
		
		return RESULT_SUCCESS;
	}

	NEType::Type NE_DLL NEModifiableListComponent::getType() const
	{
		return NEType::NEMODIFIABLE_LIST_COMPONENT;
	}

	NEBinaryFileSaver NE_DLL &NEModifiableListComponent::serialize(NEBinaryFileSaver& saver) const
	{
		NEListComponent::serialize(saver);

		return saver << _text;
	}

	NEBinaryFileLoader NE_DLL &NEModifiableListComponent::serialize(NEBinaryFileLoader& loader)
	{
		NEListComponent::serialize(loader);

		return loader >> _text;
	}

	NETString NE_DLL &NEModifiableListComponent::getText()
	{
		return _text;
	}

	const NETString NE_DLL &NEModifiableListComponent::getText() const
	{
		return _text;
	}

	type_result NE_DLL NEModifiableListComponent::setText(const NETString& source)
	{
		if( ! &source)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		
		_text = source;
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEModifiableListComponent::removeSelectedContentFromContents()
	{
		//	pre:
		if(_index < 0 || _index > _contents.getLengthLastIndex())
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		
		
		
		//	main:
		//		삭제:
		type_result result = _contents.remove(_index);
		if(NEResult::hasError(result))
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		//		크기 컴팩트화:
		if(_contents.getLength() != _contents.getSize())
			_contents.resize(_contents.getLength());
		
		
		
		//	post:
		//		index 조정:
		if(_index > _contents.getLengthLastIndex())
			_index = _contents.getLengthLastIndex();
			
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEModifiableListComponent::insertTextInputedToContents()
	{
		//	pre:
		if(_text.getLength() <= 0)
		{
			EDITOR_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}
		
		
		
		//	main:
		//		필요시 크기 확장:
		if(_contents.getLength() == _contents.getSize())
			_contents.resize(_contents.getSize() + 1);
		//		삽입:
		_contents.push(_text);
		
		
		
		//	post:
		_text.release();
		return RESULT_SUCCESS;
	}
}
