/*링크드리스트를 이용하여 전화번호 관리 프로그램을 작성
한 노드에는 이름과 전화번호가 포함됨.
총 입력, 삭제, 검색, 출력, 종료가 메뉴에 구현됨*/
/*규칙
1. 삽입은 맨뒤, 삭제는 맨앞
2. 검색은 이름으로 검색하여 결과를 출력함.
3. 출력은 현재 내용 전부 출력
4. 종료는 동적할당을 해제하며 종료
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> //입출력을 위한 헤더
#include <stdlib.h> //동적할당을 위한 헤더

//링크드리스트 구조체 선언
typedef struct TelNode { 
	char name[20]; //이름
	char phone[20]; //전화번호
	struct Node* next; //구조체 포인터
}TelNode;

//기능함수들 구현
void Insert(); //입력함수
void Delete(); //삭제함수
void Search(); //검색함수
void PrintAll(); //출력함수

int index(); //메뉴

int main() {
	TelNode* head = NULL;
	head = (TelNode*)malloc(sizeof(TelNode)); //처음 노드 동적할당 및 형변환
	head->next = NULL; //첫노드와 아무것도 연결되어 있지 않음
	
}

void Insert() { //삽입

	
}
void Delete() {

}
void Search() {

}
void PrintAll(){

}

int index() {

	return 0;
}