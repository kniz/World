#include "../common/dep.hpp"
#include <functional>

using namespace wrd;
using namespace std;

namespace {
    class MyFunc : public Func {
        WRD_CLASS(MyFunc, Func)

    public:
        MyFunc(std::string name = "MyFunc"): Super(name) {
            WRD_E("MyFunc(%x) new", this);
        }
        ~MyFunc() {
            WRD_E("MyFunc(%x) delete", this);
        }

        using Super::subs;
        NContainer& subs() override { return _shares; }

        void setUp() {
            _executed = false;
            _res = false;
        }

        wbool isRun() const {
            return _executed;
        }

        void setLambda(function<wbool(const NContainer&, const StackFrame&)> lambda) {
            _lambda = lambda;
        }

        wbool isSuccess() const {
            return _res;
        }

        const WTypes& getTypes() const override { return _types; }
        WTypes& getTypes() { return _types; }

    protected:
        Str _onRun(NContainer& args) override {
            WRD_I("hello world!");
            _executed = true;

            if(_lambda)
                _res = _lambda(args, (StackFrame&) Thread::get().getStackFrame());
            return Str();
        }

    private:
        wbool _executed;
        wbool _res;
        function<wbool(const NContainer&, const StackFrame&)> _lambda;
        NArr _shares;
        WTypes _types;
    };
}

wbool checkFrameHasFuncAndObjScope(const Frame& fr, const Func& func, const Obj& obj) {
    if(nul(fr)) return false;

    int n = 0;
    WRD_E("fr.len=%d", fr.subs().getLen());
    for(Iter e=fr.subs().head(); e ;e++)
        WRD_E(" - Func(\"%s\") calls: fr[%d]=%s", func.getName().c_str(), n++, e->getType().getName().c_str());

    const NChain& funcScope = fr.subs().cast<NChain>();
    if(nul(funcScope)) return WRD_E("nul(funcScope)"), false;
    if(&func.subs() != &funcScope.getContainer())
        return WRD_E("func.subs(%x) != funcScope(%x)", &func.subs(), &funcScope), false;

    const NChain& objScope = funcScope.getNext();
    if(nul(objScope)) return WRD_E("nul(objScope)"), false;
    if(&obj.subs() != &objScope)
        return WRD_E("obj.subs(%x) != objScope(%x)", &obj.subs(), &objScope), false;

    NArr foundFunc = fr.sub(func.getName());
    if(foundFunc.getLen() != 1)
        return WRD_E("couldn't find %s func on frame(%x)", func.getName().c_str(), &fr), false;

    return true;
}

TEST(FuncFixture, testFuncConstructNewFrame) {
    Obj obj;
    MyFunc func;
    obj.subs().add(func);
    WRD_E("obj.len=%d", obj.subs().getLen());
    int n = 0;
    for(Iter e=obj.subs().head(); e ;e++) {
        WRD_E(" - fr[%d]=%s", n++, e->getType().getName().c_str());
    }

    NArr args;
    args.add(obj);

    func.setLambda([&func, &obj](auto args, auto sf) {
        if(sf.getLen() != 1) return false;

        return checkFrameHasFuncAndObjScope(sf[0], func, obj);
    });

    func.run(args);
    ASSERT_TRUE(func.isRun());
    ASSERT_TRUE(func.isSuccess());
    ASSERT_TRUE(func.isSuccess());
    func.setLambda(nullptr);
}

TEST(FuncFixture, testCallFuncInsideFunc) {
    Obj obj1;
    MyFunc obj1func1("obj1func1");
    MyFunc obj1func2("obj1func2");
    obj1.subs().add(obj1func1);
    obj1.subs().add(obj1func2);

    Obj obj2;
    MyFunc obj2func1("obj2func1");
    obj2.subs().add(obj2func1);

    obj1func1.setLambda([&obj1, &obj1func1, &obj1func2](auto args, auto sf) {
        if(sf.getLen() != 1) return WRD_E("obj1func1: sf.getLen() != 1"), false;
        if(!checkFrameHasFuncAndObjScope(sf[0], obj1func1, obj1)) return false;

        NArr args;
        args.add(obj1);
        obj1func2.run(args);
        if(sf.getLen() != 1)
            return WRD_E("return of obj1func1: sf.getLen() != 1"), false;
        return true;
    });
    obj1func2.setLambda([&obj2, &obj1func2, &obj1, &obj2func1](auto args, auto sf) {
        if(sf.getLen() != 2) return WRD_E("obj1func2: sf.getLen() != 2"), false;

        if(!checkFrameHasFuncAndObjScope(sf[1], obj1func2, obj1)) return false;

        NArr args;
        args.add(obj2);

        obj2func1.run(args);
        if(sf.getLen() != 2)
            return WRD_E("return of obj1func2: sf.getLen() != 2"), false;
        return true;
    });
    obj2func1.setLambda([&obj2, &obj2func1](auto args, auto sf) {
        if(sf.getLen() != 3) return false;

        if(!checkFrameHasFuncAndObjScope(sf[2], obj2func1, obj2)) return false;
        return true;
    });

    NArr args;
    args.add(obj1);
    obj1func1.run(args);
    ASSERT_TRUE(obj1func1.isSuccess());
}

TEST(FuncFixture, testFuncHasStrParameter) {
    MyFunc func1;
    func1.getTypes().push_back(&TType<Str>::get());
    func1.setLambda([&](auto args, auto sf) {
        const WTypes& types = getTypes();
        if(args.getLen() != types.size() + 1) return false;

        TRef<String>
        for(int n=0; types.size() ;n++) {
            const WType& expectType = *types[n];
            Ref cast = args[n+1].impliAs(expectType);
            if(!cast) return false;

            tray.push_back(cast);
        }

        tray
    });
}
