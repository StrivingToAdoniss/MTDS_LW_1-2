#include "pch.h"
#include <iostream>
#include <windows.h>
#include "gtest/gtest.h"



int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}