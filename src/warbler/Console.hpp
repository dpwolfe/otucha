#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

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
    
    typedef void (*commandHandlerType)(const std::shared_ptr<const std::vector<ConsoleArg>> &args);
    typedef std::unordered_map<std::string, const std::shared_ptr<std::vector<commandHandlerType>>> commandHandlerMapType;
    
    class Console
    {
    public:
        Console();
        Console(Console& rhs);
        virtual ~Console();
    
        void registerCommand(const std::string &name, commandHandlerType, const std::shared_ptr<const std::vector<ConsoleArgType>> &argTypes);
        
    private:
        commandHandlerMapType _commandHandlerMap = commandHandlerMapType();
    };
}