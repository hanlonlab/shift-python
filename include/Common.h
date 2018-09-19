#pragma once

#include <iostream>
#include <string>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <CoreClient.h>
#include <Exceptions.h>
#include <FIXInitiator.h>


namespace py = pybind11;

class Log {
public:
    enum LogLevel {
        INFO,
        WARN,
        ERRO,
        FATA
    };
    struct LogStruct {
        LogLevel level = WARN;
    };

    Log() {}
    Log(LogLevel type)
    {
        operator<<("[" + getLabel(type) + "] ");
    }
    ~Log()
    {
        if (opened) {
            std::cout << std::endl;
        }
        opened = false;
    }
    template <class T>
    Log& operator<<(const T& msg)
    {
        std::cout << msg;
        opened = true;
        return *this;
    }

private:
    bool opened = false;
    LogStruct LOGCFG;

    inline std::string getLabel(LogLevel type)
    {
        std::string label;
        switch (type) {
        case INFO:
            label = "\033[32;1;1mINFO\033[0m";
            break;
        case WARN:
            label = "\033[36;1;1mWARNING\033[0m";
            break;
        case ERRO:
            label = "\033[33;1;1mERROR\033[0m";
            break;
        case FATA:
            label = "\033[31;1;1mFATAL\033[0m";
            break;
        }
        return label;
    }
};
