#include <stdio.h>

typedef struct node {
	char *data;
	struct node *next;
}Node;

Node* head = NULL;

int main() {
	//��� ��� ����
	head = (Node*)malloc(sizeof(Node));
	head->data = "Tuesday";
	head->next = NULL;
	
	//�ι�° ���
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = "Thursday";
	q->next = NULL;
	head->next = q;

	//��ũ�帮��Ʈ �� �տ� ��� ����
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