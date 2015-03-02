#include "Console.hpp"

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


void Console::registerCommand(const std::string &name, void (*handler)(const std::vector<ConsoleArg> &args), const std::vector<ConsoleArgType> &argTypes)
{
    if (handler == nullptr)
    {
        throw std::exception();
    }
}