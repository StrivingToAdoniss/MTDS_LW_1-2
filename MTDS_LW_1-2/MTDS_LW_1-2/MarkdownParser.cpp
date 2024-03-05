#include "MarkdownParser.h"

MarkdownParser::MarkdownParser() {
    handlers.push_back(std::make_unique<UniversalMarkdownHandler>("bold", "\\*\\*", "\\*\\*", "<strong>", "</strong>")); // ��� ������� ������
    handlers.push_back(std::make_unique<UniversalMarkdownHandler>("italic", "_", "_", "<em>", "</em>")); // ��� �������
    handlers.push_back(std::make_unique<UniversalMarkdownHandler>("monospaced", "`", "`", "<code>", "</code>")); // ��� ������������� ������
    
}

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() &&
        str.compare(0, prefix.size(), prefix) == 0;
}


void MarkdownParser::ValidateMarkdown(const std::string& markdownText) {
    
    std::vector<std::pair<std::string, std::regex>> patterns;
    for (const auto& handler : handlers) {
        patterns.emplace_back(handler->GetName(), std::regex(handler->GetOpenTagPattern() + "(.*?)" + handler->GetCloseTagPattern()));
    }

    std::map<size_t, std::string> positions; // ������ ������� ���� � �� ����

    for (const auto& pattern : patterns) {
        auto words_begin = std::sregex_iterator(markdownText.begin(), markdownText.end(), pattern.second);
        size_t lastMatchEnd = 0; // ������ ��� ���������� ����������� � ����

        for (std::sregex_iterator i = words_begin; i != std::sregex_iterator(); ++i) {
            std::smatch match = *i;
            size_t matchStart = match.position();
            size_t matchEnd = matchStart + match.length();

            // ��������, �� ����������� �� ������, ��� �������� �����������
            if (matchStart < lastMatchEnd || matchEnd <= lastMatchEnd) {
                continue; // ���������� �� ��������, ���� ���� �� ������� ��� ������
            }
            lastMatchEnd = matchEnd; // ��������� ������� ������� ��������� ����������

            positions[matchStart] = "open_" + pattern.first;
            positions[matchEnd] = "close_" + pattern.first;
        }
    }

    std::string lastOpen;
    for (const auto& pos : positions) {
        if (startsWith(pos.second, "open_")) {
            if (!lastOpen.empty()) {
                throw std::runtime_error("������������ �������� �������: " + lastOpen + " �������� " + pos.second.substr(5));
            }
            lastOpen = pos.second.substr(5);
        }
        else if (startsWith(pos.second, "close_")) {
            if (lastOpen != pos.second.substr(6)) {
                throw std::runtime_error("������������ �������� �������: " + lastOpen + " ����������� ����� " + pos.second.substr(6));
            }
            lastOpen.clear();
        }
    }
    
  


    /*
    for (const auto& handler : handlers) {
        // �������� �������� �������� �� �������� ��� ������� ���������
        auto openPattern = handler->GetOpenTagPattern();
        auto closePattern = handler->GetCloseTagPattern();

        // �������� regex �������, ���� �������� ������� ����
        std::string regexPattern = openPattern + "(.*?)" + closePattern;
        std::regex pattern(regexPattern);

        auto words_begin = std::sregex_iterator(markdownText.begin(), markdownText.end(), pattern);
        auto words_end = std::sregex_iterator();

        int count = std::distance(words_begin, words_end);
        if (count % 2 != 0) { // ���� ������� �������� �� ������� ������� ��������
            throw std::runtime_error("���������� ��� ������� �������� � ������: " + openPattern);
        }
    }
    */
    // ��� ����� ������ �������� ���������� ��������, ���� �������
}

std::string MarkdownParser::ParsePreformatted(const std::string& text) {
    std::regex preformattedPattern(R"(```([\s\S]*?)```)");
    std::string processedText = text;
    std::smatch matches;

    // ��������� ������������� ��� ����� ����� ����
    std::string placeholderPrefix = "PRE_FORMATTED_BLOCK_";
    int counter = 0;
    std::vector<std::string> preformattedBlocks;

    // ������ �� ����� ���������������� ������ �� ������� �� �� ������� ������������
    while (std::regex_search(processedText, matches, preformattedPattern)) {
        std::string placeholder = placeholderPrefix + std::to_string(counter++);
        preformattedBlocks.push_back(matches[1].str());
        processedText = processedText.replace(matches.position(0), matches.length(0), placeholder);
    }

    // ��� ����� �������� ����� �� ��������� ����� ��������� Markdown...

    // ³������� ����� ���������������� ������ �� ���� ������������
    for (int i = 0; i < preformattedBlocks.size(); ++i) {
        std::string placeholder = placeholderPrefix + std::to_string(i);
        std::string toReplace = "<pre>" + preformattedBlocks[i] + "</pre>";
        size_t pos = processedText.find(placeholder);
        if (pos != std::string::npos) {
            processedText.replace(pos, placeholder.length(), toReplace);
        }
    }

    return processedText;
}


std::string MarkdownParser::Parse(const std::string& markdownText) {
    std::string result = markdownText;
    ValidateMarkdown(result);
    //result = ParsePreformatted(result);

    for (auto& handler : handlers) {
        result = handler->Handle(result);
    }
    return result;
}