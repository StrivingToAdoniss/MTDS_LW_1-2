#include "MarkdownParser.h"
#include "gtest/gtest.h"

TEST(MarkdownParserTest, BoldTextToHTML) {
    MarkdownParser parser("HTML");
    std::string markdown = "**bold**";
    std::string expectedHtml = "<strong>bold</strong>";
    ASSERT_EQ(parser.Parse(markdown), expectedHtml);
}

TEST(MarkdownParserTest, BoldTextToASCI) {
    MarkdownParser parser("ASCI");
    std::string markdown = "**bold**";
    std::string expectedAscii = "\033[1mbold\033[0m"; // Adjust based on your ASCII representation
    ASSERT_EQ(parser.Parse(markdown), expectedAscii);
}

TEST(MarkdownParserTest, ItalicTextToHTML) {
    MarkdownParser parser("HTML");
    std::string markdown = "_italic_";
    std::string expectedHtml = "<em>italic</em>";
    ASSERT_EQ(parser.Parse(markdown), expectedHtml);
}

TEST(MarkdownParserTest, ItalicTextToASCI) {
    MarkdownParser parser("ASCI");
    std::string markdown = "_italic_";
    std::string expectedAscii = "\033[3mitalic\033[0m"; // Adjust based on your ASCII representation
    ASSERT_EQ(parser.Parse(markdown), expectedAscii);
}

TEST(MarkdownParserTest, MonospacedTextToHTML) {
    MarkdownParser parser("HTML");
    std::string markdown = "`monospace`";
    std::string expectedHtml = "<code>monospace</code>";
    ASSERT_EQ(parser.Parse(markdown), expectedHtml);
}

TEST(MarkdownParserTest, MonospacedTextToASCI) {
    MarkdownParser parser("ASCI");
    std::string markdown = "`monospace`";
    std::string expectedAscii = "\033[7mmonospace\033[0m"; // Adjust based on your ASCII representation
    ASSERT_EQ(parser.Parse(markdown), expectedAscii);
}

TEST(MarkdownParserTest, PreformattedToHTML) {
    MarkdownParser parser("HTML");
    std::string markdown = "```code```";
    std::string expectedHtml = "<pre>code</pre>";
    ASSERT_EQ(parser.ParsePreformatted(markdown), expectedHtml);
}

TEST(MarkdownParserTest, PreformattedToASCI) {
    MarkdownParser parser("ASCI");
    std::string markdown = "```code```";
    std::string expectedAscii = "\033[7mcode\033[27m"; // Adjust based on your ASCII representation
    ASSERT_EQ(parser.ParsePreformatted(markdown), expectedAscii);
}
