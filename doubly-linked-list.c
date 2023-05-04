#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;//Node함수 키 값 받기
	struct Node* llink;//앞의 노드 주소를 저장할 포인터 llink
	struct Node* rlink;//뒤의 노드 주소를 저장할 포인터 rlink
} listNode;


typedef struct Head {
	struct Node* first;//Head함수 포인터
}headNode;


int initialize(headNode** h);//리스트 초기화 함수
int freeList(headNode* h);//리스트의 노드들 free시키는 함수

int insertNode(headNode* h, int key);//노드 추가 함수
int insertLast(headNode* h, int key);//노드 마지막에 추가하는 함수
int insertFirst(headNode* h, int key);//노드 처음에 추가하는 함수
int deleteNode(headNode* h, int key);//key값과 일치하는 노드 지우는 함수
int deleteLast(headNode* h);//마지막 노드 지우는 함수
int deleteFirst(headNode* h);//첫번째 노드 지우는 함수
int invertList(headNode* h);//함수의 순서 바꾸는 함수

void printList(headNode* h);//리스트의 노드들의 key값 차례대로 출력하는 함수


int main()
{
	char command;//명령어 입력받을 변수
	int key;//key값 받을 변수
	headNode* headnode=NULL;//headNode선언

	do{
		printf("[----- [윤혜준] [2022041021] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");//명령어 입력받기
		scanf(" %c", &command);//입력받은 명령어 command변수에 저장하기

		switch(command) {
		case 'z': case 'Z'://command변수에 z나 Z 입력받은 경우
			initialize(&headnode);//리스트 초기화 시키기
			break;
		case 'p': case 'P'://command변수에 p나 P 입력받은 경우
			printList(headnode);//리스트 노드들의 key값들 차례대로 출력하기
			break;
		case 'i': case 'I'://command변수에 i나 I 입력받은 경우
			printf("Your Key = ");//key값 입력받기
			scanf("%d", &key);//입력받은 key값 key변수에 저장
			insertNode(headnode, key);//입력받은 key값을 가지는 노드를 리스트에 넣기
			break;
		case 'd': case 'D'://command변수에 d나 D 입력받은 경우
			printf("Your Key = ");//key값 입력받기
			scanf("%d", &key);//입력받은 key값 key변수에 저장
			deleteNode(headnode, key);//입력받은 key값을 가지는 노드를 리스트에서 지우기
			break;
		case 'n': case 'N'://command변수에 n이나 N 입력받은 경우
			printf("Your Key = ");//key값 입력받기
			scanf("%d", &key);//입력받은 key값 변수에 저장
			insertLast(headnode, key);//입력받은 key값을 가지는 노드를 리스트의 마지막에 넣기
			break;
		case 'e': case 'E'://command변수에 e나 E 입력받은 경우
			deleteLast(headnode);//리스트의 마지막 노드 지우기
			break;
		case 'f': case 'F'://command변수에 f나 F 입력받은 경우
			printf("Your Key = ");//key값 입력받기
			scanf("%d", &key);//입력받은 key값 key변수에 저장
			insertFirst(headnode, key);//입력받은 key값을 가지는 노드를 리스트의 처음에 넣기
			break;
		case 't': case 'T'://command변수에 t나 T 입력받은 경우
			deleteFirst(headnode);//리스트의 첫번째 노드 지우기
			break;
		case 'r': case 'R'://command변수에 r이나 R 입력받은 경우
			invertList(headnode);//리스트의 순서 역순으로 바꾸기
			break;
		case 'q': case 'Q'://command변수에 q나 Q 입력받은 경우
			freeList(headnode);//리스트 노드들 다 free 시키기
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//command변수에 그외 값들을 입력받은 경우 Concentration 출력
			break;
		}

	}while(command != 'q' && command != 'Q');//command에 q나 Q 입력받은 경우 loop나가기

	return 1;
}


int initialize(headNode** h) {//리스트 초기화 시키기
    if(*h != NULL){//headNode가 비어있지 않으면 
        freeList(*h);//freeList(*h)실행
    }
    *h=(headNode*)malloc(sizeof(headNode));//headNode h 새로 동적할당
    (*h)->first=NULL;//first값 NULL로 선언

	return 1;
}


int freeList(headNode* h){//리스트 노드들 다 free 시키기
    listNode* p;//노드들 순서대로 가리킬 포인터 p
    listNode* q;//p따라가면서 차례대로 노드들 지울 포인터 q
    if(h == NULL){//리스트가 비어 있을 경우 바로 끝내기
        return 0;
    }
    p = h->first;//p에 첫번째 노드 값 넣기
    while(p->rlink != NULL){//맨끝 노드에 도달할 때까지 loop
        q = p;//q에 p가 갖고있는 주소값 넣기
        p = p->rlink;//p는 현재 노드의 다음 노드 주소값 가지기
        free(q);//q가 갖고있는 주소의 노드 free 시키기
    }
    free(p);//마지막 노드 free 시키기
    free(h);//headNode free 시키기

	return 0;
}


