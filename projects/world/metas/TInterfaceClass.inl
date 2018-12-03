#pragma once

namespace WRD
{
    class Instance;
    template <typename T> class TStrong;

    template <typename T, typename S>
    class TInterfaceClass : public S
    {
    public:
        virtual TStrong<Instance> instance() const;
    };
}
