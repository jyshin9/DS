//phonebook02 = phonebook01 + 파일로 저장(save)하고 로드(load)하기, 알파벳 순으로 정렬
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 100

char* names[CAPACITY]; 
char* numbers[CAPACITY];
int n = 0; 

void add();
void find();
void status();
void remove();
void load();
void save();

int main() {
	char command[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0)
			add();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0)
			remove();
		else if (strcmp(command, "save") == 0)
			save();
		else if (strcmp(command, "read") == 0)
			load();
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}

void load() {
	char fileName[BUFFER_SIZE]; //입력받은 파일의 이름을 저장
	scanf("%s", fileName); //불러올 파일 이름을 입력받는다

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
		names[n] = strdup(buf1); //이름
		numbers[n] = strdup(buf2); //전화번호
		n++;
	}
	fclose(fp); //볼일이 끝난 파일은 반드시 닫아주어야 함.
}

void save() {
	char fileName[BUFFER_SIZE]; //파일을 다음 이름으로 저장
	char tmp[BUFFER_SIZE];
	
	scanf("%s", tmp); //as임. 그냥 입력용. 후에 버림
	scanf("%s", fileName);

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

void add() {
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1); //이름
	scanf("%s", buf2); //전화번호

	int i = n - 1;
	while (n > 0 && strcmp(buf1, names[i]) < 0) { //buf가 더 작을 때(알파벳이 더 작을 때)
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i] = strdup(buf1);
	numbers[i] = strdup(buf2);
	n++;
	
	printf("%s was added successfully,\n", buf1);
}

void status() {
	int i = n-1; //마지막 사람의 인덱스. 
	
	for (i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}

void remove() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	int i = index;
	for (; i < n - 1; i++) {
		names[i] = names[i+1];
		numbers[i] = numbers[i+1];
	}
	n--;

	printf("No person named '%s' exists.\n", buf);
}

int search(char* name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(names[i], name) == 0) {
			return i;
		}
	}
	return -1;
}

void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(buf, names[i]) == 0) {
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("No person named '%s' exist.\n", buf);
}

void status() {
	int i;
	for (i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}