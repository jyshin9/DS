//phonebook01
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h> //strcmp ���̺귯�� ����
#include <stdbool.h> //boolean Ÿ�� ����

#define CAPACITY 100
#define WORDS 20

//�������� ����
char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0; //���� ����Ǿ� �ִ� ��� ��

void add();
void find();
void status();
void delete();

int main() {
	while (1) { //�Է��� ��� �޾ƾ���
		char command[WORDS];
		printf("$ ");
		scanf("%s", command); //add, find ���� ��ɾ ����.

		if (strcmp(command, "add") == 0) //strcmp�� �� ���ڿ��� �����ϸ� 0�� ��ȯ
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
	char buff1[WORDS], buff2[WORDS]; //names��� ����(heap)�� ����ǹǷ�,, add�Լ��� ���ϵǸ� �Ҹ��
	scanf("%s", buff1); //�̸�
	scanf("%s", buff2); //��ȭ��ȣ

	names[n] = strdup(buff1); //���ο� �迭�� �Ҵ�ޱ� ���Ͽ� strdup ���
	numbers[n] = strdup(buff2); //names, numbers..���� ���� �Ҵ�� �迭�� �ּҰ� ����
	n++; //���ο� ����� �Ѹ� �߰��Ǿ��� ����

	printf("%s was added successfully.\n", buff1);

	return 0;
}

void find() {
	char* buff[WORDS];
	scanf("%s", buff); //ã�����ϴ� �̸� �Է�
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
	char name[WORDS]; //������� �ϴ� �̸�
	int index; //������� �ϴ� �̸��� �ε�����
	scanf("%s", name);

	bool is_there = false;

	for (int i = 0; i < n; i++) {
		if (names[i] == name)
			is_there = true;
		index = i;
	}
	if (is_there == true) { //���� ����� ��ȭ��ȣ�ο� �����Ѵٸ�
		for (int j = index; j < n; j++) { //�ش� �̸�, ��ȭ��ȣ ����
			names[j] = names[j + 1];
			numbers[j] = numbers[j + 1];
		}
		printf("No person named '%s' exists.\n", name);
	}
	else if (is_there == false) {
		printf("%s was deleted successfully.\n", name);
	}
}