#pragma once

#include <string>
#include <vector>

namespace warbler {
    enum ConsoleArgType
    {
        STRING,
        INT,
        FLOAT
    };
    
    struct ConsoleArg
    {
        ConsoleArgType type;
        int intValue;
        double doubleValue;
        std::string &stringValue;
    };
    
    class Console
    {
    public:
        Console();
        Console(Console& rhs);
        virtual ~Console();
    
        void registerCommand(const std::string &name, void (*handler)(const std::vector<ConsoleArg> &args), const std::vector<ConsoleArgType> &argTypes);
    };
}