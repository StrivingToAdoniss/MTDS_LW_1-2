#pragma once

#include "MarkdownParser.h"
#include "FileManager.h"

class Application {
    MarkdownParser parser;
public:
    Application();
    void Run(int argc, char* argv[]);
};