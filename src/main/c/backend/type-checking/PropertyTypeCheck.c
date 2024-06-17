#include <string.h>
#include <stdlib.h>

#define BASE_SIZE 26 //alphabet letters

struct PropertyNameList {
    char * name;
    struct PropertyNameList * next;
}PropertyNameList;

typedef struct PropertyNameList * names;

names propertyNameList[BASE_SIZE] = {NULL};

int isPropertyUnique(char * property) {
    int idx = property[0] % 26; //scuffed solution, but should work consistently
    names curr = propertyNameList[idx];
    while(curr != NULL) {
        if (strcmp(property, curr->name) == 0) {
            return 0;
        }
        curr = curr->next;
    }
    names new = malloc(sizeof(PropertyNameList));
    new->name = property; //this should be long gone by the time this needs to be freed or accessed again
    new->next = propertyNameList[idx];
    propertyNameList[idx] = new;
    return 1;
}

void releasePropertyNameList() {
    for (int i=0; i<BASE_SIZE; i++) {
        if (propertyNameList[i] != NULL) {
            names curr = propertyNameList[i];
            names prev;
            while (curr != NULL) {
                prev = curr;
                curr = curr->next;
                free(prev);
            }
        }
    }
}