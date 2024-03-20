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
    std::string format;
    void ValidateMarkdown(const std::string& markdownText);
public:
    MarkdownParser();
    MarkdownParser(std::string _format);
    std::string Parse(const std::string& markdownText);
    std::string ParsePreformatted(const std::string& text);
    void setFormat(std::string _format);
    std::string getFormat();

    void ParseToANSI(const std::string& markdownText);

};
