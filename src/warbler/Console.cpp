#include "Console.hpp"

#include <utility>
#include <sstream>

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


void Console::registerCommand(const std::string &name, t_commandHandler handler, const std::shared_ptr<const std::vector<ConsoleArgType>> &argTypes)
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
    
    // get handler
    if (_commandHandlerMap.count(name) == 0)
    {
        throw std::exception();
    }
    
    t_commandHandlers_ptr handler = _commandHandlerMap.find(name)->second;
}