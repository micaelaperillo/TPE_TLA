#ifndef CAL_9000_PROPERTIES_H
#define CAL_9000_PROPERTIES_H

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include <limits.h>

enum PropertyReturnCodes {
    OK,
    INVALID_PARAM_TYPE,
    INVALID_PARAM_AMOUNT,
    INVALID_PROP,
    DUPLICATE_PROP
};

int isPropertyValid(char * propertyName, ParameterList * parameterList);

#endif //CAL_9000_PROPERTIES_H
