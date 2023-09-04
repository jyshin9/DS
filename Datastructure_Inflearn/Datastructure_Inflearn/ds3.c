//������ �հ� �ڿ� ���� ���鹮�ڵ��� �����ϰ�, �ܾ� ���̿� �� �� �̻��� ���ӵ� ���� ���ڵ��� �ϳ��� ���� ���ڷ� ��ü�϶�.
#define MAX 100
#include <stdio.h>
#include <string.h>
#include <ctype.h> //isspace library ����

int readline(char compressed[], int limit);

int main() {
	char line[MAX];

	//���� ���� ���ڿ� �Է¹ޱ�
	while (1) {
		printf("$ ");
		int length = readline(line, MAX);
		printf("%s:%d", line, length);
	}
	return 0;

	int readline(char compressed[], int limit) {
		int ch, i = 0;

		while ((ch = getchar()) != '\n') { //���ڿ��� ������ ������
			if (i < limit - 1 && (!isspace(ch) || i > 0 && isspace(compressed[i - 1]))) //������ �ƴϰų� ó���̾ƴϰ� ������ ������ �ƴϾ����.
				compressed[i++] = ch;
		}
		if (i > 0 && isspace(compressed[i - 1])) //��� �ϳ� �̻��� ���ڰ� ����Ǿ� �ְ�, ������ ���ڰ� �����̶��
			i--;
		compressed[i] = '\0'; //������ ���� ����Ű�� ä���
		return i; //���� ���� ��ȯ
	}