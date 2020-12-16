#include "Chunk.hpp"

namespace wrd { namespace memlite {

	WRD_DEF_THIS(Chunk, Allocator)

	This::Chunk(wcnt blksize, wbool is_fixed)
        : Super(blksize), _heap(0), _is_fixed(is_fixed) { This::rel(); }
	This::~Chunk() { This::rel(); }
	wcnt This::getLen() const { return _len; }
	wcnt This::getSize() const { return _sz; }

	void* This::new1()
	{
		if(	_len >= _sz	&& 
			!resize((getSize() + 1) * 2))
			return NULL;

		widx* ret = (widx*)_get(_head);
		if( ! ret)
			return NULL;

		_head = *ret;
		_len++;
		return ret;
	}

	wbool This::del(void* used, wcnt)
	{
		if(!used) return false;
		*(widx*)used = _head;

		_head = ((wuchar*)used - _heap) / _getRealBlkSize();
		_len--;
		return true;
	}

	wbool This::rel()
	{
		_len = _sz = 0;
		_head = 0;
		return _freeHeap(&_heap);
	}

	wbool This::resize(wcnt new_sz)
	{
		//	pre:
		if(new_sz < INIT_SZ) new_sz = INIT_SZ;
		if(_is_fixed) new_sz = INIT_SZ;
		if(new_sz == _sz) return false;

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

	wbool This::has(const Instance& it) const
	{
		void* pt = (void*) &it;
		return _heap && _heap <= pt && pt <= getEOB();
	}

	const wuchar* This::getEOB() const WRD_UNCONST_FUNC(_getEOB())
	const wuchar* This::getHeap() const { return _heap; }
	wbool This::isFixed() const { return _is_fixed; }

	void* This::_get(widx n)
	{
		if(n < 0 || n >= _sz)
			return WRD_NULL;
		return _heap + n*_getRealBlkSize();
	}

	wuchar* This::_getEOB()
	{
		wuchar* org = (wuchar*) _get(_sz - 1);
		if(!org)
			return WRD_NULL;

		return org + _getRealBlkSize() - 1;
	}

	wbool This::_index(widx start)
	{
		for(wcnt n=start; n < _sz ;n++)
			*(widx*)_get(n) = n+1;

		return true;
	}

	wcnt This::_getRealBlkSize() const
	{
		wcnt sz = getBlkSize();
		return sz < 4 ? 4 : sz;
	}

	void* This::_allocHeap(wcnt new_sz) { return malloc(new_sz * _getRealBlkSize()); }

	wbool This::_freeHeap(wuchar** heap)
	{
		if(*heap)
		{
			free(*heap);
			*heap = NULL;
		}
		return true;
	}
}}