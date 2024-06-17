#include "backend/code-generation/Generator.h"
#include "backend/domain-specific/Program.h"
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
        ProgramResult programResult = computeProgram(program);
        if (programResult.succeed) {
            compilerState.value = 0;
            generate(&compilerState);
        }
        else {
            char * msg;
            switch(programResult.value) {
                case INVALID_AUTOMATA_NUMBERS:
                    msg = "INVALID_AUTOMATA_NUMBERS : the automata definition numbers are invalid.";
                    break;
                case INVALID_PARAMETER_TYPE:
                    msg = "INVALID_PARAMETER_TYPE : a property is receiving invalid parameter types.";
                    break;
                case INVALID_PARAMETER_AMOUNT:
                    msg = "INVALID_PARAMETER_AMOUNT : a property is receiving the wrong number of parameters.";
                    break;
                case ILLEGAL_CHECK:
                    msg = "ILLEGAL_CHECK : there is an out-of-bound check.";
                    break;
                case INVALID_GRID:
                    msg = "INVALID_GRID : the grid number is invalid.";
                    break;
                case INVALID_PROPERTY:
                    msg = "INVALID_PROPERTY : a specified property does not exist.";
                    break;
                case UNSPECIFIED_ERROR:
                    msg = "UNSPECIFIED_ERROR : todo roto.";
                    break;
                default:
                    msg = "";
                    break;
            }
            logError(logger, msg);
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
	shutdownAbstractSyntaxTreeModule();
	shutdownSyntacticAnalyzerModule();
	shutdownBisonActionsModule();
	shutdownFlexActionsModule();
	logDebugging(logger, "Compilation is done.");
	destroyLogger(logger);
	return compilationStatus;
}
