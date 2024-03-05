#pragma once

#include <regex>

class UniversalMarkdownHandler {
    std::string name;
    std::string openTag;
    std::string closeTag;
    std::string htmlOpenTag;
    std::string htmlCloseTag;

public:
    UniversalMarkdownHandler(std::string name, std::string open, std::string close, std::string htmlOpen, std::string htmlClose);

    std::string GetName() const;

    std::string Handle(const std::string& text);

    std::string GetOpenTagPattern() const;

    std::string GetCloseTagPattern() const;
};
