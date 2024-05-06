%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	Token token;
	boolean boolean;
	char* string;

	/** Non-terminals. */
	Automata* automata;
	CheckList* checkList;
	Check* check;
	RuleNumber* ruleNumber;
	Rule* rule;
	Grid* grid;
	Data* data_type;
	ParameterList* parameter_list;
	PropertyList* property_list;
	Property* property;

	Program * program;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */
%token <integer> INTEGER
%token <token> COMMA
%token <token> BOOLEAN
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_PARENTHESIS
%token <token> AUTOMATA
%token <token> AUTOMATA_NT
%token <token> RULE
%token <token> RULE_NT
%token <token> UNKNOWN
%token <token> COLON
%token <token> SEMICOLON
%token <token> EQUAL
%token <token> CHECK
%token <integer> COLOR_HANDLER
%token <token> GRID
%token <string> PROPERTY


/** Non-terminals. */
%type <automata> automata
%type <program> program
%type <checkList> checkList
%type <check> check
%type <ruleNumber> ruleNumber
%type <rule> rule
%type <grid> grid
%type <data_type> data_type
%type <parameter_list> parameter_list
%type <property_list> property_list
%type <property> property

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

program: automata rule												{ $$ = AutomataProgramSemanticAction(currentCompilerState(), $1, $2); }
	| rule automata												{ $$ = AutomataProgramSemanticAction(currentCompilerState(), $2, $1); }
	;

ruleNumber: AUTOMATA OPEN_PARENTHESIS INTEGER COMMA INTEGER COMMA INTEGER CLOSE_PARENTHESIS			{ $$ = RuleNumberSemanticAction($3, $5, $7); }
	;

grid: GRID OPEN_PARENTHESIS INTEGER COMMA INTEGER CLOSE_PARENTHESIS						{ $$ = GridSemanticAction($3, $5); }
	;

checkList: %empty												{$$ = CheckListSemanticAction(NULL, NULL);}
	| checkList check											{ $$ = CheckListSemanticAction($2, $1); }
	;

check: OPEN_PARENTHESIS INTEGER COMMA INTEGER CLOSE_PARENTHESIS SEMICOLON					{ $$ = CheckSemanticAction($2, $4); }
	;

automata: AUTOMATA ruleNumber COMMA grid COLON checkList AUTOMATA_NT						{ $$ = AutomataSemanticAction($2, $4, $6); }
	;

data_type: BOOLEAN												{ $$ = DataSemanticAction("bool", $1); }
    | COLOR_HANDLER												{ $$ = DataSemanticAction("color", $1); }
    | INTEGER													{ $$ = DataSemanticAction("int", $1); }
    ;

parameter_list: data_type											{ $$ = ParameterListSemanticAction($1, NULL); }
    | parameter_list COMMA data_type										{ $$ = ParameterListSemanticAction($3, $1); }
    ;

property: PROPERTY EQUAL OPEN_PARENTHESIS parameter_list CLOSE_PARENTHESIS SEMICOLON				{ $$ = PropertySemanticAction($1, $4); }
    ;

property_list: %empty												{ $$ = PropertyListSemanticAction(NULL, NULL); }
    | property_list property											{ $$ = PropertyListSemanticAction($2, $1); }
    ;

rule: RULE COLON property_list RULE_NT										{ $$ = RuleSemanticAction($3); }
	;

%%
