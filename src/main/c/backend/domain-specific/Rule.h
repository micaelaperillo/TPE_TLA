
#ifndef RULE_HEADER
#define RULE_HEADER

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
void initializeRuleModule();

/** Shutdown module's internal state. */
void shutdownRuleModule();

typedef struct {
    boolean succeed;
    int value;
} RuleResult;

typedef RuleResult (*BinaryOperator)(const int, const int);

RuleResult computeRule(Rule * rule);

RuleResult computeProperty(Property * property);

#endif //RULE_HEADER