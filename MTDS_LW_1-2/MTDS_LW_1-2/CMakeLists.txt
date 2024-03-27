cmake_minimum_required(3.27.2)

project(MTDS_LW_1-2 VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(${CMAKE_SOURCE_DIR}/HeaderFiles)

string(TIMESTAMP BUILD_DATE "%Y%m%d")
string(TIMESTAMP BUILD_TIME "%H%M%S")

add_executable(
	MTDS_LW_1-2
	Application.cpp
	FileManager.cpp
    MarkdownParser.cpp
    UniversalMarkdownHandler.cpp

)

# Enable testing with CTest
enable_testing()

# Find Google Test package (provided by Visual Studio)
find_package(GTest REQUIRED)

# Add test executables
add_executable(MarkdownParserConstructorTest Tests/MarkdownParserConstructorTest.cpp)
add_executable(MarkdownParserEdgeCasesTest Tests/MarkdownParserEdgeCasesTest.cpp)
add_executable(MarkdownParserFormattingTest Tests/MarkdownParserFormattingTest.cpp)
add_executable(MarkdownParserIntegrationTest Tests/MarkdownParserIntegrationTest.cpp)

# Link Google Test to the test executable
target_link_libraries(MarkdownParserConstructorTest GTest::GTest GTest::Main)
target_link_libraries(MarkdownParserEdgeCasesTest GTest::GTest GTest::Main)
target_link_libraries(MarkdownParserFormattingTest GTest::GTest GTest::Main)
target_link_libraries(MarkdownParserIntegrationTest GTest::GTest GTest::Main)

# Add test cases
add_test(NAME ConstructorTest COMMAND MarkdownParserConstructorTest)
add_test(NAME EdgeCasesTest COMMAND MarkdownParserEdgeCasesTest)
add_test(NAME FormattingTest COMMAND MarkdownParserFormattingTest)
add_test(NAME IntegrationTest COMMAND MarkdownParserIntegrationTest)