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
} AutomataResult;

typedef AutomataResult (*BinaryOperator)(const int, const int);

AutomataResult computeAutomata(Automata * automata);

AutomataResult computeRuleNumbers(RuleNumber * ruleNumber);

AutomataResult computeGrid(Grid * grid);

AutomataResult computeCheckList(CheckList * checkList);

#endif //AUTOMATA_HEADER
