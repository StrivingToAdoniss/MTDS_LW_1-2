#pragma once

#include "UniversalMarkdownHandler.h"
#include <vector>
#include <memory>
#include <regex>
#include <string>
#include <iostream>
#include <map>
#include <stdexcept>

class MarkdownParser {
    std::vector<std::unique_ptr<UniversalMarkdownHandler>> handlers;
    std::string ParsePreformatted(const std::string& text);
    void ValidateMarkdown(const std::string& markdownText);
public:
    MarkdownParser();
    std::string Parse(const std::string& markdownText);


};
