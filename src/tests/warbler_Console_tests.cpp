#include "gtest/gtest.h"
#include "Console.hpp"

#include <memory>

using namespace warbler;

class ConsoleTest
{
public:
    static void noopCommandHandler(const t_consoleArgs_ptr args) {};
    static const t_consoleArgTypes_ptr args0;
    static const t_consoleArgTypes_ptr args1;
    static const t_consoleArgTypes_ptr args1i;
    static const t_consoleArgTypes_ptr args1f;
};

const t_consoleArgTypes_ptr ConsoleTest::args0 = std::make_shared<t_consoleArgTypes>();
const t_consoleArgTypes_ptr ConsoleTest::args1 = std::make_shared<t_consoleArgTypes>(1, ConsoleArgType::STRING);
const t_consoleArgTypes_ptr ConsoleTest::args1i = std::make_shared<t_consoleArgTypes>(1, ConsoleArgType::INT);
const t_consoleArgTypes_ptr ConsoleTest::args1f = std::make_shared<t_consoleArgTypes>(1, ConsoleArgType::FLOAT);

TEST(constructor, default_constructor)
{
    Console c;
}

TEST(registerCommand, valid_inputs)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
}

TEST(registerCommand, null_handler_throws)
{
    Console c;
    ASSERT_ANY_THROW(c.registerCommand("test", nullptr, ConsoleTest::args0));
}

TEST(registerCommand, empty_name_throws)
{
    Console c;
    ASSERT_ANY_THROW(c.registerCommand("", ConsoleTest::noopCommandHandler, ConsoleTest::args0));
}

TEST(registerCommand, second_handler_different_signature)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args1);
}

TEST(registerCommand, second_handler_same_signature_throws)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    ASSERT_ANY_THROW(c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0));
}

TEST(registerCommand, third_handler_same_signature_as_first_throws)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args1);
    ASSERT_ANY_THROW(c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0));
}

TEST(registerCommand, second_handler_same_signature_but_different_name)
{
    Console c;
    c.registerCommand("test1", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    c.registerCommand("test2", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
}

TEST(executeCommand, throws_when_no_command_found)
{
    Console c;
    ASSERT_ANY_THROW(c.executeCommand("test"));
}

TEST(executeCommand, throws_when_given_empty_string)
{
    Console c;
    ASSERT_ANY_THROW(c.executeCommand(""));
}

TEST(executeCommand, throws_when_no_command_matching_parameter_count_found)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    ASSERT_ANY_THROW(c.executeCommand("test arg1"));
}

TEST(executeCommand, finds_command_with_matching_parameter_count_0params)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args0);
    c.executeCommand("test");
}

TEST(executeCommand, finds_command_with_matching_parameter_count_1param)
{
    Console c;
    c.registerCommand("test", ConsoleTest::noopCommandHandler, ConsoleTest::args1);
    c.executeCommand("test arg1");
}

TEST(executeCommand, executes)
{
    Console c;
    bool success = false;
    c.registerCommand("test", [&] (t_consoleArgs_ptr args) { success = true; }, ConsoleTest::args0);
    c.executeCommand("test");
    ASSERT_TRUE(success);
}

TEST(executeCommand, executes_with_string_arg)
{
    Console c;
    bool success = false;
    c.registerCommand("test", [&] (t_consoleArgs_ptr args) { if ((*args)[0].stringValue == "arg") { success = true; }}, ConsoleTest::args1);
    c.executeCommand("test arg");
    ASSERT_TRUE(success);
}

TEST(executeCommand, executes_with_int_arg)
{
    Console c;
    bool success = false;
    c.registerCommand("test", [&] (t_consoleArgs_ptr args) { if ((*args)[0].intValue == 1) { success = true; }}, ConsoleTest::args1i);
    c.executeCommand("test 1");
    ASSERT_TRUE(success);
}

TEST(executeCommand, executes_with_float_arg)
{
    Console c;
    bool success = false;
    c.registerCommand("test", [&] (t_consoleArgs_ptr args) {
        auto floatValue = (*args)[0].floatValue;
        if (floatValue <= std::nextafter(1.1, 2.0) && floatValue >= std::nextafter(1.1, 1.0)) { success = true; }
    }, ConsoleTest::args1f);
    c.executeCommand("test 1.1");
    ASSERT_TRUE(success);
}

TEST(executeCommand, cannot_parse_int)
{
    Console c;
    bool success = true;
    c.registerCommand("test", [&] (t_consoleArgs_ptr args) { success = false; }, ConsoleTest::args1i);
    ASSERT_ANY_THROW(c.executeCommand("test x"));
    ASSERT_TRUE(success);
}

TEST(executeCommand, cannot_parse_float)
{
    Console c;
    bool success = true;
    c.registerCommand("test", [&] (t_consoleArgs_ptr args) { success = false; }, ConsoleTest::args1f);
    ASSERT_ANY_THROW(c.executeCommand("test y"));
    ASSERT_TRUE(success);
}