#include "UniversalMarkdownHandler.h"

UniversalMarkdownHandler::UniversalMarkdownHandler(std::string name, std::string open, std::string close, std::string htmlOpen, std::string htmlClose)
    : name(std::move(name)), openTag(std::move(open)), closeTag(std::move(close)),
    htmlOpenTag(std::move(htmlOpen)), htmlCloseTag(std::move(htmlClose)) {}

std::string UniversalMarkdownHandler::Handle(const std::string& text) {
    // Шаблон для знаходження правильно сформованої розмітки
    std::regex fullPattern(openTag + "(.+?)" + closeTag);
    std::string replaced = std::regex_replace(text, fullPattern, htmlOpenTag + "$1" + htmlCloseTag);

    // Шаблон для знаходження незакритих тегів
    std::regex openTagPattern(openTag + "([^" + closeTag + "]+)$");
    std::smatch matches;
    std::string result = replaced;

    // Пошук та обробка незакритих тегів
    std::string::const_iterator searchStart(replaced.cbegin());
    while (std::regex_search(searchStart, replaced.cend(), matches, openTagPattern)) {
        std::string unmatched = matches[0];
        // Викидання помилки з інформацією про незакритий тег
        throw std::runtime_error("Unclosed tag: " + unmatched + " at position " + std::to_string(matches.position(0)));
    }

    return result;
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

