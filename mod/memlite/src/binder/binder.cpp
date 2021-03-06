#include "binder.hpp"
#include "../watcher/bindTag.hpp"
#include "bindTacticable.hpp"
#include "tbindable.inl"

namespace wrd {

    WRD_DEF_ME(binder)

    binder::binder(const type& type, bindTacticable& tactic): _type(&type.getStatic()), _tactic(&tactic) {}
    binder::binder(const me& rhs): _type(rhs._type), _tactic(rhs._tactic) { _assign(rhs); }
    binder::~binder() { me::unbind(); }

    me& me::operator=(const me& rhs) {
        if(this == &rhs) return *this;

        _assign(rhs);
        return *this;
    }

    wbool me::isBind() const {
        const bindTag& tag = _getBindTag();
        if(nul(tag)) return false;

        return tag.isBind();
    }

    wbool me::unbind() {
        return _tactic->unbind(*this);
    }

    id me::getItsId() const { return _itsId; }
    wbool me::canBind(const type& type) const { return getType().isSuper(type); }
    const type& me::getType() const { return *_type; }

    wbool me::bind(const instance& it) {
        unbind();
        if(!tbindable<instance>::bind(it)) return false;

        return _tactic->bind(*this, it);
    }

    instance& me::get() {
        return WRD_GETS(_getBindTag(),get());
    }

    wbool me::_assign(const binder& rhs) {
        unbind();
        _type = rhs._type;
        if (nul(_tactic))
            _tactic = rhs._tactic;
        return bind(rhs.get());
    }

    wbool me::_onSame(const typeProvidable& rhs) const {
        const me& cast = (const me&) rhs;
        return get() == cast.get();
    }

    bindTag& me::_getBindTag() const {
        return const_cast<bindTag&>(bindTag::getBindTag(_itsId));
    }
}
