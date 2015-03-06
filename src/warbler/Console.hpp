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
    
    typedef void (*t_commandHandler)(const std::shared_ptr<const std::vector<ConsoleArg>> &args);
    typedef const std::shared_ptr<const std::vector<ConsoleArgType>> t_argTypes;
    
    struct ConsoleCommand
    {
        ConsoleCommand(t_commandHandler handler, t_argTypes argTypes) : handler(handler), argTypes(argTypes)
        {
        }
        
        t_commandHandler handler;
        t_argTypes argTypes;
    };
    
    typedef std::vector<ConsoleCommand> t_commandHandlers;
    typedef std::shared_ptr<t_commandHandlers> t_commandHandlers_ptr;
    typedef std::unordered_map<std::string, t_commandHandlers_ptr> t_commandHandlerMap;
    
    class Console
    {
    public:
        Console();
        Console(Console& rhs);
        virtual ~Console();
    
        void registerCommand(const std::string &name, t_commandHandler, t_argTypes &argTypes);
        void executeCommand(const std::string command) const;
        
    private:
        t_commandHandlerMap _commandHandlerMap = t_commandHandlerMap();
    };
}