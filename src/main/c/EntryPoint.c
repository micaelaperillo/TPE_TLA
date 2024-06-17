#include "backend/code-generation/Generator.h"
#include "backend/domain-specific/Program.h"
#include "backend/domain-specific/Rule.h"
#include "frontend/lexical-analysis/FlexActions.h"
#include "frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "frontend/syntactic-analysis/BisonActions.h"
#include "frontend/syntactic-analysis/SyntacticAnalyzer.h"
#include "shared/CompilerState.h"
#include "shared/Environment.h"
#include "shared/Logger.h"
#include "shared/String.h"

/**
 * The main entry-point of the entire application.
 */
const int main(const int count, const char ** arguments) {
	Logger * logger = createLogger("EntryPoint");
	initializeFlexActionsModule();
	initializeBisonActionsModule();
	initializeSyntacticAnalyzerModule();
	initializeAbstractSyntaxTreeModule();
	initializeAutomataModule();
    initializeRuleModule();
	initializeGeneratorModule();

	// Logs the arguments of the application.
	for (int k = 0; k < count; ++k) {
		logDebugging(logger, "Argument %d: \"%s\"", k, arguments[k]);
	}

	// Begin compilation process.
	CompilerState compilerState = {
		.abstractSyntaxtTree = NULL,
		.succeed = false,
		.value = 0
	};
	const SyntacticAnalysisStatus syntacticAnalysisStatus = parse(&compilerState);
	CompilationStatus compilationStatus = SUCCEED;
	if (syntacticAnalysisStatus == ACCEPT) {
		logDebugging(logger, "Computing expression value...");
		Program * program = compilerState.abstractSyntaxtTree;
        ProgramResult automataResult = computeAutomata(program->automata); //TODO se podria mergear automata y rule en un mismo check
        RuleResult ruleResult = computeRule(program->rule);
        if (automataResult.succeed && ruleResult.succeed) {
            compilerState.value = 0; //TODO hacerlo dinamico a partir de los valores de rule y automata
            generate(&compilerState);
        }
        else {
            logError(logger, "Todo roto"); //TODO hacer que el error dependa de lo que devolvio automata o rule
            compilationStatus = FAILED;
        }
		logDebugging(logger, "Releasing AST resources...");
		releaseProgram(program);
	}
	else {
		logError(logger, "The syntactic-analysis phase rejects the input program.");
		compilationStatus = FAILED;
	}

	logDebugging(logger, "Releasing modules resources...");
	shutdownGeneratorModule();
	shutdownAutomataModule();
    shutdownRuleModule();
	shutdownAbstractSyntaxTreeModule();
	shutdownSyntacticAnalyzerModule();
	shutdownBisonActionsModule();
	shutdownFlexActionsModule();
	logDebugging(logger, "Compilation is done.");
	destroyLogger(logger);
	return compilationStatus;
}
