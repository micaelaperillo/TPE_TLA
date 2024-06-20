#include <string.h>
#include "Properties.h"
#include "../../frontend/syntactic-analysis/BisonParser.h"
#include "../type-checking/PropertyTypeCheck.h"

struct Prop {
    char * name;
    Token type;
    int paramAmount;
}Prop;

#define PROP(name, type, param) &(struct Prop){name, type, param}

#define UNDEFINED -1

struct Prop * properties[] = {
        PROP("initial_cells", INTEGER, UNDEFINED),
        PROP("window_width", INTEGER, 1),
        PROP("window_height", INTEGER, 1),
        PROP("wrapping", BOOLEAN, 1),
        PROP("min_time_between_updates", INTEGER, 1),
        PROP("color", COLOR_HANDLER, UNDEFINED),
        PROP("bg_color", COLOR_HANDLER, 1),
        NULL
};

int checkParameters(ParameterList * parameterList, Token type, int maxParams);

int isPropertyValid(char * propertyName, ParameterList * parameterList) {
    int i = 0;
    while (properties[i] != NULL) {
        if (strcmp(propertyName, properties[i]->name) == 0 && isPropertyUnique(propertyName)) {
            return checkParameters(parameterList, properties[i]->type, properties[i]->paramAmount);
        }
        i++;
    }
    return INVALID_PROP;
}

int checkParameters(ParameterList * parameterList, Token type, int maxParams) {
    int i = 0;
    ParameterList * curr = parameterList;
    while(curr != NULL) {
        if (maxParams != UNDEFINED && i >= maxParams) {
            return INVALID_PARAM_AMOUNT;
        }
        if (curr->data->type != type) {
            return INVALID_PARAM_TYPE;
        }
        curr = curr->next;
        i++;
    }
    if (maxParams != UNDEFINED && i != maxParams) {
        return INVALID_PARAM_AMOUNT;
    }
    parameterList->multipleParameters = maxParams != 1 ? 1 : 0;
    return OK;
}
