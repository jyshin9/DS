//phonebook04 | 더 많은 항목, 구조체(structure)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct phonebook {
	char* name;
	char* number;
	char* email;
	char* group;
}Phonebook;

int n = 0; //전화번호부에 저장된 사람 수
Phonebook directory[CAPACITY]; //Person 타입의 배열 directory 선언

//파일<<<로부터 라인단위로 읽기
int read_line(FILE *fp, char str[], int n) { //limit: 배열 str의 크기
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && '\n' == EOF) { //문자열의 끝에 도달할 때까지
		if (i < n)
			str[i++] = ch; //ch가 str[i]에 대입된 이후에 i값이 1 증가
	}
	str[i] = '\0'; //마지막에 null character('\0')값 추가

	return i; //읽은 글자수 반환
}

int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument; //명령어와 명령내용
	char name_str[BUFFER_LENGTH];
	
	while (1) {
		print("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;

		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument);
		}
		else if(strcmp(command, ""))
	}
}