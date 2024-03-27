#include "MarkdownParser.h"


MarkdownParser::MarkdownParser() {

}

MarkdownParser::MarkdownParser(std::string _format) {

    setFormat(_format);
    
}

void MarkdownParser::setFormat(std::string _format)
{
    format = _format;
    handlers.clear();

    if (format == "HTML")
    {
        handlers.push_back(std::make_unique<UniversalMarkdownHandler>("bold", "\\*\\*", "\\*\\*", "<strong>", "</strong>")); // для жирного тексту
        handlers.push_back(std::make_unique<UniversalMarkdownHandler>("italic", "_", "_", "<em>", "</em>")); // для курсиву
        handlers.push_back(std::make_unique<UniversalMarkdownHandler>("monospaced", "`", "`", "<code>", "</code>")); // для моноширинного тексту
    }
    else if (format == "ASCI")
    {
        handlers.push_back(std::make_unique<UniversalMarkdownHandler>("bold", "\\*\\*", "\\*\\*", "\033[1m", "\033[0m")); // для жирного тексту
        handlers.push_back(std::make_unique<UniversalMarkdownHandler>("italic", "_", "_", "\033[3m", "\033[0m")); // для курсиву
        handlers.push_back(std::make_unique<UniversalMarkdownHandler>("monospaced", "`", "`", "\033[7m", "\033[0m")); // для моноширинного тексту
    }

}

std::string MarkdownParser::getFormat()
{
    return format;
}


bool startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() &&
        str.compare(0, prefix.size(), prefix) == 0;
}


void MarkdownParser::ValidateMarkdown(const std::string& markdownText) {
   

    // Передбачається, що handlers — це колекція обробників розмітки

    std::vector<std::pair<std::string, std::regex>> patterns;
    for (const auto& handler : handlers) {
        
        patterns.emplace_back(handler->GetName(), std::regex(handler->GetOpenTagPattern() + "(.*?)" + handler->GetCloseTagPattern()));
    }

    std::map<size_t, std::string> positions; // Зберігає позиції тегів і їх типи
    std::vector<std::pair<std::string, size_t>> tagsVector; // Вектор для відстеження відкритих тегів

    // Збір позицій відкриття та закриття тегів
    for (const auto& pattern : patterns) {
        auto words_begin = std::sregex_iterator(markdownText.begin(), markdownText.end(), pattern.second);
        size_t lastMatchEnd = 0;

        for (std::sregex_iterator i = words_begin; i != std::sregex_iterator(); ++i) {
            std::smatch match = *i;
            size_t matchStart = match.position();
            size_t matchEnd = matchStart + match.length();

            if (matchStart < lastMatchEnd || matchEnd <= lastMatchEnd) {
                continue;
            }
            lastMatchEnd = matchEnd;

            positions[matchStart] = "open_" + pattern.first;
            positions[matchEnd] = "close_" + pattern.first;

            //std::cout << "Correspondence found: " << pattern.first << " from " << matchStart << " to " << matchEnd << std::endl;
        }
    }

    std::string lastOpenTag;
    for (const auto& pos : positions) {
        //std::cout << "Position processing: " << pos.first << ", type: " << pos.second << std::endl;

        if (startsWith(pos.second, "open_")) {
            if (!lastOpenTag.empty()) {
                //std::cout << "Invalid nested markup: " << lastOpenTag << " inside of " << pos.second.substr(5) << std::endl;
                throw std::runtime_error("Invalid nested markup: " + lastOpenTag + " inside of " + pos.second.substr(5));
            }
            lastOpenTag = pos.second.substr(5);
            tagsVector.push_back({ lastOpenTag, pos.first }); // Додаємо відкриття тегу до вектора
            //std::cout << "Added to open tag vector " << lastOpenTag << std::endl;
        }
        else if (startsWith(pos.second, "close_")) {
            if (tagsVector.empty() || tagsVector.back().first != pos.second.substr(6)) {
               //std::cout << "Markup does not match: open tag " << (tagsVector.empty() ? "missing" : tagsVector.back().first) << ", but an attempt to close " << pos.second.substr(6) << std::endl;
                throw std::runtime_error("Markup Mismatch: An open tag does not match a closed tag " + pos.second.substr(6));
            }
            tagsVector.pop_back(); // Видаляємо останній відкритий тег, якщо він відповідає закритому
            //std::cout << "The last open tag has been deleted from the vector" << std::endl;
            lastOpenTag.clear(); // Очищаємо lastOpenTag після закриття тегу
        }
    }


}

std::string MarkdownParser::ParsePreformatted(const std::string& text) {
    std::regex preformattedPattern(R"(```([\s\S]*?)```)");
    std::string processedText = text;
    std::smatch matches;

    // Унікальний ідентифікатор для заміни блоків коду
    std::string placeholderPrefix = "PRE_FORMATTED_BLOCK_";
    int counter = 0;
    std::vector<std::string> preformattedBlocks;

    // Знайти всі блоки преформатованого тексту та замінити їх на унікальні плейсхолдери
    while (std::regex_search(processedText, matches, preformattedPattern)) {
        std::string placeholder = placeholderPrefix + std::to_string(counter++);
        preformattedBlocks.push_back(matches[1].str());
        processedText = processedText.replace(matches.position(0), matches.length(0), placeholder);
    }

    // Тут можна обробити текст за допомогою інших обробників Markdown...

    // Відновити блоки преформатованого тексту на місце плейсхолдерів
    for (int i = 0; i < preformattedBlocks.size(); ++i) {
        std::string placeholder = placeholderPrefix + std::to_string(i);
        
        std::string toReplace;
        if (format == "ASCI") 
        {
            toReplace = "\033[7m" + preformattedBlocks[i] + "\033[27m";
        }
        else if(format == "HTML")
        {
            toReplace = "<pre>" + preformattedBlocks[i] + "</pre>";
        }

        size_t pos = processedText.find(placeholder);
        if (pos != std::string::npos) {
            processedText.replace(pos, placeholder.length(), toReplace);
        }
    }

    return processedText;
}


std::string MarkdownParser::Parse(const std::string& markdownText) {
    std::string result = markdownText;
    result = ParsePreformatted(result);
    ValidateMarkdown(result);


    for (auto& handler : handlers) {
        result = handler->Handle(result);
    }
    return result;
}