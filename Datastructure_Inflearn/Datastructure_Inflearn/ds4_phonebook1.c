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

//�Լ� ������Ÿ��(����� �����Լ�) ����
void add();
void find();
void status();
void deleteNode();

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
			deleteNode();
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			printf("Invalid command. Please enter a valid command.\n");
			// �Է� ���� ����
			while (getchar() != '\n') {}
		}
	}
	return 0;
}

void add() {
	//��ȭ��ȣ�ΰ� �� á�ٸ�
	if (n >= CAPACITY) { 
		printf("Phonebook is full. Cannot add more entries.\n");
		return;
	}
	char buff1[WORDS], buff2[WORDS]; //names��� ����(heap)�� ����ǹǷ�,, add�Լ��� ���ϵǸ� �Ҹ��
	scanf("%s", buff1); //�̸�
	scanf("%s", buff2); //��ȭ��ȣ

	names[n] = _strdup(buff1); //���ο� �迭�� �Ҵ�ޱ� ���Ͽ� strdup ���
	numbers[n] = _strdup(buff2); //names, numbers..���� ���� �Ҵ�� �迭�� �ּҰ� ����
	n++; //���ο� ����� �Ѹ� �߰��Ǿ��� ����
	
	printf("%s was added successfully.\n", buff1);
}

void find() {
	char* buff[WORDS];
	int num;
	scanf("%s", buff); //ã�����ϴ� �̸� �Է�
	
	bool is_there = false;

	for (int i = 0; i < n; i++) {
		if (strcmp(buff, names[i]) == 0) { //names �迭�� ã�����ϴ� �̸��� �����Ѵٸ�
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
	char name[WORDS]; //������� �ϴ� �̸�
	scanf("%s", name);

	int index = -1; //������� �ϴ� �̸��� �ε�����
	bool is_there = false;

	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0)
			is_there = true;
			index = i;
			break;
	}
	if (is_there) { //���� ����� ��ȭ��ȣ�ο� �����Ѵٸ�
		free(names[index]);
		free(numbers[index]);
		for (int j = index; j < n; j++) { //�ش� �̸�, ��ȭ��ȣ ����
			names[j] = names[j + 1];
			numbers[j] = numbers[j + 1];
		}
		n--; //�Ѹ��� ���������� �� �� ���̱�
		printf("%s was deleted successfully.\n", name);
	}
	else 
		printf("No person named '%s' exists.\n", name);
}