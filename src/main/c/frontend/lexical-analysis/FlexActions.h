#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../shared/Environment.h"
#include "../../shared/Logger.h"
#include "../../shared/String.h"
#include "../../shared/Type.h"
#include "../syntactic-analysis/AbstractSyntaxTree.h"
#include "../syntactic-analysis/BisonParser.h"
#include "LexicalAnalyzerContext.h"
#include <stdio.h>
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeFlexActionsModule();

/** Shutdown module's internal state. */
void shutdownFlexActionsModule();

/**
 * Flex lexeme processing actions.
 */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
void EndMultilineCommentLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
void IgnoredLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token IntegerLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);
Token ParenthesisLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

Token UnknownLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void checkLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void openParenthesisLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void closeParenthesisLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void integerLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void ignoredLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void unknownLexemeAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void automataFunctionAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void colonPatternAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void commaPatternAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void semicolonPatternAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void endAutomataFunctionAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void ruleFunctionAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void endRuleFunctionAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void colorSetupAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void colorHandlerAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void bgColorSetupAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void wrappingSetupAction(LexicalAnalyzerContext *lexicalAnalyzerContext);

void truePatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext);
void falsePatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext);

#endif
