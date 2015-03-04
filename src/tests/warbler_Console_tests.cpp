#include "gtest/gtest.h"
#include "Console.hpp"

#include <memory>

using namespace warbler;

class ConsoleTest
{
public:
    static void noopCommandHandler(const std::shared_ptr<const std::vector<ConsoleArg>> &args) {};
    static const std::shared_ptr<std::vector<ConsoleArgType>> args;
};

const std::shared_ptr<std::vector<ConsoleArgType>> ConsoleTest::args = std::make_shared<std::vector<ConsoleArgType>>();

TEST(constructor, default_constructor)
{
    ASSERT_NO_THROW(Console c);
}

TEST(methods, registerCommand)
{
    Console c;
    ASSERT_NO_THROW(c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args));
}

TEST(methods, registerCommand_null_func_throws)
{
    Console c;
    ASSERT_ANY_THROW(c.registerCommand("test", nullptr, ConsoleTest::args));
}

TEST(methods, registerCommand_empty_name_throws)
{
    Console c;
    ASSERT_ANY_THROW(c.registerCommand("", ConsoleTest::noopCommandHandler, ConsoleTest::args));
}