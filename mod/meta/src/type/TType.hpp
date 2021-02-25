#pragma once

#include "Type.hpp"
#include "../rtti.hpp"

namespace wrd {

    /// @remark TType returns TType<Type> as its meta class.
    ///         however, this makes impossible to get specific TType instance
    ///         at a binder.
    ///
    ///         if user typedefs SuperType at their type T, then TType
    ///         inherits from given SuperType.
    ///         this eventually make user add API to want to TType class.
    template <typename T>
    class TType : public TSuperTypeDef<T>::is {
        WRD_DECL_THIS(TType<T>, typename TSuperTypeDef<T>::is)

    public:
        TType();

        wbool isTemplate() const override;
        wbool isAbstract() const override;
        const std::string& getName() const override;
        void* make() const override;
        wcnt getSize() const override;
        //TODO: virtual wbool isImmutable() const;
        const Type& getSuper() const override;
        const wbool& isInit() const override;
        static const This& get();

    protected:
        Types& _getSupers() override;
        Types& _getSubs() override;
        Type& _getStatic() const override;

    private:
        TType(wbool); // for skipping recursive static variable init.
    };
}