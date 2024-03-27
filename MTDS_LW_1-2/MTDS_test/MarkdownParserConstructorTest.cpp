#include "pch.h"
#include "MarkdownParser.h"
#include "gtest/gtest.h"

// Test default constructor
TEST(MarkdownParserTest, DefaultConstructor) {
    MarkdownParser parser;
    ASSERT_EQ(parser.getFormat(), ""); // Assuming default constructor sets format to empty
}

// Test parameterized constructor with "HTML"
TEST(MarkdownParserTest, ParameterizedConstructorHTML) {
    MarkdownParser parser("HTML");
    ASSERT_EQ(parser.getFormat(), "HTML");
}

// Test parameterized constructor with "ASCI"
TEST(MarkdownParserTest, ParameterizedConstructorASCI) {
    MarkdownParser parser("ASCI");
    ASSERT_EQ(parser.getFormat(), "ASCI");
}

// Test setFormat() method
TEST(MarkdownParserTest, SetFormat) {
    MarkdownParser parser;
    parser.setFormat("HTML");
    ASSERT_EQ(parser.getFormat(), "HTML");
    parser.setFormat("ASCI");
    ASSERT_EQ(parser.getFormat(), "ASCI");
}
