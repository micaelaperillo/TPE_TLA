#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PUBLIC FUNCTIONS */

void releaseConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		free(constant);
	}
}

void releaseProgram(Program* program) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (program != NULL) {
        releaseAutomata(program->automata);
        releaseRule(program->rule);
        free(program);
    }
}

void releaseAutomata(Automata* automata) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (automata != NULL) {
        releaseRuleNumber(automata->ruleNumber);
        releaseGrid(automata->grid);
        releaseCheckList(automata->checks);
        free(automata);
    }
}

void releaseRule(Rule* rule) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (rule != NULL) {
        releasePropertyList(rule->properties);
        free(rule);
    }
}

void releaseRuleNumber(RuleNumber* ruleNumber) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (ruleNumber != NULL) {
        free(ruleNumber);
    }
}

void releaseGrid(Grid* grid) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (grid != NULL) {
        free(grid);
    }
}

void releaseCheckList(CheckList* checkList) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (checkList != NULL) {
        releaseCheck(checkList->check);
        releaseCheckList(checkList->next);
        free(checkList);
    }
}

void releaseCheck(Check* check) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (check != NULL) {
        free(check);
    }
}

void releasePropertyList(PropertyList* propertyList) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (propertyList != NULL) {
        releaseProperty(propertyList->property);
        releasePropertyList(propertyList->next);
        free(propertyList);
    }
}

void releaseProperty(Property* property) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (property != NULL) {
        releaseParameterList(property->parameters);
        free(property->propertyName);
        free(property);
    }
}

void releaseParameterList(ParameterList* parameterList) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (parameterList != NULL) {
        releaseData(parameterList->data);
        releaseParameterList(parameterList->next);
        free(parameterList);
    }
}

void releaseData(Data* data) {
    logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
    if (data != NULL) {
        free(data->dataType);
        free(data);
    }
}

/*
void releaseProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseExpression(program->expression);
		free(program);
	}
}
 */
