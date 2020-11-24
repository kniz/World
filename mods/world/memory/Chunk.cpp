#include "Chunk.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Chunk
	WRD_CLASS_DEF(THIS)

	THIS::THIS(wcnt blksize, wbool is_fixed)
		: Allocator(blksize), _heap(0), _is_fixed(is_fixed) { THIS::release(); }
	THIS::~THIS() { THIS::release(); }
	wcnt THIS::getLen() const { return _len; }
	wcnt THIS::getSize() const { return _sz; }

	void* THIS::new1()
	{
		if(	_len >= _sz	&& 
			resize((getSize() + 1) * 2))
			return NULL;

		widx* ret = (widx*)_get(_head);
		if( ! ret)
			return NULL;

		_head = *ret;
		_len++;
		return ret;
	}

	Res& THIS::del(void* used, wcnt)
	{
		if( ! used) return wasnull;
		*(widx*)used = _head;

		_head = ((wuchar*)used - _heap) / _getRealBlkSize();
		_len--;
		return wasgood;
	}

	Res& THIS::release()
	{
		_len = _sz = 0;
		_head = 0;
		return _freeHeap(&_heap);
	}

	Res& THIS::resize(wcnt new_sz)
	{
		//	pre:
		if(new_sz < INIT_SZ) new_sz = INIT_SZ;
		if(_is_fixed) new_sz = INIT_SZ;
		if(new_sz == _sz) return wasoob;

		//	main:
		wuchar* new1 = (wuchar*) _allocHeap(new_sz);
		// considered if user resize far smaller rather than what it had.
		wcnt min = _sz < new_sz ? _sz : new_sz;
		memcpy(new1, _heap, min*_getRealBlkSize());

		//	post:
		_freeHeap(&_heap);
		_heap = new1;
		_sz = new_sz;
		return _index(_len);
	}

	wbool THIS::has(const Instance& it) const
	{
		void* pt = (void*) &it;
		return _heap && _heap <= pt && pt <= getEOB();
	}

	const wuchar* THIS::getEOB() const
	{
		WRD_UNCONST()
		return unconst._getEOB();
	}

	const wuchar* THIS::getHeap() const { return _heap; }
	wbool THIS::isFixed() const { return _is_fixed; }

	void* THIS::_get(widx n)
	{
		if(n < 0 || n >= _sz)
			return NULL;
		return _heap + n*_getRealBlkSize();
	}

	wuchar* THIS::_getEOB()
	{
		wuchar* org = (wuchar*) _get(_sz - 1);
		if( ! org)
			return NULL;

		return org + _getRealBlkSize() - 1;
	}

	Res& THIS::_index(widx start)
	{
		for(wcnt n=start; n < _sz ;n++)
			*(widx*)_get(n) = n+1;

		return wasgood;
	}

	wcnt THIS::_getRealBlkSize() const
	{
		wcnt sz = getBlkSize();
		return sz < 4 ? 4 : sz;
	}

	void* THIS::_allocHeap(wcnt new_sz) { return malloc(new_sz * _getRealBlkSize()); }

	Res& THIS::_freeHeap(wuchar** heap)
	{
		if(*heap)
		{
			free(*heap);
			*heap = NULL;
		}
		return wasgood;
	}
}