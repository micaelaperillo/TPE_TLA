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

typedef struct ParameterList ParameterList;
typedef struct Property Property;
typedef struct PropertyList PropertyList;
typedef struct Data Data;
typedef struct Automata Automata;
typedef struct Grid Grid;
typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;
typedef struct Automata Automata;
typedef struct Check Check;
typedef struct CheckList CheckList;
typedef struct Rule Rule;
typedef struct RuleNumber RuleNumber;
typedef struct Colors Colors;
typedef struct BgColors BgColors;
/**
 * Node types for the Abstract Syntax Tree (AST).
 */

struct Constant {
	int value;
};

struct Program {
	Automata* automata;
    Rule* rule;
};

struct RuleNumber {
	int neighboursAliveToSurvive;
	int neighboursAliveToDie;
	int neighboursAliveToBeBorn;
};


struct CheckList {
	Check * check;
	CheckList * next;
};


struct Check {
	int x,y; //( ͡° ͜ʖ ͡°) ayuda
};

struct Grid {
	int width;
	int height;
};

struct Automata {
	RuleNumber * ruleNumber;
	Grid * grid;
	CheckList * checks;
};

struct Data {
    Token type;
    int value;
};

struct ParameterList {
    Data * data;
    ParameterList * next;
    int multipleParameters; //only set in backend
};

struct Property {
    char * propertyName;
    ParameterList * parameters;
};

struct PropertyList {
    Property * property;
    PropertyList * next;
};

struct Rule {
	PropertyList * properties;
};



/**
 * Node recursive destructors.
 */
void releaseProgram(Program * program);

void releaseAutomata(Automata* automata);

void releaseRule(Rule* rule);

void releaseRuleNumber(RuleNumber* ruleNumber);

void releaseGrid(Grid* grid);

void releaseCheckList(CheckList* checkList);

void releaseCheck(Check* check);

void releasePropertyList(PropertyList* propertyList);

void releaseProperty(Property* property);

void releaseParameterList(ParameterList* parameterList);

void releaseData(Data* data);

#endif
