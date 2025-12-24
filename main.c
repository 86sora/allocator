#include "alloc.h"
#include <string.h>
#include <stdio.h>

typedef struct {
    char *name;
    int age;
} person_t;

int main() {
    person_t* personptr = (person_t *) alloc(1,sizeof(person_t));
    personptr->name = alloc(5,sizeof(char));
    strcpy(personptr->name, "deni");
    personptr->age = 10;
    printf("%p \n",(void *) personptr);
    printf("%s %d\n", personptr->name, personptr->age);
    return 0;
}
