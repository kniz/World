#include "WeakTactic.hpp"
#include "Bind.hpp"

namespace wrd {

    WRD_DEF_THIS(WeakTactic)

    wbool This::assign(Bind& me, const Bind& rhs) {
        if(&me == &rhs) return true;

        me._tactic = rhs._tactic;
        return me.bind(rhs.get());
    }

    wbool This::unbind(Bind& me) {
        me._itsId.rel();
        return true;
    }

    wbool This::bind(Bind& me, const Instance& it) {
        unbind(me);
        //  regardless of result from _onStrong binder can bind:
        //      there are two reasons:
        //          because Block has equal lifecycle to what it bind, if there is
        //          a request by user to refer a bind for binding freed instance,
        //          user has responsibilty to treat wrongly.
        //          so, we should not consider such cases.
        //
        //      and:
        //          no matter how block reacts, anyway it won't refuse binder's
        //          refering. for instance, the scenario for binding non-heap allocated
        //          instance.
        me._itsId = it.getId();
        return true;
    }

    This This::singletone;
}