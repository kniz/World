#pragma once

#include "../pool/Pool.hpp"
#include "../watcher/Watcher.hpp"

namespace wrd {

    class Instancer {
        WRD_DECL_THIS(Instancer)
        WRD_INIT_META(This)
        friend class Instance;

    public:
        wbool bind(const Instance& new1);
        wbool unbind(const Instance& old);
        const Pool& getPool() const;
        const Watcher& getWatcher() const;
        static WRD_SINGLETON_GETTER(This)

    private:
        void* _new1(size_t sz);
        void _del(void* pt, wcnt sz);
        wbool _hasBindTag(const Instance& it) const;

        Pool _pool;
        Watcher _watcher;
    };
}