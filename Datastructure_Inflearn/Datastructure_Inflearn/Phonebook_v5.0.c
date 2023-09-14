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

int main() {
	char command_line[BUFFER_SIZE];
	char* command, * argument; //명령어와 명령내용
	char name_str[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0)
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
			if (compose_name(name_str, BUFFER_SIZE) <= 0) {
				printf("Name required.\n");
				continue;
			}
			add_div(name_str);
		}
		else if (strcmp(command, "find") == 0) {
			if (compose_name(name_str, BUFFER_SIZE) <= 0) {
				printf("Name required.\n");
				continue;
			}
			find(name_str);
		}
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0) {
			if (compose_name(name_str, BUFFER_SIZE) <= 0) {
				printf("Invalid argument.\n");
				continue;
			}
			remove(name_str);
		}
		else if (strcmp(command, "save") == 0) {
			argument = strtok(command, " ");
			if (strcmp(argument, "as") != 0) { //두번째 토큰이 as이어야 함
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

void add_div(char* name) {
	char number[BUFFER_SIZE], email[BUFFER_SIZE], group[BUFFER_SIZE];
	char empty[] = " "; //입력값이 없을 때

	printf("   Phone: ");
	read_line(stdin, number, BUFFER_SIZE);
	printf("   Email: ");
	read_line(stdin, email, BUFFER_SIZE);
	printf("   Group: ");
	read_line(stdin, group, BUFFER_SIZE);

	//존재하지 않는 항목들을 하나의 공백문자로 구성된 문자열로 대체한다. <<대박이당~~
	add(name, (char*)(strlen(number) > 0 ? number : empty),
		(char*)(strlen(email) > 0 ? email : empty),
		(char*)(strlen(group) > 0 ? group : empty));
}

int compose_name(char str[], int limit) { //이름을 담아둘 배열 str
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " "); //이름 성
	if (ptr == NULL) return 0;

	strcpy(str, ptr);
	length += strlen(str);

	while ((ptr = strtok(NULL, " ")) != NULL) {
		if (length + strlen(ptr) + 1 < limit) { //+1을 하는 이유는 끝에 '\0'을 넣기 위함
			str[length++] = ' ';
			str[length] = '\0'; //문자열 마지막에 '\0'(Null chracter)추가
			strcat(str, ptr); //문자열 연결 함수
			length += strlen(ptr);
		}
	}
	return length;
}

//초기설정
void init() {
	directory = (Person**)malloc(sizeof(Person*) * INIT_CAPACITY);
	capacity = INIT_CAPACITY;
	n = 0;
}

//재할당
void reallocate() {
	capacity *= 2;
	//임시 배열 tmp 선언
	Person** tmp = (Person**)malloc(capacity * sizeof(Person*));
	for (int i = 0; i < n; i++)
		tmp[i] = directory[i];
	free(directory);
	directory = tmp;
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
			number = NULL; //존재하지 않는 항목을 명시적으로 NULL로 표시
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
	if (n >= capacity)
		reallocate();
	
	//앞으로 한칸씩 당기며 알파벳순으로 정렬
	int i = n - 1;
	while (i >= 0 && strcmp((*directory[i]).name, name) > 0) {
		directory[i + 1] = directory[i]; //directory는 포인터일뿐!
		i--;
	} 

	directory[i + 1] = (Person*)malloc(sizeof(Person));

	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;

	n++; //인원수증가
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

int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, directory[i]->name) == 0)
			return i;
	}
	return -1;
}

void find(char* name) {
	int i = search(name);
	if (i == -1) {
		printf("No person names '%s' exists.", name);
		return;
	}
	Person* p = directory[i];
	printf("%s:\n", directory[i]->name);
	printf("   Phone: %s\n", directory[i]->number);
	printf("   Email: %s\n", directory[i]->email);
	printf("   Group: %s\n", directory[i]->group);
}

void remove(char* name) {
	int i = search(name);
	if(i == -1) {
		printf("No person names '%s' exists.", name);
		return;
	}
	//directory[i]는 내가 찾은 Person객체를 저장하는 포인터
	Person* p = directory[i];
	for (int j = 0; i < n; j++) 
		directory[j] = directory[j + 1];
	n--;
	release_person(p);
	printf("'%s' was deleted successfully.\n", name);
}

void release_person(Person* p) {
	free(p->name);
	if (p->number != NULL) free(p->number);
	if (p->email != NULL) free(p->email);
	if (p->group != NULL) free(p->group);
	free(p);
}

void save(char* name) {
	FILE* fp = fopen(name, "w");
	if (fp == NULL) {
		printf("Open failed");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[n]->name);
		fprintf(fp, "%s#", directory[n]->number);
		fprintf(fp, "%s#", directory[n]->email);
		fprintf(fp, "%s#", directory[n]->group);
	}
	fclose(fp);
}