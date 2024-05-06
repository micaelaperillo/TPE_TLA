#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

Constant * IntegerConstantSemanticAction(const int value);
Grid * GridSemanticAction(const int width, const int height);
RuleNumber* RuleNumberSemanticAction(const int nAliveToSurvive, const int nAliveToDie, const int nAliveToBeBorn);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
CheckList * CheckListSemanticAction(Check * check, CheckList * next);
Automata * AutomataSemanticAction(RuleNumber * ruleNumber, Grid * grid, CheckList * checks);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);
Check* CheckSemanticAction(const int x,const int y);
#endif
