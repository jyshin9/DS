#include <stdio.h>

typedef struct node {
	char *data;
	struct node *next;
}Node;

Node* head = NULL;

int main() {
	//헤드 노드 생성
	head = (Node*)malloc(sizeof(Node));
	head->data = "Tuesday";
	head->next = NULL;
	
	//두번째 노드
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = "Thursday";
	q->next = NULL;
	head->next = q;

	//링크드리스트 맨 앞에 노드 삽입
	q = (Node*)malloc(sizeof(Node));
	q->data = "Monday";
	q->next = head;
	head = q;

	Node* p = head;
	while (p != NULL) {
		printf("%s\n", p->data);
		p = p->next;
	}
}