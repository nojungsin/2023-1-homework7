#include<stdio.h>
#include<stdlib.h>


typedef struct Node {//Node형 구조체 이름 listNode로 정의
	int key;//정수형 변수 key
	struct Node* link;//구조체 Node형 포인터 변수 link
} listNode;


typedef struct Head {//Head형 구조체 이름 headNode로 정의
	struct Node* first;//구조체 Node형 포인터 변수 first
} headNode;


headNode* initialize(headNode* h);///리스트의 기존에 있는 노드들을 다 지우고 맨 처음의 headNode만 새로 만들어서 headNode만 있는 리스트로 만드는 함수 initialize
int freeList(headNode* h);//리스트에 있는 노드들 다 free 시키는 함수 freeList

int insertFirst(headNode* h, int key);//int형 함수 insertFirst와 매개변수 headNode형 포인터 변수 h, int형 포인터 변수 key
int insertNode(headNode* h, int key);//key값을 가지는 Node를 만들어 리스트에 삽입하기
int insertLast(headNode* h, int key);//int형 함수 insertLast와 매개변수 headNode형 포인터 변수 h, int형 포인터 변수 key

int deleteFirst(headNode* h);//int형 함수 deleteFirst와 매개변수 headNode형 포인터 변수 h
int deleteNode(headNode* h, int key);//int형 함수 deleteNode와 매개변수 headNode형 포인터 변수 h
int deleteLast(headNode* h);//int형 함수 deleteLast와 매개변수 headNode형 포인터 변수 h
int invertList(headNode* h);//int형 함수 inverLast와 매개변수 headNode형 포인터 변수 h

void printList(headNode* h);//void형 함수 printList와 매개변수 headNode형 포인터 변수 h


int main()
{
	char command;//명령어 입력받은 char형 변수 command
	int key;//넣고싶은 값 입력받은 int형 변수 key
	headNode* headnode=NULL;//시작 부분이 될 headNode형 포인터 변수 headnode값 Node로 초기화

	printf("[----- [윤혜준] [2022041021] -----]\n");
	
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//실행할 명령어 command변수에 입력받기

		switch(command) {//입력받은 command값에 따라 다르게 실행
		case 'z': case 'Z'://command값으로 z나 Z 입력받은 경우
			headnode = initialize(headnode);///리스트의 기존에 있는 노드들을 다 지우고 headNode만 새로 만들어서 headNode만 있는 리스트로 만들기
			break;
		case 'p': case 'P'://command값으로 p나 P입력받은 경우
			printList(headnode);//headnode값을 매개변수 값으로 해서 printList함수에 넣어 노드 값 차례대로 출력
			break;
		case 'i': case 'I'://command값으로 i나 I 입력받은 경우
			printf("Your Key = ");//노드에 넣고 싶은 key값 입력받기
			scanf("%d", &key);
			insertNode(headnode, key);//key값을 가지는 Node를 만들어 리스트에 삽입하기
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);//리스트에 있는 노드들 다 free 시키기
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//command가 q나 Q일때 반복 종료

	return 1;
}


headNode* initialize(headNode* h) {//리스트의 기존에 있는 노드들을 다 지우고 headNode만 새로 만들어서 headNode만 있는 리스트로 만드는 함수 initialize
	if(h != NULL)//입력받은 headNode의 값이 NULL이 아닌 경우
		freeList(h);//리스트에 있는 노드들 다 free 시키기
	headNode* temp = (headNode*)malloc(sizeof(headNode));//새로운 노드 temp 만들기
	temp->first = NULL;//새로 만든 노드 temp의 first에 NULL값 넣기
	return temp;//새로운 headNode주소 temp를 return
}


int freeList(headNode* h){//매개변수로 headNode형 포인터 변수 h를 받아 리스트 노드들 다 free 시키는 함수 freeList
	listNode* p = h->first;//새로운 listNode형 포인터 변수 p를 만들어 h->first의 주솟값 넣기

	listNode* prev = NULL;//비어있는 listNode형 포인터 변수 prev 만들기
	while(p != NULL) {//p가 list의 headNode부터 맨끝까지 한 칸씩 차례대로 이동하면서 지나가는 길에 있는 노드들 free 시키기
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);//다 free 시키고 남은 head함수 free 시키기
	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


int insertNode(headNode* h, int key) {//key값을 가지는 Node를 만들어 리스트에 삽입하는 함수 insertNode
    listNode* node = (listNode*)malloc(sizeof(listNode));//새로운 노드로 node만들기
	node->key = key;//node의 key 값에 입력받은 key값 넣기
	node->link = NULL;//node의 Link 비워두기

	if (h->first == NULL)//아무것도 존재하지 않는 리스트인 경우
	{
		h->first = node;//headNode에 node넣기
		return 0;
	}

	listNode* n = h->first;//새로운 노드 n을 만들고 h->first값 넣기
	listNode* trail = h->first;//새로운 노드 trail을 만들어 h->first값 넣기

	while(n != NULL) {//
		if(n->key >= key) {
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { 
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}
	trail->link = node;

	return 0;
}


int insertLast(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;

	return 0;
}


int deleteFirst(headNode* h) {
    if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}


int deleteNode(headNode* h, int key) {
    if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {
				h->first = n->link;
			} else {
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	printf("cannot find the node for key = %d\n", key);

	return 0;

}


int deleteLast(headNode* h) {
    if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	trail->link = NULL;
	free(n);

	return 0;
}


int invertList(headNode* h) {
    if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
