//phonebook04 | �� ���� �׸�, ����ü(structure)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define BUFFER_LENGTH 100

void save(char*);
int compose_name(char, int);
int read_line(FILE*, char, int );
void load(char*);
void status();
void add_div(char*);
void add(char*, char*, char*, char*);
int search(char*);
void find(char*);
int remove(char*);

//��ȭ��ȣ�� ����ü ����
typedef struct phonebook {
	char* name;
	char* number;
	char* email;
	char* group;
}Phonebook;

int n = 0; //��ȭ��ȣ�ο� ����� ��� ��
Phonebook directory[CAPACITY]; //Phonebook Ÿ���� �迭 directory ����

int main() {
	char command_line[BUFFER_LENGTH];
	char* command, * argument; //��ɾ�� ��ɳ���
	char name_str[BUFFER_LENGTH];
	
	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue; //input�� �ƹ��͵� ���ٸ�

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
			if (strcmp(argument, "as") != 0) { //�ι�° ��ū�� as�̾�� ��
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
	FILE* fp = fopen(argument, "w");
	if (fp == NULL) {
		printf("Open failed");
		return;
	}
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s#", directory[n].name);
		fprintf(fp, "%s#", directory[n].number);
		fprintf(fp, "%s#", directory[n].email);
		fprintf(fp, "%s#", directory[n].group);
	}
	fclose(fp);
}

//�̸��� ���̸� ��ȯ
//add_div, find, delete�� ���
int compose_name(char str[], int limit) { //�̸��� ��Ƶ� �迭 str
	char* ptr;
	int length = 0;

	ptr = strtok(NULL, " "); //�̸� ��
	if (ptr == NULL) return 0;
	
	strcpy(str, ptr);
	length += strlen(str);

	while ((ptr = strtok(NULL, " ")) != NULL) {
		if (length + strlen(ptr) + 1 < limit) { //+1�� �ϴ� ������ ���� '\0'�� �ֱ� ����
			str[length++] = ' ';
			str[length] = '\0'; //���ڿ� �������� '\0'(Null chracter)�߰�
			strcat(str, ptr); //���ڿ� ���� �Լ�
			length += strlen(ptr);
		}
	}
	return length;
}

//����<<<�κ��� ���δ����� �б�
int read_line(FILE* fp, char str[], int n) { //limit: �迭 str�� ũ��
	int ch, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) { //���ڿ��� ���� ������ ������
		if (i < n) //�����÷ο� ����
			str[i++] = ch; //ch�� str[i]�� ���Ե� ���Ŀ� i���� 1 ����
	}
	str[i] = '\0'; //�������� null character('\0')�� �߰�
	return i; //���� ���ڼ� ��ȯ
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

void status() {
	for (int i = 0; i < n; i++) {
		find(directory[i].name);
	printf("Total %d persons.\n", n);
	}
}

void add_div(char *name) {
	char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
	char empty[] = " "; //�Է°��� ���� ��

	printf("   Phone: ");
	read_line(stdin, number, BUFFER_LENGTH);
	printf("   Email: ");
	read_line(stdin, email, BUFFER_LENGTH);
	printf("   Group: ");
	read_line(stdin, group, BUFFER_LENGTH);

	//�������� �ʴ� �׸���� �ϳ��� ���鹮�ڷ� ������ ���ڿ��� ��ü�Ѵ�. <<����̴�~~
	add(name, (char*)(strlen(number) > 0 ? number : empty),
			(char*)(strlen(email) > 0 ? email : empty),
			(char*)(strlen(group) > 0 ? group : empty));
}

//�߰� �� ���ĺ� ������ ����
void add(char* name, char* number, char* email, char* group) {
	int i = n - 1;
	if (i >= 0 && strcmp(directory[i].name, name) > 0) { //directory[i].name > name
		directory[i + 1] = directory[i];
		i--;
	}
	directory[i + 1].name = _strdup(name);
	directory[i + 1].number = _strdup(number);
	directory[i + 1].email = _strdup(email);
	directory[i + 1].group = _strdup(group);

	printf("%s was added successfully.", directory[n].name);
	n++;
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
	if (index == -1) {
		printf("No person names '%s' exists.");
		return;
	}
	else {
		printf("%s:\n", directory[index].name);
		printf("   Phone: %s\n", directory[index].number);
		printf("   Email: %s\n", directory[index].email);
		printf("   Group: %s\n", directory[index].group);
	}
}

int remove(char* argument) {
	int index = search(argument);
	if (index == -1) {
		printf("No person names '%s' exists.");
		return;
	}
	else {
		int j = index;
		for (; j < n - 1; j++) {
			directory[j] = directory[j + 1];
		}
		n--;
		printf("'%s' was deleted successfully.\n", argument);
	}
}