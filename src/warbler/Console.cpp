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
}

Console::~Console()
{
}

void Console::registerCommand(const std::string &name, t_commandHandler handler, t_consoleArgTypes_ptr argTypes)
{
    // pre-conditions
    if (name.length() == 0)
    {
        throw std::exception();
    }
    
    if (handler == nullptr)
    {
        throw std::exception();
    }
    
    // get or create handler vector for command name
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
    
    // check to make sure a handler with same number of args does not exist
    for (auto it = handlers->begin(); it != handlers->end(); ++it)
    {
        if (it->argTypes->size() == argTypes->size()) {
            throw std::exception();
        }
    }
    
    // add the command
    auto command = ConsoleCommand(handler, argTypes);
    handlers->push_back(command);
}

void Console::executeCommand(const std::string command) const
{
    // pre-conditions
    if (command.length() == 0)
    {
        throw std::exception();
    }
    
    std::stringstream commandStream(command);
    std::string name;
    commandStream >> name;
    
    // get handlers for given name
    if (_commandHandlerMap.count(name) == 0)
    {
        throw std::exception();
    }
    t_commandHandlers_ptr handlers = _commandHandlerMap.find(name)->second;
    
    // count arguments
    std::string arg;
    int argCount = 0;
    while (!commandStream.eof())
    {
        argCount++;
        commandStream >> arg;
    }
    
    // get handler matching param count
    t_commandHandler handler;
    t_consoleArgTypes_ptr argTypes;
    for (auto it = handlers->begin(); it != handlers->end(); ++it)
    {
        if (it->argTypes->size() == argCount)
        {
            handler = it->handler;
            argTypes = it->argTypes;
        }
    }
    if (handler == nullptr)
    {
        throw std::exception();
    }
    
    // build up arg vector to pass to handler
    std::stringstream argStream(command);
    //std::string arg;
    argStream >> arg; // skip command name
    t_consoleArgs_ptr args = std::make_shared<t_consoleArgs>();
    auto argTypeIt = argTypes->begin();
    while (!argStream.eof())
    {
        if (argTypes->end() == argTypeIt)
        {
            throw std::exception();
        }
        
        ConsoleArg consoleArg;
        consoleArg.type = *argTypeIt;
        argStream >> consoleArg.stringValue;
        if (consoleArg.type == ConsoleArgType::FLOAT)
        {
            if (!Console::_isNumber(consoleArg.stringValue))
            {
                throw std::ex   ception();
            }
            consoleArg.floatValue = std::stof(consoleArg.stringValue);
        }
        else if (consoleArg.type == ConsoleArgType::INT)
        {
            if (!Console::_isInteger(consoleArg.stringValue))
            {
                throw std::exception();
            }
            consoleArg.intValue = std::stoi(consoleArg.stringValue);
        }
        args->push_back(consoleArg);
        ++argTypeIt;
    }
    
    // execute handler
    handler(args);
}

bool Console::_isInteger(const std::string &input)
{
    return std::regex_match(input, std::regex("[(-|+)|][0-9]+"));
}

bool Console::_isNumber(const std::string &input)
{
    return std::regex_match(input, std::regex("[(-|+)|][0-9]+(\\.[0-9]+)?"));
}