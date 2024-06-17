#include "Program.h"
#include "Properties.h"
#include "../type-checking/PropertyTypeCheck.h"

ProgramResult computeAutomata(Automata * automata);

ProgramResult computeRuleNumbers(RuleNumber * ruleNumber);

ProgramResult computeGrid(Grid * grid);

ProgramResult computeCheckList(CheckList * checkList, Grid* grid);

ProgramResult computeRule(Rule * rule);


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

static ProgramResult _invalidComputation(int value) {
    ProgramResult programResult = {
            .succeed = false,
            .value = value
    };
    return programResult;
}

ProgramResult computeProgram(Program * program) {
    ProgramResult result;
    if (!(result = computeAutomata(program->automata)).succeed) {
        return result;
    }
    if (program->rule != NULL && !(result = computeRule(program->rule)).succeed) {
        return result;
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
        int ret = isPropertyValid(prop->propertyName, prop->parameters);
        switch (ret) {
            case OK:
                break;
            case INVALID_PARAM_AMOUNT:
                releasePropertyNameList();
                return _invalidComputation(INVALID_PARAMETER_AMOUNT);
            case INVALID_PARAM_TYPE:
                releasePropertyNameList();
                return _invalidComputation(INVALID_PARAMETER_TYPE);
            case INVALID_PROP:
                releasePropertyNameList();
                return _invalidComputation(INVALID_PROPERTY);
            case DUPLICATE_PROP:
                releasePropertyNameList();
                return _invalidComputation(REDEFINED_PROPERTY);
            default:
                break;
        }
        curr = curr->next;
    }
    releasePropertyNameList();
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
    if (ruleNumber->neighboursAliveToBeBorn > ruleNumber->neighboursAliveToDie
    || ruleNumber->neighboursAliveToSurvive > ruleNumber->neighboursAliveToDie) {
        return _invalidComputation(INVALID_AUTOMATA_NUMBERS);
    }
    ProgramResult programResult = {
            .succeed = true,
            .value = 0
    };
    return programResult;
}

ProgramResult computeGrid(Grid * grid) {
    if (grid->height <= 0 || grid->width <= 0) {
        return _invalidComputation(INVALID_GRID);
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
            return _invalidComputation(ILLEGAL_CHECK);
        }
        current=current->next;
    }
    return programResult;
}
