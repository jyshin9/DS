//phonebook04 | 더 많은 항목, 구조체(structure)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100

typedef struct Phonebook {
	char* number;
	char* email;
	char* group;
}phonebook;

