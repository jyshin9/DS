//phonebook05 | ����ü�� ���� ������, ���� �޸� �Ҵ�
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
int n; //�ּҷ� �� ��
int capacity;

int main() {
	char command_line[BUFFER_SIZE];
	char* command, * argument; //��ɾ�� ��ɳ���
	char name_str[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_SIZE) <= 0)
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

void add_div(char* name) {
	char number[BUFFER_SIZE], email[BUFFER_SIZE], group[BUFFER_SIZE];
	char empty[] = " "; //�Է°��� ���� ��

	printf("   Phone: ");
	read_line(stdin, number, BUFFER_SIZE);
	printf("   Email: ");
	read_line(stdin, email, BUFFER_SIZE);
	printf("   Group: ");
	read_line(stdin, group, BUFFER_SIZE);

	//�������� �ʴ� �׸���� �ϳ��� ���鹮�ڷ� ������ ���ڿ��� ��ü�Ѵ�. <<����̴�~~
	add(name, (char*)(strlen(number) > 0 ? number : empty),
		(char*)(strlen(email) > 0 ? email : empty),
		(char*)(strlen(group) > 0 ? group : empty));
}

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

//�ʱ⼳��
void init() {
	directory = (Person**)malloc(sizeof(Person*) * INIT_CAPACITY);
	capacity = INIT_CAPACITY;
	n = 0;
}

//���Ҵ�
void reallocate() {
	capacity *= 2;
	//�ӽ� �迭 tmp ����
	Person** tmp = (Person**)malloc(capacity * sizeof(Person*));
	for (int i = 0; i < n; i++)
		tmp[i] = directory[i];
	free(directory);
	directory = tmp;
}

//���� ���ڼ� ��ȯ
int read_line(FILE *fp, char str[], int limit) {
	int ch; //�о�� ���ڸ� ����
	int i; //���ڼ�

	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i > n)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void load(char* fileName) {
	char buff[INIT_CAPACITY]; //�ҷ��� ������ ����
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
			number = NULL; //�������� �ʴ� �׸��� ��������� NULL�� ǥ��
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
	
	//������ ��ĭ�� ���� ���ĺ������� ����
	int i = n - 1;
	while (i >= 0 && strcmp((*directory[i]).name, name) > 0) {
		directory[i + 1] = directory[i]; //directory�� �������ϻ�!
		i--;
	} 

	directory[i + 1] = (Person*)malloc(sizeof(Person));

	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;

	n++; //�ο�������
}

//�����ϰ� ���� �Ȱ���
void status() {
	for (int i; i < n; i++) 
		print_person(directory[i]);
	printf("Total %d persons.\n", n);
}

void print_person(Person *p) {//Person�� �ּҰ�, �� directory[i]���� �����
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
	//directory[i]�� ���� ã�� Person��ü�� �����ϴ� ������
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