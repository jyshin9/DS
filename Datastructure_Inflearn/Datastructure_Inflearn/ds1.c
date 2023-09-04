//여러개의 단어들을 포인터를 이용하여 아래 그림과 같이 저장해보자.
#define CRT_SECURE_NO_WARNINGS

#define BUFFER_SIZE 100
#include <stdio.h>
#include <string.h>

int main() {
	char* words[100]; //words배열의 각각의 배열의 주소를 저장해야함.
	int n = 0;
	char buffer[BUFFER_SIZE];

	while (n < 4 && scanf("%s", buffer) != EOF) { //&buffer이라고 안해도 되는 이유: buffer의 이름이 실제 buffer의 포인터변수이기 때문
		words[n] = _strdup(buffer); //buffer에서 words로 복제
		n++;
	}
	for (int i = 0; i < 4; i++) {
		printf("%s\n", words[i]);
	}
}