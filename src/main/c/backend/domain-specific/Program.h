#ifndef AUTOMATA_HEADER
#define AUTOMATA_HEADER

/**
 * We reuse the types from the AST for convenience, but you should separate
 * the layers of the backend and frontend using another group of
 * domain-specific models or DTOs (Data Transfer Objects).
 */
#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include <limits.h>

/** Initialize module's internal state. */
void initializeAutomataModule();

/** Shutdown module's internal state. */
void shutdownAutomataModule();

typedef struct {
    boolean succeed;
    int value;
} ProgramResult;

typedef ProgramResult (*BinaryOperator)(const int, const int);

ProgramResult computeProgram(Program * program);

<<<<<<< HEAD:src/main/c/backend/domain-specific/Program.h
=======
AutomataResult computeRuleNumbers(RuleNumber * ruleNumber);

AutomataResult computeGrid(Grid * grid);

AutomataResult computeCheckList(CheckList * checkList,Grid* grid);
>>>>>>> 4e78f2d3cec2b2e4d77f5c27625630d331426101:src/main/c/backend/domain-specific/Automata.h

#endif //AUTOMATA_HEADER
