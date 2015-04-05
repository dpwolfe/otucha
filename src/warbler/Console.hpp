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
        std::wstring stringValue;
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
        
        std::wstring name;
        int argCount;
    };
    
    typedef std::vector<const ConsoleCommand> t_commandHandlers;
    typedef std::shared_ptr<t_commandHandlers> t_commandHandlers_ptr;
    typedef std::unordered_map<std::wstring, t_commandHandlers_ptr> t_commandHandlerMap;
    
    class Console
    {
    public:
        Console();
        Console(Console& rhs);
        virtual ~Console();
    
        void registerCommand(const std::wstring &name, t_commandHandler, t_consoleArgTypes_ptr argTypes);
        void executeCommand(const std::wstring command) const;
        
	private:
		t_commandHandlers_ptr _getOrCreateHandlerVector(const std::wstring &name);
		void _validateHandlerIsUnique(t_commandHandlers_ptr handlers, int argCount);
        t_commandHandlers_ptr _getHandlersByName(const std::wstring &name) const;
        ConsoleCommandSignature _getCommandSignature(const std::wstring &input) const;
        ConsoleCommand _getConsoleCommand(const ConsoleCommandSignature &signature) const;
        t_consoleArgs_ptr _getConsoleArgs(const std::wstring &input, const ConsoleCommand command) const;
        
        t_commandHandlerMap _commandHandlerMap;
    };
}