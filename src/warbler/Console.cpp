#include "Console.hpp"

#include <utility>

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


void Console::registerCommand(const std::string &name, commandHandlerType handler, const std::shared_ptr<const std::vector<ConsoleArgType>> &argTypes)
{
    if (name.length() == 0)
    {
        throw std::exception();
    }
    
    if (handler == nullptr)
    {
        throw std::exception();
    }
    
    std::shared_ptr<std::vector<commandHandlerType>> handlerVector;
    if (_commandHandlerMap.count(name) != 0)
    {
        handlerVector = _commandHandlerMap.find(name)->second;
    }
    else
    {
        handlerVector = std::make_shared<std::vector<commandHandlerType>>();
        _commandHandlerMap.insert(std::make_pair(name, handlerVector));
    }
    handlerVector->push_back(handler);
}