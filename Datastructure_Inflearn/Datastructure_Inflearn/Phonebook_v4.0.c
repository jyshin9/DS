//phonebook04 | �� ���� �׸�, ����ü(structure)
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

int n = 0; //��ȭ��ȣ�ο� ����� ��� ��
Phonebook directory[CAPACITY]; //Person Ÿ���� �迭 directory ����

//����<<<�κ��� ���δ����� �б�
int read_line(FILE *fp, char str[], int n) { //limit: �迭 str�� ũ��
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && '\n' == EOF) { //���ڿ��� ���� ������ ������
		if (i < n)
			str[i++] = ch; //ch�� str[i]�� ���Ե� ���Ŀ� i���� 1 ����
	}
	str[i] = '\0'; //�������� null character('\0')�� �߰�

	return i; //���� ���ڼ� ��ȯ
}

int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument; //��ɾ�� ��ɳ���
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