/*��ũ�帮��Ʈ�� �̿��Ͽ� ��ȭ��ȣ ���� ���α׷��� �ۼ�
�� ��忡�� �̸��� ��ȭ��ȣ�� ���Ե�.
�� �Է�, ����, �˻�, ���, ���ᰡ �޴��� ������*/
/*��Ģ
1. ������ �ǵ�, ������ �Ǿ�
2. �˻��� �̸����� �˻��Ͽ� ����� �����.
3. ����� ���� ���� ���� ���
4. ����� �����Ҵ��� �����ϸ� ����
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> //������� ���� ���
#include <stdlib.h> //�����Ҵ��� ���� ���

//��ũ�帮��Ʈ ����ü ����
typedef struct TelNode { 
	char name[20]; //�̸�
	char phone[20]; //��ȭ��ȣ
	struct Node* next; //����ü ������
}TelNode;

//����Լ��� ����
void Insert(); //�Է��Լ�
void Delete(); //�����Լ�
void Search(); //�˻��Լ�
void PrintAll(); //����Լ�

int index(); //�޴�

int main() {
	TelNode* head = NULL;
	head = (TelNode*)malloc(sizeof(TelNode)); //ó�� ��� �����Ҵ� �� ����ȯ
	head->next = NULL; //ù���� �ƹ��͵� ����Ǿ� ���� ����
	
}

void Insert() { //����

	
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