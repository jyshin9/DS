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

//함수 프로토타입(사용자 지정함수) 선언
void add();
void find();
void status();
void deleteNode();

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
			deleteNode();
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			printf("Invalid command. Please enter a valid command.\n");
			// 입력 버퍼 비우기
			while (getchar() != '\n') {}
		}
	}
	return 0;
}

void add() {
	//전화번호부가 꽉 찼다면
	if (n >= CAPACITY) { 
		printf("Phonebook is full. Cannot add more entries.\n");
		return;
	}
	char buff1[WORDS], buff2[WORDS]; //names라는 스택(heap)에 저장되므로,, add함수가 리턴되면 소멸됨
	scanf("%s", buff1); //이름
	scanf("%s", buff2); //전화번호

	names[n] = _strdup(buff1); //새로운 배열을 할당받기 위하여 strdup 사용
	numbers[n] = _strdup(buff2); //names, numbers..에는 새로 할당된 배열의 주소가 저장
	n++; //새로운 사람이 한명 추가되었기 때문
	
	printf("%s was added successfully.\n", buff1);
}

void find() {
	char* buff[WORDS];
	int num;
	scanf("%s", buff); //찾고자하는 이름 입력
	
	bool is_there = false;

	for (int i = 0; i < n; i++) {
		if (strcmp(buff, names[i]) == 0) { //names 배열에 찾고자하는 이름이 존재한다면
			is_there = true;
			printf("%s\n", numbers[i]);
			break;
		}
	}
	if (!is_there)
		printf("No person named '%s' exists.\n", buff);
}

void status() {
	for (int i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}

void deleteNode() {
	char name[WORDS]; //지우고자 하는 이름
	scanf("%s", name);

	int index = -1; //지우고자 하는 이름의 인덱스값
	bool is_there = false;

	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0)
			is_there = true;
			index = i;
			break;
	}
	if (is_there) { //지울 대상이 전화번호부에 존재한다면
		free(names[index]);
		free(numbers[index]);
		for (int j = index; j < n; j++) { //해당 이름, 전화번호 삭제
			names[j] = names[j + 1];
			numbers[j] = numbers[j + 1];
		}
		n--; //한명을 제거했으니 명 수 줄이기
		printf("%s was deleted successfully.\n", name);
	}
	else 
		printf("No person named '%s' exists.\n", name);
}