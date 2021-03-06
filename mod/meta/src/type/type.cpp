#include "type.hpp"

namespace wrd {
    WRD_DEF_ME(type)

    wbool me::operator==(const me& rhs) const { return &getName() == &rhs.getName(); }
    wbool me::operator!=(const me& rhs) const { return !operator==(rhs); }

    const types& me::getLeafs() const {
        //TODO: change to range based for loop.
        return nulOf<types>();
    }

    wbool me::init() {
        //  pre:
        //      Caution for not refering metaclass and binding inside of this:
        //          while this func is called, a structuring for metaclass doesn't finished.
        //          so if you call funcs using metaclass (in)directly, that calling makes
        //          crash or infinite loop.
        //          please you make sure not to use those APIs.
        //
        //      Object class should not initialize explicitly:
        //          or me makes recursive call. Because if we make a instance of TType<Object>,
        //          it triggers Type::init inside of it.
        if(isInit()) return false;

        //  main:
        //      setting init flag first is important:
        //          when we construct structure between super and subs,
        //          we need to assign ptr of static variable. but can't gaurantee that this ptr is
        //          belonged to static memory. so we're going to use get() static func.
        //          when static variable at get() func was not initialized before, its constructor
        //          will leds us to here, however nothing serius happen because init flag was set
        //          to true.
        _setInit(true);
        WRD_DI("initializing %s type's meta info...", getName().c_str());
        //      get Supers info from Super:
        //          at this point TType<Super> is instantiated, and "Super" also is all of this
        //          sequences.
        type& super = const_cast<type&>(getSuper());
        super.init();
        //        constructing SuperType:
        types& mySupers = _getSupers();
        mySupers = super._getSupers();
        mySupers.push_back(&super);
        //        notify to super:
        super._getSubs().push_back(&_getStatic());
        return _logInitOk(true);
    }

    wbool me::rel() {
        // TODO:
        _setInit(false);
        return true;
    }

    wbool me::isSuper(const type& it) const {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(nul(it)) return false;
        const types& its = it.getSupers();
        wcnt myTier = getSupers().size(),
             itsTier = its.size();
        if(myTier > itsTier) return false;


        //  main:
        const type& target = itsTier == myTier ? it :
            (const type&) *its[myTier];

        return *this == target; // operator== is virtual func.
    }

    wbool me::_logInitOk(wbool res) {
        if(!res) {
            WRD_E("couldn't init meta of %s class.", getName().c_str());
            return res;
        }

#define _FUNC(func) WRD_DI("\t  ." #func "=%s", func ? "true" : "false");
        WRD_EACH(_FUNC, isTemplate(), isAbstract())
#undef _FUNC

        WRD_DI("... %s class init completed.", getName().c_str());
        return res;
    }
}
