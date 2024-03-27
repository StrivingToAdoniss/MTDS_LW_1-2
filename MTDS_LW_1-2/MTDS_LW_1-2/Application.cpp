#include "Application.h"
#include <iostream>
#include <windows.h>
#include "gtest/gtest.h"



Application::Application() {}

void Application::Run(int argc, char* argv[]) {
    std::string inputFilePath;
    std::string outputFilePath;

    if (argc < 2) {
        std::cerr << "Using: " << argv[0] << " <input file> [--out <output file>]\n";
        exit(EXIT_FAILURE);
    }

    inputFilePath = argv[1];

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.substr(0, 9) == "--format=") {
            std::string format = arg.substr(9);
            if (format != "HTML" && format != "ASCI") {
                std::cerr << "Unknown format: " << format << ". Use 'HTML' or 'ASCI'.\n";
                exit(EXIT_FAILURE);
            }
            else
            {
                parser.setFormat(format);
            }
        }

        else if (arg == "--out") {
            if (i + 1 < argc) {
                outputFilePath = argv[++i];
            }
            else {
                std::cerr << "The --out argument requires the path to the output file.\n";
                exit(EXIT_FAILURE);
            }
        }
       
    }

    try {
        std::string markdownText = FileManager::ReadFile(inputFilePath);
        std::string htmlContent = parser.Parse(markdownText);
        if (outputFilePath.empty()) {
            std::cout << htmlContent;
        }
        else {
            FileManager::WriteFile(outputFilePath, htmlContent);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    std::locale::global(std::locale(""));
    //::testing::InitGoogleTest(&argc, argv);
    //RUN_ALL_TESTS();
    Application app;
    app.Run(argc, argv);
    return 0;
}