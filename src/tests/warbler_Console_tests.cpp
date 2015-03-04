#include "gtest/gtest.h"
#include "Console.hpp"

#include <memory>

using namespace warbler;

class ConsoleTest
{
public:
    static void noopCommandHandler(const std::shared_ptr<const std::vector<ConsoleArg>> &args) {};
    static const std::shared_ptr<std::vector<ConsoleArgType>> args0;
    static const std::shared_ptr<std::vector<ConsoleArgType>> args1;
};

const std::shared_ptr<std::vector<ConsoleArgType>> ConsoleTest::args0 = std::make_shared<std::vector<ConsoleArgType>>();
const std::shared_ptr<std::vector<ConsoleArgType>> ConsoleTest::args1 = std::make_shared<std::vector<ConsoleArgType>>(1, ConsoleArgType::STRING);

TEST(constructor, default_constructor)
{
    ASSERT_NO_THROW(Console c);
}

TEST(methods, registerCommand)
{
    Console c;
    ASSERT_NO_THROW(c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0));
}

TEST(methods, registerCommand_null_func_throws)
{
    Console c;
    ASSERT_ANY_THROW(c.registerCommand("test", nullptr, ConsoleTest::args0));
}

TEST(methods, registerCommand_empty_name_throws)
{
    Console c;
    ASSERT_ANY_THROW(c.registerCommand("", ConsoleTest::noopCommandHandler, ConsoleTest::args0));
}

TEST(methods, registerCommand_second_handler_different_signature)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    ASSERT_NO_THROW(c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args1));
}

TEST(methods, registerCommand_second_handler_same_signature_throws)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    ASSERT_ANY_THROW(c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0));
}