#include "Compiler.hpp"
#include "BaseErrorListener.h"
#include "Utils.hpp"
#include "gtest.h"
#include "prologLexer.h"
#include "prologParser.h"
#include <filesystem>
#include <memory>

class SyntaxErrorListener : public antlr4::BaseErrorListener {
public:
    bool isError() const {
        return m_syntaxError;
    }

private:
    bool m_syntaxError = false;
    void syntaxError(antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string& msg, std::exception_ptr e) override {
        m_syntaxError = true;
    };
};

class SemanticsTest {};

static std::unique_ptr<SyntaxErrorListener> getSyntaxTestListenerPtr(const std::filesystem::path& path) {
    antlr4::ANTLRInputStream input;
    std::ifstream targetFile{path};
    if (!targetFile) {
        std::cerr << std::format("Error opening the file: {}\n", path.string());
    }
    input.load(targetFile);

    prologLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    prologParser parser(&tokens);

    auto syntaxErrorListener = std::make_unique<SyntaxErrorListener>();
    parser.removeErrorListeners();

    parser.addErrorListener(syntaxErrorListener.get());
    parser.p_text();

    return syntaxErrorListener;
}

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