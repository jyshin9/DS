//phonebook03 | �迭 ���Ҵ�, ���� ���� �Է°� ���ڿ� tokenizing
//����� ����� ���� �迭�� ũ�⸦ �ʰ��� ��� ���� �޸� �Ҵ����� �迭�� ũ�⸦ Ű���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define INIT_CAPACITY 3
#define BUFFER_SIZE 50

//char * Ÿ���� �迭�� �̸��̹Ƿ� char ** Ÿ���� ������
char ** names;
char ** numbers;

char* delim = " ";

int capacity = INIT_CAPACITY; //�迭�� ũ��
int n = 0; //��� ��

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
	init_directory(); //�����޸��Ҵ�
	proccess_command(); //��ȭ��ȣ��

	return 0;
}

void process_command() {
	char command_line[BUFFER_SIZE]; //�� ������ ��°�� �о���� ���� ����
	char* command; //��ɾ�
	char* argument1; //�ι�°
	char* argument2; //����°

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0) //�ۼ��� ������ ���ٸ�
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
	//�Ҵ��� �޸��� byte���� ����
	//���� ���ڷ� �����ϴ� �ͺ��� sizeof �����ڸ� ����ϴ� ���� �ٶ�����.
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

//���Ҵ�
void reallocate() {
	int i;
	capacity *= 2; //ũ�⸦ �ι�� �ø�
	
	char ** tmp1 = (char**)malloc(capacity * sizeof(char*)); //�ӽ� �Ҵ� ����1
	char ** tmp2 = (char**)malloc(capacity * sizeof(char*)); //�ӽ� �Ҵ� ����1

	for (i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	//�����޸��Ҵ����� ������� �迭�� �׳� �θ� �������� �ʴ� �޸�(garbage).
	//garbage�� free�Լ��� �̿��Ͽ� ��ȯ.
	free(names);
	free(numbers);

	//�����ͺ��� names�� numbers�� ���ο� �迭�� ����Ű���� �ϱ�
	names = tmp1;
	numbers = tmp2;
}

int read_line(char str[], int limit) { //limit: �迭 str�� ũ��
	int ch, i = 0;

	while ((ch = getchar()) != '\n') { //�ѱ��ھ� �Է¹ޱ�
		if (i < limit - 1)
			str[i++] = ch; //ch�� str[i]�� ���Ե� ���Ŀ� i���� 1 ����
	}
	str[i] = '\0'; //�������� null character('\0')�� �߰�

	return i; //���� ���ڼ� ��ȯ
}

void load(char *fileName) {
	char buf1[BUFFER_SIZE]; //�̸�
	char buf2[BUFFER_SIZE]; //��ȭ��ȣ

	//fopen(���� �̸�, "���� ���")
	FILE* fp = fopen(fileName, "r"); //���� ������ fp ����
	if (fp == NULL) {
		printf("Open failed.\n");
		return; //�Լ� Ż��
	}
	//������ ���������� ��!!! �׸��� ���Ϸκ��� ������ �о����
	while ((fscanf(fp, "%s", buf1) != EOF)) { //������ ���� ������ ������ �����͸� �о �迭�� ����
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp); //������ ���� ������ �ݵ�� �ݾ��־�� ��.
}

void save(char * fileName) {
	FILE* fp = fopen(fileName, "w"); //�������Ͽ� write���� ��
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	//������ ����ϱ�(����)
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]); //fp: � ���Ͽ� ������ �ϴ���
	}
	fclose(fp);
}

void add(char * name, char * number) {
	if (n >= capacity) //�迭�� ����
		reallocate(); 

	int i = n - 1;
	while (n > 0 && strcmp(name, names[i]) < 0) { //buf�� �� ���� ��(���ĺ��� �� ���� ��)
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
	int i = n - 1; //������ ����� �ε���. 

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