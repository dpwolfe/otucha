#include "Console.hpp"

#include <utility>
#include <sstream>
#include <regex>

using namespace warbler;

Console::Console()
{
}

Console::Console(Console& rhs)
{
    _commandHandlerMap = rhs._commandHandlerMap;
}

Console::~Console()
{
}

void Console::registerCommand(const std::wstring &name, t_commandHandler handler, t_consoleArgTypes_ptr argTypes)
{
    // pre-conditions
    if (name.length() == 0) { throw std::exception(); }
    if (handler == nullptr) { throw std::exception(); }
    
	auto handlers = _getOrCreateHandlerVector(name);
	_validateHandlerIsUnique(handlers, argTypes->size());
    handlers->push_back(ConsoleCommand(handler, argTypes));
}

t_commandHandlers_ptr Console::_getOrCreateHandlerVector(const std::wstring &name)
{
	t_commandHandlers_ptr handlers;
	if (_commandHandlerMap.count(name) != 0)
	{
		handlers = _commandHandlerMap.find(name)->second;
	}
	else
	{
		handlers = std::make_shared<t_commandHandlers>();
		_commandHandlerMap.insert(std::make_pair(name, handlers));
	}
	return handlers;
}

void Console::_validateHandlerIsUnique(t_commandHandlers_ptr handlers, int argCount)
{
    for (auto it = handlers->begin(); it != handlers->end(); ++it)
    {
        if (it->argTypes->size() == argCount) {
            throw std::exception();
        }
    }
}

void Console::executeCommand(const std::wstring input) const
{
    if (input.length() == 0) { throw std::exception(); }
    
    auto signature = _getCommandSignature(input);
    ConsoleCommand command = _getConsoleCommand(signature);
    t_consoleArgs_ptr args = _getConsoleArgs(input, command);
    command.handler(args);
}

t_commandHandlers_ptr Console::_getHandlersByName(const std::wstring &name) const
{
    if (_commandHandlerMap.count(name) == 0) { throw std::exception(); }
    return _commandHandlerMap.find(name)->second;
}

ConsoleCommandSignature Console::_getCommandSignature(const std::wstring &input) const
{
    ConsoleCommandSignature signature;
    std::wstringstream commandStream(input);
    
    commandStream >> signature.name;
    
    // count arguments
    std::wstring arg;
    while (!commandStream.eof())
    {
        signature.argCount++;
        commandStream >> arg;
    }
    
    return signature;
}

ConsoleCommand Console::_getConsoleCommand(const ConsoleCommandSignature &signature) const
{
    ConsoleCommand command;
    t_commandHandlers_ptr handlers = _getHandlersByName(signature.name);
    t_consoleArgTypes_ptr argTypes;
    for (auto it = handlers->begin(); it != handlers->end(); ++it)
    {
        if (it->argTypes->size() == signature.argCount)
        {
            command = *it;
        }
    }
    
    if (command.handler == nullptr || command.argTypes == nullptr)
    {
        throw std::exception();
    }
    
    return command;
}

t_consoleArgs_ptr Console::_getConsoleArgs(const std::wstring &input, const ConsoleCommand command) const
{
	t_consoleArgs_ptr args = std::make_shared<t_consoleArgs>();
    std::wstringstream argStream(input);
    std::wstring arg;
    argStream >> arg; // skip command name
    auto argTypeIt = command.argTypes->begin();
    while (!argStream.eof())
    {
        ConsoleArg consoleArg;
        consoleArg.type = *argTypeIt;
        argStream >> consoleArg.stringValue;
        if (consoleArg.type == ConsoleArgType::FLOAT)
        {
            consoleArg.floatValue = std::stod(consoleArg.stringValue);
        }
        else if (consoleArg.type == ConsoleArgType::INT)
        {
            consoleArg.intValue = std::stoi(consoleArg.stringValue);
        }
        args->push_back(consoleArg);
        ++argTypeIt;
    }
    return args;
}
