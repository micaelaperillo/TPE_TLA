#include "Generator.h"

/* MODULE INTERNAL STATE */

#define INDENTATION_CHARACTER '\t'
#define INDENTATION_SIZE 1
#define PY_FILE_NAME "game_Of_Life.py"
#define CAL9K_PATHFILE "/utils/cal9k.py"
static Logger * _logger = NULL;

FILE* pyFileOutput;
FILE *pyFileMain;
void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PRIVATE FUNCTIONS */

static const char _expressionTypeToCharacter(const ExpressionType type);
static void _generateEpilogue();
static void _generateProgram(Program * program);
static void _generateAutomata(Automata* automata);
static void _generateRule(Rule* automata);
static void _generatePrologue(void);
static char * _indentation(const unsigned int indentationLevel);
static void _output(FILE* file,const unsigned int indentationLevel, const char * const format, ...);
static void _generateRuleNumber(RuleNumber* ruleNumber );
static void _generateGrid(Grid* grid);
static void _generateCheckList(CheckList* checks);
/**
 * Creates ending footing of the program
 */
static void _generateEpilogue() {
	_output(pyFileOutput,0,"%s","if __name__ == \"__main__\":\n");
	_output(pyFileOutput,1,"%s","main()\n");
	fclose(pyFileOutput);
}

static void _generateRuleNumber(RuleNumber* ruleNumber){
	_output(pyFileOutput,2,"%s:%d,\n","\"alive\"",ruleNumber->neighboursAliveToSurvive);
	_output(pyFileOutput,2,"%s:%d,\n","\"dead\"",ruleNumber->neighboursAliveToDie);
	_output(pyFileOutput,2,"%s:%d,\n","\"born\"",ruleNumber->neighboursAliveToBeBorn);
}

static void _generateGrid(Grid* grid){
	_output(pyFileOutput,2,"%s:%d,\n","\"grid_x\"",grid->width);
	_output(pyFileOutput,2,"%s:%d,\n","\"grid_y\"",grid->height);
}


static void _generateStyleParams(Automata* automata){
	_output(pyFileOutput,1,"%s","\"style_params\": {\n");
	_generateGrid(automata->grid);
	_output(pyFileOutput,1,"%s","}\n");
}

static void _generateMainProgram(){
	char c;
	while((c=fgetc(pyFileMain))!=EOF){
		fputc(c,pyFileOutput);
	}
	fclose(pyFileMain);
}

static void _generateCheckList(CheckList* checks){
	CheckList* currentCheck=checks;
	_output(pyFileOutput,2,"%s","\"rules\": {\n");
	_output(pyFileOutput,3,"(%d, %d)\n",currentCheck->check->x,currentCheck->check->y);//first rule before all rules
	currentCheck=currentCheck->next;
	while(currentCheck){
		_output(pyFileOutput,3,",(%d, %d)\n",currentCheck->check->x,currentCheck->check->y);
		currentCheck=currentCheck->next;
	}
	_output(pyFileOutput,2,"%s","}\n");
}

static void _generateAutomataParams(Automata* automata){
	_output(pyFileOutput,1,"%s","\"automata_params\" : {\n");
	_generateRuleNumber(automata->ruleNumber);
	_generateCheckList(automata->checks);
		_output(pyFileOutput,1,"%s","},\n");
}

static void _generateAutomata(Automata* automata){
	_output(pyFileOutput,0,"%s","params= {\n");
	_generateAutomataParams(automata);
	_generateStyleParams(automata);
	_output(pyFileOutput,0,"%s","}\n");
}

static void _generateProgram(Program * program) {
	_generateAutomata(program->automata);
	//_generateRules(program->rule);
	_generateMainProgram();
}

/**
 * Creates the necessary imports for the program ( ͡° ͜ʖ ͡°)
 */
static void _generatePrologue(void) {
	_output(pyFileOutput,0, "%s","import pygame\nimport numpy as np\nimport time\nimport tk as tk\n");
}

/**
 * Generates an indentation string for the specified level.
 */
static char * _indentation(const unsigned int level) {
	return indentation(INDENTATION_CHARACTER, level, INDENTATION_SIZE);
}

/**
 * Outputs a formatted string to standard output.
 */
static void _output(FILE* file,const unsigned int indentationLevel, const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(file, effectiveFormat, arguments);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}

/** PUBLIC FUNCTIONS */

void generate(CompilerState * compilerState) {
	char cal9kAbsolutePath[1024];
	getcwd(cal9kAbsolutePath,sizeof(cal9kAbsolutePath));
	strcat(cal9kAbsolutePath,CAL9K_PATHFILE);
	pyFileMain=fopen(cal9kAbsolutePath,"r");

	if(pyFileMain==NULL){
		logError(_logger,"Roto abrir el archivo cal9k.py");
		return;
	}

	pyFileOutput=fopen(PY_FILE_NAME,"w");
	if(pyFileOutput==NULL){
		logError(_logger,"Roto crear el archivo .py");
		return;
	}

	logDebugging(_logger, "Generating final output...");
	_generatePrologue();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue();
	logDebugging(_logger, "Generation is done.");
}
