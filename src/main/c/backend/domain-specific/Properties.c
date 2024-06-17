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
    while (properties[i] != 0) {
        if (strcmp(propertyName, properties[i]->name) == 0
        && checkParameters(parameterList, properties[i]->type, properties[i]->paramAmount)) {
            return 1;
        }
        i++;
    }
    return 0;
}

int checkParameters(ParameterList * parameterList, char * type, int maxParams) {
    int i = 0;
    ParameterList * curr = parameterList;
    ParameterList * next = parameterList->next;
    while((maxParams == UNDEFINED || i < maxParams) && curr != NULL) {
        if (strcmp(curr->data->dataType, type) != 0) {
            return 0;
        }
        curr = next;
        next = curr->next;
    }
    return 1;
}