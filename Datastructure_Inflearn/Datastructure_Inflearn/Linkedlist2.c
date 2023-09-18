#include <stdio.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

Node* head = NULL;

int main() {
	head = (Node*)malloc(sizeof(Node));
	head->data = "Tom";
	head->next = NULL;

	Node*p= (Node*)malloc(sizeof(Node));
	p->data = "Dick";
	p->next = NULL;
	head->next = p;

	p->next= (Node*)malloc(sizeof(Node));
	p->next->data = "Harry";
	p->next->next = NULL;
	
	
}

//������ head�� ���������� �ƴ� ��� 1
//ȣ�� �� 'add_first(&head, item_to_store)'
void add_first(Node **ptr_head, char*item) { //�����ͺ��� head�� �ּҸ� �Ű������� �޴´�
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = *ptr_head;
	*ptr_head = tmp; //����� head����� �ּҸ� �����͸� �̿��Ͽ� ���� head�� ��
}

//������ head�� ���������� �ƴ� ��� 2
//ȣ�� �� 'head = add_first(head, item_to_store)'
Node* add_first(Node* head, char* item) { //�����ͺ��� head�� �ּҸ� �Ű������� �޴´�
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = head;
	return tmp; //���ο� head����� �ּҸ� return
}