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
    
    typedef std::vector<const ConsoleArg> t_consoleArgs;
    typedef std::shared_ptr<t_consoleArgs> t_consoleArgs_ptr;
    typedef std::function<void(t_consoleArgs_ptr)> t_commandHandler;
    typedef std::vector<ConsoleArgType> t_consoleArgTypes;
    typedef std::shared_ptr<t_consoleArgTypes> t_consoleArgTypes_ptr;
    
    struct ConsoleCommand
    {
        ConsoleCommand(t_commandHandler handler, t_consoleArgTypes_ptr argTypes) : handler(handler), argTypes(argTypes)
        {
        }
        
        t_commandHandler handler;
        t_consoleArgTypes_ptr argTypes;
    };
    
    typedef std::vector<const ConsoleCommand> t_commandHandlers;
    typedef std::shared_ptr<t_commandHandlers> t_commandHandlers_ptr;
    typedef std::unordered_map<std::string, t_commandHandlers_ptr> t_commandHandlerMap;
    
    class Console
    {
    public:
        Console();
        Console(Console& rhs);
        virtual ~Console();
    
        void registerCommand(const std::string &name, t_commandHandler, t_consoleArgTypes_ptr argTypes);
        void executeCommand(const std::string command) const;
        
    private:
        t_commandHandlerMap _commandHandlerMap = t_commandHandlerMap();
    };
}