#pragma once

#include <logger.hpp>
#include "../TestCase.hpp"
#include "../Initiator.hpp"

namespace NE
{
    struct LoggerTest : public TestCase {
        virtual const char* getName() const { return "LoggerTest"; }
        virtual std::string _onTest() {
            Logger& logger = Logger::getInstance();
            
            WRD_TEST(logger.getName() != string("Logger"))
            WRD_TEST(logger.getStreamCount() < 2)
            WRD_TEST( ! &logger["ConsoleStream"])
            WRD_TEST( ! &logger["FileLogStream"])

            WRD_DUMP("D", "hello!")
            WRD_WARN("world!")
            WRD_ERROR("this is not error. paradox?")

            class MyStream : public Stream {
            public:
                virtual const char* getName() const { return "MyStream"; }
                virtual type_bool dump(const char* message) {
                    msg += message;
                    return false;
                }
                std::string msg;
            };
            MyStream* cs = new MyStream();
            WRD_TEST(logger.pushStream(cs));
            WRD_TEST(logger.getStreamCount() < 3)
            WRD_TEST( ! &logger["MyStream"])

            WRD_TEST(logger.dump("hello world"))
            WRD_TEST(cs->msg != "hello world")

            WRD_DUMP("D", "hello!")
            WRD_WARN("world!")
            WRD_ERROR("this is not error. paradox?")


            type_bool found = false;
            Folder build(".", Folder::Option(false));            
            while( found || ! build.next().isNull())
                if(build.peek().getName().find("logs"))
                    found = true;

            WRD_TEST(found)
            WRD_TEST(logger.dump("let's go on 2nd phase."));

            BuildFeatures::Date date;
            WRD_INFO("today is %d-%d %d. %s.", date.getMonth(), date.getDay(), date.getYear(), "Nice start!")
            WRD_WARN("Fatal error! Fatal error! this PC should be infected to a virus immediatly!!!")
            WRD_ERROR("***backstabbing*** It's a joke. Carm down, my master.")

            //WRD_TEST(logger.release()) -> can't call.            

            return "";
        }
    };

    INITIATE_CLASS(LoggerTest)
}