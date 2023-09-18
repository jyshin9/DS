#include <stdio.h>

typedef struct node {
	int data;
	struct node* next;
}Node;

//������ head�� ���������� �ƴ� ��� 1
//ȣ�� �� 'add_first(&head, item_to_store)'
void add_first(Node** ptr_head, char* item) { //�����ͺ��� head�� �ּҸ� �Ű������� �޴´�
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

//� ��� �ڿ� ���ο� ��� �����ϱ�
//�����ϸ� 1, �ƴϸ� 0
int add_after(Node* prev, char* item) { //prev: ������ �κ� �ٷ� �ճ��
	if (prev == NULL)
		return 0;
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = prev->next;
	prev->next = tmp;

	return 1;
}

//ù��° ����� ����
