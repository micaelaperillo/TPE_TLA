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

AutomataResult computeCheckList(CheckList * checkList) {
    //TODO checkear que no haga checks con valores mayores a compute grid
    AutomataResult automataResult = {
            .succeed = true,
            .value = 0
    };
    return automataResult;
}
