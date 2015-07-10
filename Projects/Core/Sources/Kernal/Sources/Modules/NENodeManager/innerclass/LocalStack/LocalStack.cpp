#include "../../NENodeManager.hpp"
#include "../../../Kernal/Kernal.hpp"

namespace NE
{
	typedef NENodeManager::LocalStack LocalStack;

	LocalStack::Unwinder::Unwinder(LocalStack& stack)
		: _index_to_unwind(-1), _master(stack)
	{
		_markToUnwind();
	}

	LocalStack::Unwinder::~Unwinder()
	{
		_unwind();
	}

	type_result LocalStack::Unwinder::_unwind()
	{
		return _master._getLocalKeySet()._releaseDirtiedsTill(_index_to_unwind);
	}

	type_result LocalStack::Unwinder::_markToUnwind()
	{
		_index_to_unwind = _master._getLocalKeySet()._dirtieds.getLength();

		return RESULT_SUCCESS;
	}

	typedef NENodeManager::LocalStack::PersistentKeySet PersistentKeySet;
	PersistentKeySet::DirtiedIndexes PersistentKeySet::_dirtieds;

	PersistentKeySet::PersistentKeySet(NEEnlistableManager& manager)
		: SuperClass(manager)
	{

	}

	type_result PersistentKeySet::initialize()
	{
		static NETString prefix = "$";
		const NEKeySet& ks = Kernal::getInstance().getKeyManager().getKeySet();
		const type_count KEYS_PER_TYPE = 5;

		type_count key_count = ks.getLength() * KEYS_PER_TYPE;
		create(key_count);
		_dirty_flags.create(key_count);

		for(int n = 0; n < ks.getLength(); n++)
		{
			const NEKey& src = ks[n];
			NETString name = src.getTypeName();
			name = prefix + name.extract(2, name.getLengthLastIndex() - 3 - 1);

			for(int cnt = 0; cnt < 5; cnt++)
			{
				NEKey& inserted = getElement(push(src));
				inserted.getName() = name + cnt;
				_dirty_flags.push(false);
			}
		}


		return _dirtieds.create(1024);
	}

	NEKey& PersistentKeySet::getElement(type_index n)
	{
		NEKey* null = 0;
		if( !_occupiedset[n]) return *null;

		_makeDirty(n);	

		return SuperClass::getElement(n);
	}	
	type_result PersistentKeySet::_makeDirty(type_index n)
	{
		if(&_dirty_flags[n] && ! _dirty_flags[n])
		{
			//	only push to the bucket for dirties when the value turns 'clean' to 'dirty'.
			//	for removing duplicants.
			_dirtieds.push(n);
			_dirty_flags[n] = true;
		}

		return RESULT_SUCCESS;
	}
	type_result PersistentKeySet::_releaseDirtiedsTill(type_index index_to_release)
	{
		while(index_to_release <= _dirtieds.getLengthLastIndex())
		{
			type_index n = _dirtieds[_dirtieds.getLengthLastIndex()];
			getElement(n).releaseValue();
			_dirty_flags[n] = false;
			_dirtieds.pop();
		}

		return RESULT_SUCCESS;
	}


	NE_DLL NENodeManager::LocalStack::LocalStack()
		: NEObject()
	{

	}

	NE_DLL NENodeManager::LocalStack::LocalStack(const LocalStack& source)
		: NEObject(source)
	{

	}

	NE_DLL NENodeManager::LocalStack::~LocalStack()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NENodeManager::LocalStack::getType() const
	{
		return NEType::LOCALSTACK;
	}	



	type_result LocalStack::insertLocalKey(type_index n, const NEKey& new_key)
	{
		return _getLocalKeySet().insert(n, new_key);
	}



	LocalStack::Unwinder NENodeManager::LocalStack::createUnwinder() const
	{
		LocalStack* casted = const_cast<LocalStack*>(this);

		return LocalStack::Unwinder(*casted);
	}


	type_result NENodeManager::LocalStack::initialize()
	{
		return _getLocalKeySet().initialize();
	}
}
