#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;

typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;
typedef struct Automata Automata;
typedef struct Check Check;
typedef struct Rule Rule;
typedef struct RuleNumber RuleNumber;
typedef struct Colors Colors;
typedef struct BgColors BgColors;
/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION
};

enum FactorType {
	CONSTANT,
	EXPRESSION
};

struct Constant {
	int value;
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
};

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
	};
	ExpressionType type;
};

struct Program {
	Expression * expression;
};

struct RuleNumber {
	int neighboursAliveToSurvive;
	int neighboursAliveToDie;
	int neighboursAliveToBeBorn;
};



struct Check {
	int x,y; //( ͡° ͜ʖ ͡°) ayuda
	struct Check * nextCheck;
};


struct Automata {
	RuleNumber ruleNumber; 
	int grid_x;
	int grid_y;
	Check checks;
};

struct Colors {
	int R;
	int G;
	int B;
};

struct BgColors{
	int OnColors;
	int OffColors;
};

struct Rule {
	Colors colors;
	BgColors bgColors;
	boolean wrapping;
};


/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor);
void releaseProgram(Program * program);

#endif
