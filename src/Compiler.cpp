#include "Compiler.hpp"
#include "ParsingManager.hpp"
#include "SemanticChecker.hpp"
#include "SyntaxChecker.hpp"
#include "Visitors.hpp"
#include "prologParser.h"
#include <filesystem>
#include <format>
#include <fstream>
#include <optional>
#include <util.h>
#include <utility>

namespace Prolog {

void Compiler::genProlog(prologParser& parser) {
    parser.reset();
    auto* programStartCtx = parser.p_text();
    Visitors::ProgramRestoreVisitor progRestoreV;
    Visitors::MarkEmptyTuplesVisitor markEmptyTuplesV;

    markEmptyTuplesV.visit(programStartCtx);

    // progRestoreV.emptyTuples = markEmptyTuplesV.emptyTuples;
    progRestoreV.visit(programStartCtx);
    auto progList = progRestoreV.programStmtList;

    std::filesystem::path outputPath;

    if(m_outputPath.has_value()){
        outputPath = m_outputPath.value();
    } else{
        outputPath = m_targetPath;
        outputPath.replace_extension("").concat("_out.pl");
    }


    std::ofstream outputFile(outputPath);

    if (!outputFile) {
        std::cerr << std::format("ERROR: can't open the file {}\n", outputPath.string());
    }

    for (auto& stmtList : progList) {
        for (auto& stmt : stmtList) {
            outputFile << stmt << " ";
        }
        outputFile << '\n';
    }
}

inline void Compiler::checkSemantics() const {
    SemanticChecker semanticChecker(m_targetPath);
    semanticChecker.checkUniqueBinding();
    semanticChecker.checkFuncInitVariables();
    semanticChecker.checkInvocImpliesDefine();
    semanticChecker.checkVanishingImpliesBinding();
    semanticChecker.checkUniqueFuncDef();
}

void Compiler::compile(const std::filesystem::path& path, const std::optional<std::filesystem::path>& outputPath) {
    m_targetPath = path;
    m_outputPath = outputPath;
    auto parsingManager = ParsingManager(path);

    if(SyntaxChecker(path).checkSyntax() == SyntaxChecker::Status::FAIL){
        std::cerr << "ERROR: Invalid Syntax\n";
        exit(-1);
    }

    checkSemantics();
    genProlog(*parsingManager.pParser);
}

/**************************************************************************/

} // namespace Prolog
