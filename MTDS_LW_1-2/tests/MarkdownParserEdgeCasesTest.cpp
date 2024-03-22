#include "MarkdownParser.h"
#include "gtest/gtest.h"

TEST(MarkdownParserTest, EmptyString) {
    MarkdownParser parser("HTML");
    std::string markdown = "";
    ASSERT_EQ(parser.Parse(markdown), "");
}

TEST(MarkdownParserTest, StringWithoutMarkdown) {
    MarkdownParser parser("HTML");
    std::string markdown = "Just a normal string.";
    ASSERT_EQ(parser.Parse(markdown), "Just a normal string.");
}
