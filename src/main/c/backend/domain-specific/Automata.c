#include "Automata.h"

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

static AutomataResult _invalidComputation() {
    AutomataResult automataResult = {
            .succeed = false,
            .value = 0
    };
    return automataResult;
}

AutomataResult computeAutomata(Automata * automata) {
    if (!computeRuleNumbers(automata->ruleNumber).succeed
    || !computeGrid(automata->grid).succeed
    || !computeCheckList(automata->checks).succeed) {
        return _invalidComputation();
    } else {
        AutomataResult automataResult = {
                .succeed = true,
                .value = 0
        };
        return automataResult;
    }
}

AutomataResult computeRuleNumbers(RuleNumber * ruleNumber) {
    if (ruleNumber->neighboursAliveToBeBorn > ruleNumber->neighboursAliveToDie
    || ruleNumber->neighboursAliveToSurvive > ruleNumber->neighboursAliveToDie) {
        return _invalidComputation();
    } else {
        AutomataResult automataResult = {
                .succeed = true,
                .value = 0
        };
        return automataResult;
    }
}

AutomataResult computeGrid(Grid * grid) {
    if (grid->height == 0 || grid->width == 0) {
        return _invalidComputation();
    } else {
        AutomataResult automataResult = {
                .succeed = true,
                .value = 0
        };
        return automataResult;
    }
}


AutomataResult computeCheckList(CheckList * checkList,Grid* grid) {
    //TODO: reemplazar AutomataResult por booleano maybe?
    CheckList* current=checkList;
    AutomataResult automataResult = {
            .succeed = true,
            .value = 0
    };
    while(current){
        if(current->check->x>grid->width ||current->check->y>grid->height ){
            return _invalidComputation();
        }
        current=current->next;
    }
    return automataResult;
}
