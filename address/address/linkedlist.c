#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//1. node ����ü �����
typedef struct _Node {
	int data;
	struct _Node* next; //�������(�ڱ� �ڽ��� �ƴ� �ٸ� ���)�� �ּҸ� �����ϴ� ����ü������
}Node;

Node* head;

//2. node �ʱ�ȭ �Լ� �����
int init() {
	head = NULL;
}

//3. �߰� �Լ�, data�� ũ��(���ڰ� ū ����)��� ������ �� �ְ�
void add(int data) {
	Node* ptr;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data; //�������Ҵ�
	newNode->next = NULL; //next ������ �ʱ�ȭ

	//1. �Ǿտ����� 2. �߰������� 3. �ǵڿ�����
	if (head == NULL) {
		head = newNode;
	}
	else { //�� �ڷᱸ���� �ƴ϶��
		if (newNode->data < head->data) {
			newNode->next = head;
			head = newNode;
			return; //�Լ� ���� �ߴ�
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

//4. delete �Լ�
int deleteNode(int data) {
	Node* curr;
	Node* prev;
	curr = prev = head;

	if (head == NULL) {
		printf("Error: ������ ����� �����ϴ�!\n");
		return -1;		
	}
	if (head) {

	}
}

//5. search �Լ�

//6. print �Լ�

//7. main �Լ�

int main() {
	init(); //�ϴ� �ʱ�ȭ

}