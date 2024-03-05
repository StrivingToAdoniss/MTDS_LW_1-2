#pragma once

#include <string>

class FileManager {
public:
    static std::string ReadFile(const std::string& filePath);
    static void WriteFile(const std::string& filePath, const std::string& content);
};