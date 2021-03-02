#pragma once

#include "Stream.hpp"

namespace wrd {

    class ConsoleStream : public Stream {
        WRD_DECL_THIS(ConsoleStream, Stream)

    public:
        //  Stream:
        const char* getName() const override;
        wbool dump(const char* message) override;
    };
}