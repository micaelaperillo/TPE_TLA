#include <string.h>
#include "Properties.h"

struct Prop {
    char * name;
    char * type;
    int paramAmount;
}Prop;

#define PROP(name, type, param) &(struct Prop){name, type, param}

#define UNDEFINED -1

struct Prop * properties[] = {
        PROP("initial_cells", "int", UNDEFINED),
        PROP("window_width", "int", 1),
        PROP("window_height", "int", 1),
        PROP("wrapping", "bool", 1),
        PROP("min_time_between_updates", "int", 1),
        PROP("color", "color", UNDEFINED),
        PROP("bg_color", "color", 2),
        0
};

int checkParameters(ParameterList * parameterList, char * type, int maxParams);

int isPropertyValid(char * propertyName, ParameterList * parameterList) {
    int i = 0;
    while (properties[i] != NULL) {
        if (strcmp(propertyName, properties[i]->name) == 0) {
            return checkParameters(parameterList, properties[i]->type, properties[i]->paramAmount);
        }
        i++;
    }
    return INVALID_PROP;
}

int checkParameters(ParameterList * parameterList, char * type, int maxParams) {
    int i = 0;
    ParameterList * curr = parameterList;
    while(curr != NULL) {
        if (maxParams != UNDEFINED && i >= maxParams) {
            return INVALID_PARAM_AMOUNT;
        }
        if (strcmp(curr->data->dataType, type) != 0) {
            return INVALID_PARAM_TYPE;
        }
        curr = curr->next;
        i++;
    }
    if (maxParams != UNDEFINED && i != maxParams) {
        return INVALID_PARAM_AMOUNT;
    }
    return OK;
}