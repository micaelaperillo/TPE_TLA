#include "Rule.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeRuleModule() {
    _logger = createLogger("Rule");
}

void shutdownRuleModule() {
    if (_logger != NULL) {
        destroyLogger(_logger);
    }
}

static RuleResult _invalidComputation() {
    RuleResult ruleResult = {
            .succeed = false,
            .value = 0
    };
    return ruleResult;
}

//TODO armar la lista de propiedades aceptadas (en un json si es posible) y revisar desde ahi si es valida
