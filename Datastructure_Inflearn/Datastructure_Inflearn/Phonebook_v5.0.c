//phonebook05 | 구조체에 대한 포인터, 동적 메모리 할당
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 100
#define BUFFER_SIZE 100

typedef struct person {
	char* name;
	char* number;
	char* email;
	char* group;
}Person;

Person ** directory;
int n; //주소록 명 수
int capacity;

//초기설정
void init() {
	directory = (Person**)malloc(sizeof(Person*) * INIT_CAPACITY);
	capacity = INIT_CAPACITY;
	n = 0;
}

int main() {
	
}

//라인 글자수 반환
int read_line(FILE *fp, char str[], int limit) {
	int ch; //읽어온 글자를 담음
	int i; //글자수

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i > n)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void load(char* fileName) {
	char buff[INIT_CAPACITY]; //불러온 파일을 담음
	char* name, *number, *email, *group;
	char* token;

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while (1) {
		if (read_line(fp, buff, BUFFER_SIZE) <= 0)
			break;
		name = strtok(buff, "#");
		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			number = NULL;
		else
			number = strdup(token);

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			email = NULL;
		else
			email = strdup(token);

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			group = NULL;
		else
			group = strdup(token);
		add(strdup(name), number, email, group);
	}
	fclose(fp);
}

void add(char * name, char* number, char* email, char* group ) {
	
}

//이전하고 완전 똑같음
void status() {
	for (int i; i < n; i++) 
		print_person(directory[i]);
	printf("Total %d persons.\n", n);
}

void print_person(Person *p) {//Person의 주소값, 즉 directory[i]값이 복사됨
	printf("%s:\n", p -> name);
	printf("   Phone:%s\n", p -> number);
	printf("   Email:%s\n", p -> email);
	printf("   Group:%s\n", p -> group);
}