void printList(headNode* h) {//헤드 노드가 가리키는 리스트의 노드들의 key값들 차례대로 출력하기
	int i = 0;//정수형 변수 i 선언
	listNode* p;//listNode형 포인터 변수 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {//리스트가 존재하지 않을 경우 함수 실행 종료
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//리스트가 존재할 경우 p에 리스트의 첫 번째 노드의 주소값 넣기

	while(p != NULL) {//리스트의 마지막 노드까지 계속해서 반복
		printf("[ [%d]=%d ] ", i, p->key);//노드의 key값 출력
		p = p->rlink;//현재 있는 노드의 rlink 포인터에 담긴 주소의 노드로 이동
		i++;
	}

	printf("  items = %d\n", i);//노드의 개수 출력
}


int insertLast(headNode* h, int key) {//int형 매개변수 key값을 가지는 노드를 포인터 h주소가 가리키는 리스트의 마지막에 노드 삽입
    listNode* p;//마지막의 이전 노드를 가르킬 listNode형 포인터 변수 p
    listNode* node;//key값을 가지는 마지막에 삽입될 listNode형 포인터 변수 node
    node = (listNode*)malloc(sizeof(listNode));//node에 동적할당
    node -> llink = NULL;//node의 llink값 NULL로 선언
    node -> rlink = NULL;//node의 rlink값 NULL로 선언
    node -> key = key;//node의 key 값 key로 선언
    if (h == NULL){//headNode가 존재하지 않을 경우
        initialize(h);
        } //headNode생성
    if (h ->first == NULL){//head노드는 존재하나 리스트가 없는 경우
        h ->first = node;//리스트의 첫 번째에 node삽입
        return 0;
    }
    p = h -> first;//리스트 첫번째 주소값 변수 p에 넣기
    while(p -> rlink != NULL){//리스트의 마지막에 도달할 때까지 loop
        p = p -> rlink;//p에 현재 p의 노드의 다음 노드 주소값 너기
    }
    p -> rlink = node;//p의 다음 노드 가리키는 rlink에 node의 주소값 넣기
    node -> llink = p;//node의 이전 노드 가리키는 llink에 p의 주소값 넣기

	return 0;
}


int deleteLast(headNode* h) {//포인터 h주소가 가리키는 리스트의 마지막 노드 제거
    listNode* p;//마지막 노드를 가리킬 포인터 p
    listNode* q;//마지막 이전 노드를 가리킬 포인터 q
    if ((h == NULL)||(h -> first == NULL)){//headNode가 비어있거나 headNode만 존재하고 리스트는 존재하지 않을 경우
        return 0;
    }
    p = h->first;//headNode가 가리키는 리스트의 첫 번째 노드 주소 p에 넣기
    q = h->first;//headNode가 가리키는 리스트의 첫 번째 노드 주소 q에 넣기
    while(p->rlink !=NULL){//p가 리스트의 마지막 노드에 도달할 때까지 loop
        q = p;
        p = p->rlink;
    }
    free(p);//p가 가리키는 노드 free 시키기
    q->rlink = NULL;//q가 가리키는 노드의 rlink값 NULL로 만들기
	return 0;
}


int insertFirst(headNode* h, int key) {//입력받은 key값을 가지는 노드를 리스트의 처음에 넣기
    listNode* node;//리스트의 처음에 넣을 포인터 변수 node 선언
    node = (listNode*)malloc(sizeof(listNode));//node 동적할당
    node -> llink = NULL;//node의 llinke NULL로 선언
    node -> rlink = NULL;//node의 rlink NULL로 선언
    node -> key = key;//node의 key key로 선언
    if(h == NULL){//headNode가 비어있을 경우 headNode생성
        initialize(h);
    }
    node -> rlink = h -> first;//node의 다음 노드 값으로 현재 h ->first에 있는 주소값 넣기
    h -> first = node;//h -> first가 node 가리키게 만들어 node를 첫 번째 노드로 만들기

	return 0;
}


int deleteFirst(headNode* h) {//리스트의 첫번째 노드 지우기
    listNode* p;//첫 번째 노드 지우는 데 쓸 listNode형 포인터 변수 p 선언
    if ((h == NULL)||(h->first == NULL)){//headNode가 없거나 첫 번째 노드가 존재하지 않는 경우
        return 0;
    }
    p = h -> first;//p에 첫 번째 노드 주소값 넣기
    p = p -> rlink;//p에 두 번째 노드 주소값 넣기
    if (p != NULL){//두 번째 노드가 존재할 경우
        p -> llink = NULL;//두 번째 노드의 앞선 노드 가리키는 값 NULL로 바꾸기
    }
    p = h->first;//다시 첫 번째 노드 가리키기
    h -> first = p -> rlink;//h -> first에 두 번째 노드를 가리키는 주소값 넣기
    free(p);//기존 첫 번째 노드 지우기

	return 0;
}


