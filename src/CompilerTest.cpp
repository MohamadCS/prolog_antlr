#include "Testing.hpp"
#include "gtest.h"
#include <filesystem>
#include <memory>

TEST(FunctionsWithEmptyStmts, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionsWithEmptyStmts.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}

TEST(FunctionsTuples, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionsTuples.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), true);
}

TEST(FunctionNoBody, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionsNoBody.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}

TEST(FunctionNoArgs, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionsWithNoArgs.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}

TEST(FunctionManyArguments, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionWithManyArguments.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}

TEST(FunctionsWrongVar, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionsWrongVar.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), true);
}

TEST(FunctionsWithLocalStmt, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionsWithLocalStmt.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}

TEST(FunctionsLocalStmt, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/FunctionsWithLocalStmt.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}

TEST(TuplesIssue12, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/TupleIssue12.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}


TEST(TwoBindings, SyntaxTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/Issue15TwoBinding.pl");
    auto syntaxErrorListener = getSyntaxTestListenerPtr(path);
    EXPECT_EQ(syntaxErrorListener->isError(), false);
}

TEST(TwoBindings, SemanticsTest) {
    std::filesystem::path path = std::filesystem::current_path() / ("tests/Issue15TwoBinding.pl");
    SemanticsTest semanticsTest(path);
    auto pFuncV = semanticsTest.getFunctionSemanticsData();

}
