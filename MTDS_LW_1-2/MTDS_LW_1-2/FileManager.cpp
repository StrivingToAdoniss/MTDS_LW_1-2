#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// Реалізація методу для читання файлу
std::string FileManager::ReadFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

// Реалізація методу для запису у файл
void FileManager::WriteFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filePath);
    }

    file << content;
    file.close();
}
