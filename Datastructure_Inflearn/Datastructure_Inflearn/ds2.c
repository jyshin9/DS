//공백을 포함하여 문자열을 읽고 그 길이를 출력하는 프로그램
#define BUFFER_SIZE 20
#include <stdio.h>
#include <string.h>

int main(void) {
	char buffer[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		//fgets(buffer, BUFFER_SIZE, stdin); //fgets(읽어올데이터를저장할매버퍼, 버퍼의크기, 파일포인터(stdin)  
		//buffer[strlen(buffer) - 1] = '\0';
		readline(buffer, BUFFER_SIZE);
		printf("%s:%d\n", buffer, strlen(buffer));
	}
	return 0;
}

//readline 함수 만들기
int readline(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n') { //getchar함수를 이용하여 한글자씩 읽음 -> ch에 담기                                                                                 
		if (i < limit - 1) { //마지막에 null을 추가해야 함
			str[i] = ch; //int형
			i++;
		}
	}
	str[i] = '\0'; //문자열 마지막 부분 '\0'로 채우기
	return i; //문자열 크기 리턴
}