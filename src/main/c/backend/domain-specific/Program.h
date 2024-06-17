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

enum ErrorCode {
    UNSPECIFIED_ERROR,
    INVALID_AUTOMATA_NUMBERS,
    INVALID_PARAMETER_TYPE,
    INVALID_PARAMETER_AMOUNT,
    ILLEGAL_CHECK,
    INVALID_GRID,
    INVALID_PROPERTY
};

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

#endif //AUTOMATA_HEADER
