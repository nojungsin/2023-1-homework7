#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4//MAX_QUEUE_SIZE 4로 정의

typedef char element;//char를 element로 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE];//element형(char형)의 크기가 MAX_QUEUE_SIZE(4)인 배열 선언
	int front, rear;//int형 변수 front, rear 선언
}QueueType;//구조체 이름 QueueType으로 선언


QueueType *createQueue();//QueueType구조체 포인터 함수 createQueue선언
int freeQueue(QueueType *cQ);//매개변수로 QueueType구조체 포인터 변수 cQ를 받는 int형 함수 freQueue 선언
int isEmpty(QueueType *cQ);//매개변수로 QueueType구조체 포인터 변수 cQ를 받는 int형 함수 isEmpty 선언
int isFull(QueueType *cQ);//매개변수로 QueueType구조체 포인터 변수 cQ를 받는 int형 함수 isFull 선언
void enQueue(QueueType *cQ, element item);//매개변수로 QueueType구조체 포인터 변수 cQ와 element형 변수 item을 받는 void형 함수 enQueue 선언
void deQueue(QueueType *cQ, element* item);//매개변수로 QueueType구조체 포인터 변수 cQ와 element형 푕ㄴ터 변수 item을 받는 void형 함수 deQueue 선언
void printQ(QueueType *cQ);//매개변수로 QueueType구조체 포인터 변수 cQ를 받는 void형 함수 printQ 선언
void debugQ(QueueType *cQ);//매개변수로 QueueType구조체 포인터 변수 cQ를 받는 void형 함수 debugQ 선언
element getElement();//element형(char형) 변수 getElement 선언


int main(void)
{
	QueueType *cQ = createQueue();//구조체 생성
	element data;//element형 변수 data 선언
	char command;//char형 변수 command 선언

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");//명령어 종류 : 값 입력은 i, 값 삭제는 d, 값 출력은 p, 디버깅은 b, 그만두기는 q
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//명령어 입력받기

		switch(command) {//명령어 종류 따라서
		case 'i': case 'I'://명령어 i거나 I 입력받을 경우
			data = getElement();//data에 getElement함수 통해 넣고싶은 값 받아 data에 넣기
			enQueue(cQ, data);//enQueue함수에 매개변수로 cQ와 data값 넣고 값 넣기
			break;
		case 'd': case 'D'://명령어 d나 D 입력받을 경우
			deQueue(cQ, &data);//deQueue함수에 매개변수로 cQ와 data주소값 넣고 삭제하기
			break;
		case 'p': case 'P'://명령어 p나 P 입력받을 경우
			printQ(cQ);//printQ함수에 매개변수로 cQ 넣고 값 출력
			break;
		case 'b': case 'B'://명령어 b나 B 입력받을 경우
			debugQ(cQ);//dabugQ함수에 매개변수로 cQ 
			break;
		case 'q': case 'Q'://명령어 q나 Q 입력받을 경우
   	        freeQueue(cQ);//freeQueue함수에 매개변수로 cQ 넣기
			break;
		default://명령어에 이외의 것 입력했을 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//Concentration!! 출력
			break;
		}

	}while(command != 'q' && command != 'Q');//command값이 q가 아니면서 Q가 아니면 반복


	return 1;
}


QueueType *createQueue()//구조체 생성
{
	QueueType *cQ;//QueType구조체 포인터 변수 cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ에 QueueType으로 동적할당
	cQ->front = 0;//cQ구조체의 front변수 값 0으로 선언
	cQ->rear = 0;//cQ구조체의 rear변수 값 0으로 선언
	return cQ;//cQ값 리턴
}


int freeQueue(QueueType *cQ)//QueueType구조체 cQ 동적할당 해제
{
    if(cQ == NULL) return 1;//cQ가 비어있으면 동적할당 해제할 게 없으므로 시행 할 거 없음
    free(cQ);//cQ 비어있지 않으면 동적할당 해제
    return 1;//return 1
}


element getElement()//넣고싶은 element값 받기
{
	element item;//element형 변수 item 선언
	printf("Input element = ");//element값 받기
	scanf(" %c", &item);//item에 값 넣기
	return item;//item값 return
}


int isEmpty(QueueType *cQ)//원형 큐가 비어있는지 확인
{
    if ((cQ->front) == (cQ->rear)){//cQ->front랑 cQ->rear값이 같을 경우 return 1
        return 1;
    }
    else return 0;//아닐 경우 return 0
}


int isFull(QueueType *cQ)//원형 큐가 꽉 차있는지 확인
{
    if(((cQ->front==0)&&(cQ->rear==MAX_QUEUE_SIZE-1))||((cQ->front-1)==cQ->rear)){//cQ->front가 0이고 cQ->rear가 MAX_QUEUE_SIZE-1이거나 cQ->front-1의 값이 cQ->rear일 경우 꽉 차있다 생각하고 return 1,
        return 1;
    }
    else
        return 0;//꽉 차있지 않을 경우 return 0
}


void enQueue(QueueType *cQ, element item)//구조체에 cQ에 item값 넣기
{
    if (isFull(cQ)==0){//cQ가 아직 꽉 차 있지 않을경우
        cQ->rear = (cQ->rear + 1)%MAX_QUEUE_SIZE;//cQ->rear값 1증가 시키고 증가 시킨 값이 MAX_QUEUE_SIZE와 같을 경우엔 0으로 바꾸기
        cQ->queue[cQ->rear] = item;//cQ->queue[cQ->rear] 에 item값 넣기
    }
    else printf("원형 큐가 꽉 찼습니다. \n");//cQ가 꽉 차있을 경우

}


void deQueue(QueueType *cQ, element *item)
{
    if (isEmpty(cQ)==0){//cQ가 비어있지 않을 경우
	    cQ->queue[cQ->front]=NULL;
        cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE ;//cQ->front값 1증가시키고 1증가시킨값이 MAX_QUEUE_SIZE일 경우에는 0으로 바꾸기
        *item = cQ->queue[cQ->front];
    }
    else printf("원형 큐가 비었습니다. \n");//cQ가 비어있을 경우

}


void printQ(QueueType *cQ)//cQ원소 출력
{
	int i, first, last;//int형 변수 i, first, last

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//cQ의 front값에 1을 더한 값을 MAX_QUEUE_SIZE로 나눈 나머지 first에 넣기
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//cQ의 rear값에 1을 더한 값을 MAX_QUEUE_SIZE로 나눈 나머지 last에 넣기

	printf("Circular Queue : [");

	i = first;//i값에 first값 대입
	while(i != last){//cQ.queue의 원소들 다 출력
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)//front랑 rear위치 구하고 큐 안에 들어있는 값 출력
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {//i값이 0부터 MAX_QUEUE_SIZE-1까지 증가할 동안 cQ의 front값과 비교해 같을 경우 i=front 출력, 같지 않을 경우 cQ->queue원소 출력
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front랑 rear값 출력
}