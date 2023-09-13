//phonebook05 | 구조체에 대한 포인터, 동적 메모리 할당
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_SIZE 100

typedef struct person {
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

int n = 0;
Person directory[CAPACITY];

int main() {

}