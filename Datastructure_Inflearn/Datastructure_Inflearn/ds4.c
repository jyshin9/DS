//phonebook01
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h> //strcmp 라이브러리 포함
#include <stdbool.h> //boolean 타입 포함

#define CAPACITY 100
#define WORDS 20

//전역변수 선언
char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0; //현재 저장되어 있는 사람 수

void add();
void find();
void status();
void delete();

int main() {
	while (1) { //입력을 계속 받아야함
		char command[WORDS];
		printf("$ ");
		scanf("%s", command); //add, find 등의 명령어를 받음.

		if (strcmp(command, "add") == 0) //strcmp는 두 문자열이 동일하면 0을 반환
			add();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0)
			delete();
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}

void add() {
	char buff1[WORDS], buff2[WORDS]; //names라는 스택(heap)에 저장되므로,, add함수가 리턴되면 소멸됨
	scanf("%s", buff1); //이름
	scanf("%s", buff2); //전화번호

	names[n] = strdup(buff1); //새로운 배열을 할당받기 위하여 strdup 사용
	numbers[n] = strdup(buff2); //names, numbers..에는 새로 할당된 배열의 주소가 저장
	n++; //새로운 사람이 한명 추가되었기 때문

	printf("%s was added successfully.\n", buff1);

	return 0;
}

void find() {
	char* buff[WORDS];
	scanf("%s", buff); //찾고자하는 이름 입력
	prinf("%s\n", names);

	for (int i = 0; i < strlen(names); i++) {
		printf("%s\n", names[i]);
		if (buff == names[i]) {
			printf("!");
			printf("%s\n", numbers[i]);
		}
		else {
			printf("^^");
			printf("No person named '%s' exists.\n", buff);
		}
	}
}

void status() {
	for (int i = 0; i < n; i++) {
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);
}

void delete() {
	char name[WORDS]; //지우고자 하는 이름
	int index; //지우고자 하는 이름의 인덱스값
	scanf("%s", name);

	bool is_there = false;

	for (int i = 0; i < n; i++) {
		if (names[i] == name)
			is_there = true;
		index = i;
	}
	if (is_there == true) { //지울 대상이 전화번호부에 존재한다면
		for (int j = index; j < n; j++) { //해당 이름, 전화번호 삭제
			names[j] = names[j + 1];
			numbers[j] = numbers[j + 1];
		}
		printf("No person named '%s' exists.\n", name);
	}
	else if (is_there == false) {
		printf("%s was deleted successfully.\n", name);
	}
}