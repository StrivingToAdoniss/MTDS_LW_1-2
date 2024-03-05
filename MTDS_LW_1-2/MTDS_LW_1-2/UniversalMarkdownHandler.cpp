#include "UniversalMarkdownHandler.h"

UniversalMarkdownHandler::UniversalMarkdownHandler(std::string name, std::string open, std::string close, std::string htmlOpen, std::string htmlClose)
    : name(std::move(name)), openTag(std::move(open)), closeTag(std::move(close)),
    htmlOpenTag(std::move(htmlOpen)), htmlCloseTag(std::move(htmlClose)) {}

std::string UniversalMarkdownHandler::Handle(const std::string& text) {
    std::regex pattern(openTag + "(.+?)" + closeTag);
    std::string replaced = std::regex_replace(text, pattern, htmlOpenTag + "$1" + htmlCloseTag);
    return replaced;
}

std::string UniversalMarkdownHandler::GetName() const {
    return name;
}

std::string UniversalMarkdownHandler::GetOpenTagPattern() const {
    return openTag;
}

std::string UniversalMarkdownHandler ::GetCloseTagPattern() const {
    return closeTag;
}

