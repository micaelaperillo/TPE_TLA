%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	Token token;

	/** Non-terminals. */
	Automata* automata;
	Check* check;

	Constant * constant;
	Expression * expression;
	Factor * factor;
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
%token <token> ADD
%token <token> CLOSE_PARENTHESIS
%token <token> DIV
%token <token> MUL
%token <token> OPEN_PARENTHESIS
%token <token> SUB
%token <token> AUTOMATA
%token <token> AUTOMATA_NT
%token <token> RULE
%token <token> RULE_NT
%token <token> UNKNOWN
%token <token> COLON
%token <token> SEMICOLON
%token <token> COLOR
%token <token> CHECK
%token <token> BG_COLOR
%token <integer> COLOR_HANDLER
%token <token> WRAPPING
%token <integer> TRUE
%token <integer> FALSE
%token <token> GRID


/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program
%type <check> check
%type <automata_spec> automata_spec
%type <grid> grid
/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

program: automata rule																				{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| rule automata
	| automata													
	;

automata_spec: AUTOMATA OPEN_PARENTHESIS INTEGER COMMA INTEGER COMMA INTEGER CLOSE_PARENTHESIS		{ $$ = AutomataSpecificationSemanticAction($3, $5, $7); }
	;

grid: GRID OPEN_PARENTHESIS INTEGER COMMA INTEGER CLOSE_PARENTHESIS									{ $$ = GridSemanticAction($3, $5); }
	;

checkList: %empty
	| checkList check
	;

check: OPEN_PARENTHESIS INTEGER COMMA INTEGER CLOSE_PARENTHESIS SEMICOLON							{ $$ = CheckSemanticAction($2, $4); }
	;

automata_header: automata_spec COMMA grid COLON
	;

automata: automata_header checkList AUTOMATA_NT
	;

rule_header: RULE COLON 
	;

color_setup: COLOR OPEN_PARENTHESIS COLOR_HANDLER CLOSE_PARENTHESIS SEMICOLON

boolean: TRUE
	| FALSE
	;

bg_color_setup: BG_COLOR OPEN_PARENTHESIS COLOR COMMA CLOSE_PARENTHESIS SEMICOLON

wrapping: WRAPPING OPEN_PARENTHESIS boolean CLOSE_PARENTHESIS SEMICOLON

rule: rule_header color_setup bg_color_setup wrapping RULE_NT

%%
