#include "Program.h"
#include "Properties.h"

ProgramResult computeAutomata(Automata * automata);

ProgramResult computeRuleNumbers(RuleNumber * ruleNumber);

ProgramResult computeGrid(Grid * grid);

ProgramResult computeCheckList(CheckList * checkList, Grid* grid);

ProgramResult computeRule(Rule * rule);

ProgramResult computeProperty(Property * property);

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeAutomataModule() {
    _logger = createLogger("Automata");
}

void shutdownAutomataModule() {
    if (_logger != NULL) {
        destroyLogger(_logger);
    }
}

//TODO: hacer que se devuelva un codigo de error dependiendo del caso

static ProgramResult _invalidComputation() {
    ProgramResult programResult = {
            .succeed = false,
            .value = 0
    };
    return programResult;
}

ProgramResult computeProgram(Program * program) {
    if (!computeAutomata(program->automata).succeed) {
        return _invalidComputation();
    }
    if (program->rule != NULL && !computeRule(program->rule).succeed) {
        return _invalidComputation();
    }
    ProgramResult programResult = {
            .succeed = true,
            .value = 0
    };
    return programResult;
}

ProgramResult computeRule(Rule *rule) {
    PropertyList *curr = rule->properties;
    while (curr != NULL) {
        Property *prop = curr->property;
        if (!isPropertyValid(prop->propertyName, prop->parameters)) {
            return _invalidComputation();
        }
        curr = curr->next;
    }
    ProgramResult programResult = {
            .succeed = true,
            .value = 0
    };
    return programResult;
}

ProgramResult computeAutomata(Automata * automata) {
    ProgramResult result;
    if (!(result = computeRuleNumbers(automata->ruleNumber)).succeed) {
        return result;
    }
    if (!(result = computeGrid(automata->grid)).succeed) {
        return result;
    }
    if (!(result = computeCheckList(automata->checks, automata->grid)).succeed) {
        return result;
    }
    ProgramResult programResult = {
            .succeed = true,
            .value = 0
    };
    return programResult;
}

ProgramResult computeRuleNumbers(RuleNumber * ruleNumber) {
    if (ruleNumber->neighboursAliveToBeBorn > ruleNumber->neighboursAliveToDie) {
        return _invalidComputation();
    }
    if (ruleNumber->neighboursAliveToSurvive > ruleNumber->neighboursAliveToDie) {
        return _invalidComputation();
    }
    ProgramResult programResult = {
            .succeed = true,
            .value = 0
    };
    return programResult;
}

ProgramResult computeGrid(Grid * grid) {
    if (grid->height == 0 || grid->width == 0) {
        return _invalidComputation();
    } else {
        ProgramResult programResult = {
                .succeed = true,
                .value = 0
        };
        return programResult;
    }
}


ProgramResult computeCheckList(CheckList * checkList,Grid* grid) {
    CheckList* current=checkList;
    ProgramResult programResult = {
            .succeed = true,
            .value = 0
    };
    while(current){
        if(current->check->x>grid->width ||current->check->y>grid->height ){
            return _invalidComputation();
        }
        current=current->next;
    }
    return programResult;
}
