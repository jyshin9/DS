//�������� �ܾ���� �����͸� �̿��Ͽ� �Ʒ� �׸��� ���� �����غ���.
#define CRT_SECURE_NO_WARNINGS

#define BUFFER_SIZE 100
#include <stdio.h>
#include <string.h>

int main() {
	char* words[100]; //words�迭�� ������ �迭�� �ּҸ� �����ؾ���.
	int n = 0;
	char buffer[BUFFER_SIZE];

	while (n < 4 && scanf("%s", buffer) != EOF) { //&buffer�̶�� ���ص� �Ǵ� ����: buffer�� �̸��� ���� buffer�� �����ͺ����̱� ����
		words[n] = _strdup(buffer); //buffer���� words�� ����
		n++;
	}
	for (int i = 0; i < 4; i++) {
		printf("%s\n", words[i]);
	}
}