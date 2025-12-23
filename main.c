#include "alloc.h"
#include <string.h>
#include <stdio.h>

typedef struct {
    char *name;
    int age;
} person_t;

int main() {
    person_t* personptr = (person_t *) alloc(1,sizeof(person_t));
    person_t* personptr2 = (person_t *) alloc(1,sizeof(person_t));
    personptr->name = alloc(5,sizeof(char));
    strcpy(personptr->name, "deni");
    personptr->name[4] = '\0';
    printf("%p %p\n",personptr, personptr2);
    printf("%s %p\n", personptr->name, personptr->name);
    return 0;
}
