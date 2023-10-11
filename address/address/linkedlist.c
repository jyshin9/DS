#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//1. node 구조체 만들기
typedef struct _Node {
	int data;
	struct _Node* next; //다음노드(자기 자신이 아닌 다른 노드)의 주소를 저장하는 구조체포인터
}Node;

Node* head;

//2. node 초기화 함수 만들기
int init() {
	head = NULL;
}

//3. 추가 함수, data의 크기(숫자가 큰 순서)대로 나열될 수 있게
void add(int data) {
	Node* ptr;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data; //데이터할당
	newNode->next = NULL; //next 포인터 초기화

	//1. 맨앞에삽입 2. 중간에삽입 3. 맨뒤에삽입
	if (head == NULL) {
		head = newNode;
	}
	else { //빈 자료구조가 아니라면
		if (newNode->data < head->data) {
			newNode->next = head;
			head = newNode;
			return; //함수 실행 중단
		}
		for (ptr = head; ptr->next; ptr = ptr->next) {
			if (ptr->data < newNode->data && newNode->data < ptr->next->data) {
				newNode->next = ptr->next;
				ptr->next = newNode;
				return;
			}
		}
		ptr->next = newNode;
	}
}

//4. delete 함수
int deleteNode(int data) {
	Node* curr;
	Node* prev;
	curr = prev = head;

	if (head == NULL) {
		printf("Error: 삭제할 목록이 없습니다!\n");
		return -1;		
	}
	if (head) {

	}
}

//5. search 함수

//6. print 함수

//7. main 함수

int main() {
	init(); //일단 초기화

}