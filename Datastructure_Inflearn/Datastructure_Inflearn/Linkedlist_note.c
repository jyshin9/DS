#include <stdio.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

//포인터 head가 전역변수가 아닌 경우 1
//호출 시 'add_first(&head, item_to_store)'
void add_first(Node** ptr_head, char* item) { //포인터변수 head의 주소를 매개변수로 받는다
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = *ptr_head;
	*ptr_head = tmp; //변경된 head노드의 주소를 포인터를 이용하여 변수 head에 씀
}

//포인터 head가 전역변수가 아닌 경우 2
//호출 시 'head = add_first(head, item_to_store)'
Node* add_first(Node* head, char* item) { //포인터변수 head의 주소를 매개변수로 받는다
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = head;
	return tmp; //새로운 head노드의 주소를 return
}

//어떤 노드 뒤에 새로운 노드 삽입하기
//성공하면 1, 아니면 0
int add_after(Node* prev, char* item) { //prev: 삽입할 부분 바로 앞노드
	if (prev == NULL)
		return 0;
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = prev->next;
	prev->next = tmp;

	return 1;
}

//첫번째 노드의 삭제
