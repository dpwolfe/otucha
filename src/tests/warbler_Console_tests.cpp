#include "gtest/gtest.h"
#include "Console.hpp"

#include <memory>

using namespace warbler;

TEST(constructor, default_constructor) {
    Console c;
}

TEST(methods, registerCommand) {
    Console c;
    auto func = [] (const std::vector<ConsoleArg> &args) { };
    std::vector<ConsoleArgType> args;
    c.registerCommand("test", func, args);
}