int invertList(headNode* h) {//리스트의 순서 역순으로 바꾸기
    listNode* left;
    listNode* right;
    if ((h == NULL)||(h -> first == NULL)){//headNode가 존재하지 않거나 리스트에 노드가 없는 경우
        return 0;
    }
    right = h -> first;//right변수에 첫 번째 노드 주소 넣기
    while(right -> rlink != NULL){//right가 리스트의 맨 끝 노드에 도착할 때까지 loop
        left = right;//left에 현재 right가 가리키고 있는 노드 주소값 넣기
        right = right -> rlink;//right에 현재 가리키고 있는 노드의 다음 노드 주소값 넣기
    }
    while( right != NULL){//모든 노드를 다 돌때까지 loop
        right -> llink = right -> rlink;//right가 가리키고 있는 함수의 llink값을 기존 right의 rlink값으로 변경
        right -> rlink = left;//right의 rlink값이 left를 가리키게 변경
        right = left;//right가 가리키는 노드 left가 가리키는 노드로 변경
        left = left -> llink;//left는 이전 노드로 옮기기
    }

	return 0;
}


int insertNode(headNode* h, int key) {//입력받은 key값을 가지는 노드를 리스트에 넣기
    listNode* node;//key값을 가질 노드 node
    listNode* p;//node를 리스트에 삽입할 때 쓸 listNode형 포인터 변수 p
    node = (listNode*)malloc(sizeof(listNode));//node 동적할당
    node -> llink = NULL;//node의 llink NULL로 선언
    node -> rlink = NULL;//node의 rlink NULL로 선언
    node -> key = key;//node의 key값 key로 선언
    if (h == NULL){//headNode가 존재하지 않는 경우
        initialize(h);
    }
    if (h -> first == NULL){//리스트에 노드가 존재하지 않는 경우
        h -> first = node;//h의 first에 node주소 넣기
        return 0;
    }
    p = h -> first;//p에 h -> fist의 값 넣기
    while(p != NULL) {//p가 리스트의 마지막 노드의 rlink에 도착할 때까지 loop
		if(p->key >= key) {//p가 가리키고 있는 노드의 key값이 매개변수 key값보다 크거나 같을 때
			if(p == h->first) {//p가 가리키고 있는 노드가 첫 번째 노드일 경우
				insertFirst(h, key);
			} else {//그외의 경우
				node->rlink = p;//node의 rlink에 p가 가리키고 있는 노드의 주소값 넣기
				node->llink = p->llink;//node의 llink에 p가 가리키고 있는 노드의 앞 노드 주소값 넣기
				p->llink->rlink = node;//p의 llink에 node주소값 넣기
			}
			return 0;
		}
		p = p->rlink;//p를 현재 p가 가리키고 있는 노드의 rlink값으로 변경
	}
	insertLast(h, key);//key값 가지는 노드를 리스트의 맨 마지막에 넣기

	return 0;
}


int deleteNode(headNode* h, int key) {//입력받은 key값을 가지는 노드를 리스트에서 지우기
    listNode* p;//key값을 가지는 노드를 리스트에서 지울 때 쓸 listNode형 포인터 변수 p
    if ((h == NULL)||(h->first == NULL)){//head노드가 존재하지 않거나 리스트 안에 노드가 존재하지 않는 경우
		return 1;
	}
	p = h->first;//p에 리스트의 첫 번째 노드의 주소값 넣기
	while(p != NULL) {//p가 리스트의 마지막 노드까지 다 방문하게 loop
		if( p-> key == key) {//찾는 key값과 현재 p가 가리키는 노드의 key값이 같을 경우
			if(p == h->first) {//p가 가리키는 노드가 첫 번째 노드일 경우
				deleteFirst(h);
			} 
            else if (p -> rlink == NULL){//p가 가리키는 노드가 리스트의 마지막 노드일 경우
				deleteLast(h);
			} 
            else { //그외의 경우
				p -> llink -> rlink = p -> rlink;//p의 이전 노드의 rlink값을 현재 p가 가리키고 있는 노드의 rlink값으로 변경
				p -> rlink -> llink = p -> llink;//p의 다음 노드의 llink값을 현재 p가 가리키고 있는 노드의 rlink값으로 변경
				free(p);//현재 p가 가리키고 있는 노드 free 시키기
			}
			return 1;
		}
		p = p->rlink;//p가 가리키고 있는 노드의 주소값을 현재 p가 가리키고 있는 노드의 다음 노드 주소값으로 변경
	}

	return 1;
}
