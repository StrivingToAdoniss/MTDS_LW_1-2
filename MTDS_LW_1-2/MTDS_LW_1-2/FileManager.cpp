#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// ��������� ������ ��� ������� �����
std::string FileManager::ReadFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� �������: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

// ��������� ������ ��� ������ � ����
void FileManager::WriteFile(const std::string& filePath, const std::string& content) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������: " + filePath);
    }

    file << content;
    file.close();
}
