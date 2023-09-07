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

int capacity = INIT_CAPACITY; //�迭�� ũ��
int n = 0; //��� ��

void init_directory();
void add();
void find();
void status();
void remove();
void load();
void save();

int main() {
	init_directory();
	proccess_command();

	return 0;
}

void init_directory() {
	//�Ҵ��� �޸��� byte���� ����
	//���� ���ڷ� �����ϴ� �ͺ��� sizeof �����ڸ� ����ϴ� ���� �ٶ�����.
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*));
}

void load() {
	char fileName[BUFFER_SIZE]; //�Է¹��� ������ �̸��� ����
	scanf("%s", fileName); //�ҷ��� ���� �̸��� �Է¹޴´�

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
		names[n] = strdup(buf1); //�̸�
		numbers[n] = strdup(buf2); //��ȭ��ȣ
		n++;
	}
	fclose(fp); //������ ���� ������ �ݵ�� �ݾ��־�� ��.
}

void save() {
	char fileName[BUFFER_SIZE]; //������ ���� �̸����� ����
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp); //as��. �׳� �Է¿�. �Ŀ� ����
	scanf("%s", fileName);

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

void add() {
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1); //�̸�
	scanf("%s", buf2); //��ȭ��ȣ

	int i = n - 1;
	while (n > 0 && strcmp(buf1, names[i]) < 0) { //buf�� �� ���� ��(���ĺ��� �� ���� ��)
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
	int i = n - 1; //������ ����� �ε���. 

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
		names[i] = names[i + 1];
		numbers[i] = numbers[i + 1];
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