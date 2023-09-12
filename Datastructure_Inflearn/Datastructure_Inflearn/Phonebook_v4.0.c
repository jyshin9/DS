//phonebook04 | 더 많은 항목, 구조체(structure)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_LENGTH 100

//전화번호부 구조체 선언
typedef struct phonebook {
	char* name;
	char* number;
	char* email;
	char* group;
}Phonebook;

int n = 0; //전화번호부에 저장된 사람 수
Phonebook directory[CAPACITY]; //Phonebook 타입의 배열 directory 선언

int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument; //명령어와 명령내용
	char name_str[BUFFER_LENGTH];
	
	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue; //input이 아무것도 없다면

		command = strtok(command_line, " ");

		if (strcmp(command, "read") == 0) {
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			load(argument);
		}
		else if (strcmp(command, "add") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			add_div(name_str);
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0) {
			if (compose_name(name_str, BUFFER_LENGTH) <= 0) {
				printf("Invalid argument.\n");
				continue;
			}
			remove(name_str);
		}
		else if (strcmp(command, "save") == 0) {
			argument = strtok(command, " ");
			if (strcmp(argument, "as") != 0) {
				printf("Invalid arguments.\n");
				continue;
			}
			argument = strtok(NULL, " ");
			if (argument == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			save(argument);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}

void save(char * argument) {
	
}

//공백을 기준으로 나누어져 있는 문자를 합쳐서 하나의 문자열로 만듦.
//add_div, find, delete에 사용
int compose_name(char str[], int limit) { //이름을 담아둘 배열 str
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " "); //이름 성
	if (ptr == NULL) return 0;
	
	strcpy(str, ptr);
	length += strlen(str);

	while (ptr = strtok(NULL, " ") != NULL) {
		str = str + ' ' + ptr; //음 몰겟다
	}
	return length;
}

//파일<<<로부터 라인단위로 읽기
int read_line(FILE* fp, char str[], int n) { //limit: 배열 str의 크기
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) { //문자열의 끝에 도달할 때까지
		if (i < n) //오버플로우 방지
			str[i++] = ch; //ch가 str[i]에 대입된 이후에 i값이 1 증가
	}
	str[i] = '\0'; //마지막에 null character('\0')값 추가
	return i; //읽은 글자수 반환
}

void load(char * argument) {
	char buff[BUFFER_LENGTH];
	char* name, * number, * email, * group;

	FILE* fp = fopen(argument, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}

	while (1) {
		if (read_line(fp, buff, BUFFER_LENGTH) <= 0)
			break;
		name = strtok(buff, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
	}
	fclose(fp);
}

void add_div(char *argument) {
	directory[n].name = argument;
	printf("Phone: ");
	scanf("%s", directory[n].number);
	printf("Email: ");
	scanf("%s", directory[n].email);
	printf("Group: ");
	scanf("%s", directory[n].group);
	n++;
	printf("%s",directory);
	printf("%s was added successfully.", directory[n].name);
}

void add(char* name, char* number, char* email, char* group) {
	 
}

int search(char * argument) {
	for(int i = 0; i < n; i++){
		if (strcmp(directory[i].name, argument) == 0)
			return i;
	}
	return -1;
}

void find(char* argument) {
	int index = search(argument);
	if (index == -1)
		printf("No person names '%s' exists.");
	else {
		printf("%s\n:", directory[index].name);
		printf("   Phone: %s\n", directory[index].number);
		printf("   Email: %s\n", directory[index].email);
		printf("   Group: %s\n", directory[index].group);
	}
}