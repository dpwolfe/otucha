#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

namespace warbler {
    
    enum ConsoleArgType
    {
        STRING,
        INT,
        FLOAT
    };
    
    struct ConsoleArg
    {
        ConsoleArg() : intValue(0), floatValue(0.0) {}
        
        ConsoleArgType type;
        int intValue;
        double floatValue;
        std::string stringValue;
    };
    
    typedef std::vector<const ConsoleArg> t_consoleArgs;
    typedef std::shared_ptr<t_consoleArgs> t_consoleArgs_ptr;
    typedef std::function<void(t_consoleArgs_ptr)> t_commandHandler;
    typedef std::vector<ConsoleArgType> t_consoleArgTypes;
    typedef std::shared_ptr<t_consoleArgTypes> t_consoleArgTypes_ptr;
    
    struct ConsoleCommand
    {
        ConsoleCommand() : handler(nullptr), argTypes(nullptr) {}
        ConsoleCommand(t_commandHandler handler, t_consoleArgTypes_ptr argTypes) : handler(handler), argTypes(argTypes)
        {
        }
        
        t_commandHandler handler;
        t_consoleArgTypes_ptr argTypes;
    };
    
    struct ConsoleCommandSignature
    {
        ConsoleCommandSignature(): argCount(0) {}
        
        std::string name;
        int argCount;
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
        t_commandHandlers_ptr _getHandlersByName(const std::string &name) const;
        ConsoleCommandSignature _getCommandSignature(const std::string &input) const;
        ConsoleCommand _getConsoleCommand(const ConsoleCommandSignature &signature) const;
        t_consoleArgs_ptr _getConsoleArgs(const std::string &input, const ConsoleCommand command) const;
        
        t_commandHandlerMap _commandHandlerMap;
        
        static bool _isNumber(const std::string &input);
        static bool _isInteger(const std::string &input);
    };
}