//문장의 앞과 뒤에 붙은 공백문자들은 제거하고, 단어 사이에 두 개 이상의 연속된 공백 문자들은 하나의 공백 문자로 대체하라.
#define MAX 100
#include <stdio.h>
#include <string.h>
#include <ctype.h> //isspace library 포함

int readline(char compressed[], int limit);

int main() {
	char line[MAX];

	//공백 포함 문자열 입력받기
	while (1) {
		printf("$ ");
		int length = readline(line, MAX);
		printf("%s:%d", line, length);
	}
	return 0;

	int readline(char compressed[], int limit) {
		int ch, i = 0;

		while ((ch = getchar()) != '\n') { //문자열이 끝나기 전까지
			if (i < limit - 1 && (!isspace(ch) || i > 0 && isspace(compressed[i - 1]))) //공백이 아니거나 처음이아니고 직전이 공백이 아니어야함.
				compressed[i++] = ch;
		}
		if (i > 0 && isspace(compressed[i - 1])) //적어도 하나 이상의 문자가 저장되어 있고, 마지막 문자가 공백이라면
			i--;
		compressed[i] = '\0'; //마지막 문자 개행키로 채우기
		return i; //최종 길이 반환
	}