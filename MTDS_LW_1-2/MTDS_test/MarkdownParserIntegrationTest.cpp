#include "pch.h"
#include "MarkdownParser.h"
#include "gtest/gtest.h"

TEST(MarkdownParserTest, MixedMarkdownToHTML) {
    MarkdownParser parser("HTML");
    std::string markdown = "**bold** _italic_ `code`";
    std::string expectedHtml = "<strong>bold</strong> <em>italic</em> <code>code</code>";
    ASSERT_EQ(parser.Parse(markdown), expectedHtml);
}

TEST(MarkdownParserTest, MixedMarkdownToASCI) {
    MarkdownParser parser("ASCI");
    std::string markdown = "**bold** _italic_ `code`";
    std::string expectedAscii = "\033[1mbold\033[0m \033[3mitalic\033[0m \033[7mcode\033[0m"; // Adjust based on your ASCII representation
    ASSERT_EQ(parser.Parse(markdown), expectedAscii);
}
