//������ �����Ͽ� ���ڿ��� �а� �� ���̸� ����ϴ� ���α׷�
#define BUFFER_SIZE 20
#include <stdio.h>
#include <string.h>

int main(void) {
	char buffer[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		//fgets(buffer, BUFFER_SIZE, stdin); //fgets(�о�õ����͸������ҸŹ���, ������ũ��, ����������(stdin)  
		//buffer[strlen(buffer) - 1] = '\0';
		readline(buffer, BUFFER_SIZE);
		printf("%s:%d\n", buffer, strlen(buffer));
	}
	return 0;
}

//readline �Լ� �����
int readline(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n') { //getchar�Լ��� �̿��Ͽ� �ѱ��ھ� ���� -> ch�� ���                                                                                 
		if (i < limit - 1) { //�������� null�� �߰��ؾ� ��
			str[i] = ch; //int��
			i++;
		}
	}
	str[i] = '\0'; //���ڿ� ������ �κ� '\0'�� ä���
	return i; //���ڿ� ũ�� ����
}