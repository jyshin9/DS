//phonebook03 | 배열 재할당, 라인 단위 입력과 문자열 tokenizing
//저장된 사람의 수가 배열의 크기를 초과할 경우 동적 메모리 할당으로 배열의 크기를 키운다
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

//char * 타입의 배열의 이름이므로 char ** 타입의 변수임
char ** names;
char ** numbers;

char* delim = " ";

int capacity = INIT_CAPACITY; //배열의 크기
int n = 0; //사람 수

void init_directory();
int read_line(char * str, int limit);
void process_command();
void add();
void find();
void status();
void remove();
void load(char* fileName);
void save();
void reallocate();

int main() {
	init_directory(); //동적메모리할당
	proccess_command(); //전화번호부

	return 0;
}

void process_command() {
	char command_line[BUFFER_SIZE]; //한 라인을 통째로 읽어오기 위한 버퍼
	char* command; //명령어
	char* argument1; //두번째
	char* argument2; //세번째

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0) //작성한 내용이 없다면
			continue;
		command = strtok(command_line, delim);
		if (command == NULL) continue;

		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("File name required.\n");
				continue;
			}
			load(argument1);
		}

		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);
			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			add(argument1, argument2);
			printf("%s was added successfully", argument1);
		}

		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid argument.\n");
				continue;
			}
			find(argument1);
		}

		else if (strcmp(command, "status") == 0)
			status();

		else if (strcmp(command, "remove") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid argument.\n");
				continue;
			}
			remove(argument1);
		}
		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);
			if (argument1 == NULL || strcmp(argument1, "as") != 0 || argument2 == NULL) {
				printf("Invalid command format.\n");
				continue;
			}
			save(argument2);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

void init_directory() {
	//할당할 메모리의 byte수를 지정
	//직접 숫자로 지정하는 것보다 sizeof 연산자를 사용하는 것이 바람직함.
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

//재할당
void reallocate() {
	int i;
	capacity *= 2; //크기를 두배로 늘림
	
	char ** tmp1 = (char**)malloc(capacity * sizeof(char*)); //임시 할당 버퍼1
	char ** tmp2 = (char**)malloc(capacity * sizeof(char*)); //임시 할당 버퍼1

	for (i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	//동적메모리할당으로 만들어진 배열은 그냥 두면 없어지지 않는 메모리(garbage).
	//garbage는 free함수를 이용하여 반환.
	free(names);
	free(numbers);

	//포인터변수 names와 numbers가 새로운 배열을 가리키도록 하기
	names = tmp1;
	numbers = tmp2;
}

int read_line(char str[], int limit) { //limit: 배열 str의 크기
	int ch, i = 0;

	while ((ch = getchar()) != '\n') { //한글자씩 입력받기
		if (i < limit - 1)
			str[i++] = ch; //ch가 str[i]에 대입된 이후에 i값이 1 증가
	}
	str[i] = '\0'; //마지막에 null character('\0')값 추가

	return i; //읽은 글자수 반환
}

void load(char *fileName) {
	char buf1[BUFFER_SIZE]; //이름
	char buf2[BUFFER_SIZE]; //전화번호

	//fopen(파일 이름, "접근 방식")
	FILE* fp = fopen(fileName, "r"); //파일 포인터 fp 선언
	if (fp == NULL) {
		printf("Open failed.\n");
		return; //함수 탈출
	}
	//파일을 성공적으로 엶!!! 그리고 파일로부터 데이터 읽어오기
	while ((fscanf(fp, "%s", buf1) != EOF)) { //파일의 끝에 도달할 때까지 데이터를 읽어서 배열에 저장
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp); //볼일이 끝난 파일은 반드시 닫아주어야 함.
}

void save(char * fileName) {
	FILE* fp = fopen(fileName, "w"); //쓰기위하여 write모드로 엶
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	//데이터 출력하기(쓰기)
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]); //fp: 어떤 파일에 쓸려고 하느냐
	}
	fclose(fp);
}

void add(char * name, char * number) {
	if (n >= capacity) //배열이 꽉참
		reallocate(); 

	int i = n - 1;
	while (n > 0 && strcmp(name, names[i]) < 0) { //buf가 더 작을 때(알파벳이 더 작을 때)
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i] = strdup(name);
	numbers[i] = strdup(number);
	n++;

	printf("%s was added successfully,\n", name);
}

void status() {
	int i = n - 1; //마지막 사람의 인덱스. 

	for (i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}

void remove(char * name) {
	int index = search(name);
	if (index == -1) {
		printf("No person named '%s' exists.\n", name);
		return;
	}
	int i = index;
	for (; i < n - 1; i++) {
		names[i] = names[i + 1];
		numbers[i] = numbers[i + 1];
	}
	n--;

	printf("No person named '%s' exists.\n", name);
}

int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], name) == 0) {
			return i;
		}
	}
	return -1;
}

void find(char* name) {
	int index = search(name);
	if (index == -1)
		printf("No person named '%s' exist.\n", name);
	else
		printf("%s\n", numbers[index]);
	
}

void status() {
	int i;
	for (i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}