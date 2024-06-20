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

static void _generateEpilogue();
static void _generateProgram(Program * program);
static void _generateAutomata(Automata* automata);
static void _generateRule(Rule* automata);
static void _generatePrologue(void);
static char * _indentation(const unsigned int indentationLevel);
static void _output(const unsigned int indentationLevel, const char * const format, ...);
static void _generateRuleNumber(RuleNumber* ruleNumber );
static void _generateGrid(Grid* grid);
static void _generateCheckList(CheckList* checks);
static void _generateRules(Rule* rule);
static void _generatePropertyList(PropertyList* propertyList);
/**
 * Creates ending footing of the program
 */
static void _generateEpilogue() {
	_output(0,"%s","if __name__ == \"__main__\":\n");
	_output(1,"%s","main()\n");
	fclose(pyFileOutput);
}

static void _generateRuleNumber(RuleNumber* ruleNumber){
	_output(2,"%s:%d,\n","\"alive\"",ruleNumber->neighboursAliveToSurvive);
	_output(2,"%s:%d,\n","\"dead\"",ruleNumber->neighboursAliveToDie);
	_output(2,"%s:%d,\n","\"born\"",ruleNumber->neighboursAliveToBeBorn);
}

static void _generateGrid(Grid* grid){
	_output(2,"%s:%d,\n","\"grid_x\"",grid->width);
	_output(2,"%s:%d,\n","\"grid_y\"",grid->height);
}


static void _generateStyleParams(Program* program){
	_output(1,"%s","\"style_params\": {\n");
	_generateGrid(program->automata->grid);
	_generateRules(program->rule);
	_output(1,"%s","}\n");
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
	_output(2,"%s","\"rules\": {\n");
	_output(3,"(%d, %d)\n",currentCheck->check->x,currentCheck->check->y);//first rule before all rules
	currentCheck=currentCheck->next;
	while(currentCheck){
		_output(3,",(%d, %d)\n",currentCheck->check->x,currentCheck->check->y);
		currentCheck=currentCheck->next;
	}
	_output(2,"%s","}\n");
}

static void _generateAutomataParams(Automata* automata){
	_output(1,"%s","\"automata_params\" : {\n");
	_generateRuleNumber(automata->ruleNumber);
	_generateCheckList(automata->checks);
		_output(1,"%s","},\n");
}


static void _generateProgram(Program * program) {
	_output(0,"%s","modified_params= {\n");
	_generateAutomataParams(program->automata);
	_generateStyleParams(program);
	_output(0,"%s","}\n");
	_generateMainProgram();
}

static void _generateRules(Rule* rule){
	PropertyList* propertyList=rule->properties;
	while(propertyList){
		_generatePropertyList(propertyList);
		propertyList=propertyList->next;
	}
}


static void _generatePropertyList(PropertyList* propertyList){
	Property* prop=propertyList->property;
	if(strcmp(prop->propertyName,"bg_color")){
		_output(2,"\"bg_color\": \"#%06x\", \n",prop->parameters->data->value);
	}
	else if (strcmp(prop->propertyName,"color")){
		ParameterList* param=prop->parameters;
		_output(2,"\"color\": [\" #%06x \"",param->data->value);
		param=param->next;
		while(param){
			_output(0,", \" %06x \"",param->data->value);
			param=param->next;
		}
		_output(0,"%s","],\n");
	}
	else if(strcmp(propertyList->property->propertyName,"wrapping")){
		_output(2,"wrapping: %s ,\n",propertyList->property->parameters->data==true ? "True":"False");
	}
}

/**
 * Creates the necessary imports for the program ( ͡° ͜ʖ ͡°)
 */
static void _generatePrologue(void) {
	_output(0, "%s","import pygame\nimport numpy as np\nimport time\nimport tk as tk\n");
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
static void _output(const unsigned int indentationLevel, const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(pyFileOutput, effectiveFormat, arguments);
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
