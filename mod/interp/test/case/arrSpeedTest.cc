#include "../common/dep.hpp"
#include <functional>
#include <chrono>

using namespace wrd;
using namespace std;

namespace  {
    void benchMark(string name, int cnt, function<void(void)> func) {
        logger::get().setEnable(false);

        auto start = chrono::steady_clock::now();
        for(int n=0; n < cnt; n++)
            func();
        auto end = chrono::steady_clock::now();
        auto totalElapsed = end - start;

        logger::get().setEnable(true);
        WRD_I("[%s]: it took total %d ms.", name.c_str(), totalElapsed / chrono::milliseconds(1));
        logger::get().setEnable(false);
    }

    struct myObj : public mgdObj {
        WRD_CLASS(myObj, mgdObj)

    public:
        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }
    };
}

TEST(arrSpeedTest, testBenchmark) {
    int clc = 0;
    myObj obj1;
    benchMark("create narr 10000 times", 10000, [&clc]() {
        narr ar;
        clc += ((int64_t) &ar) % 2;
    });
    benchMark("create arr 10000 times", 10000, [&clc]() {
        arr ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("create vector 10000 times", 10000, [&clc]() {
        vector<node> ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("create obj 10000 times", 10000, [&clc]() {
        myObj ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("create nchain 10000 times", 10000, [&clc]() {
        nchain ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("add narr 10000 times", 10000, [&]() {
        narr ar;
        ar.add(obj1);
        clc += ((int64_t) &ar) % 2;
    });
    benchMark("add arr 10000 times", 10000, [&]() {
        arr ar;
        ar.add(obj1);
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("add vector 10000 times", 10000, [&]() {
        vector<str> ar;
        ar.push_back(str(obj1));
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("add nchain 10000 times", 10000, [&]() {
        nchain ar;
        ar.add(obj1);
        clc += ((int64_t) &ar) % 2;
    });
}
