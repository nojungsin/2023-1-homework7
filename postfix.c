#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 10//MAX_STACK_SIZE 10으로 정의
#define MAX_EXPRESSION_SIZE 20//MAX_EXPRESSION_SIZE 20으로 정의
/* stack 내에서 우선순위, lparen = 0 가장 낮음 */


typedef enum{
lparen = 0, /* ( 왼쪽 괄호 */
rparen = 9, /* ) 오른쪽 괄호*/
times = 7, /* * 곱셈 */
divide = 6, /* / 나눗셈 */
plus = 5, /* + 덧셈 */
minus = 4, /* - 뺄셈 */
operand = 1 /* 피연산자 */
} precedence;//lparen은 0, rparen은 9, times는 7, divide는 6, plus는 5, minus는 4, operand는 1로 precedence에서 정의한다.


char infixExp[MAX_EXPRESSION_SIZE]; /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE]; /* postfix로 변환을 위해 필요한 스택*/
int evalStack[MAX_STACK_SIZE]; /* 계산을 위해 필요한 스택 */
int postfixStackTop = -1; /* postfixStack용 top */
int evalStackTop = -1; /* evalStack용 top */
int evalResult = 0; /* 계산 결과를 저장 */
void postfixpush(char x);//postfixStack에 문자 넣기 함수
char postfixPop();//postfixStack에서 문자 빼기 함수
void evalPush(int x);//evalStack에 숫자 넣기 함수
int evalPop();//evalStack에 숫자 빼기 함수
void getInfix();//Infix값 입력 받기
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();



int main()
{
char command;//char형 변수 command 선언
printf("[-----[윤혜준] [2022041021] -----]");
do{
printf("----------------------------------------------------------------\n");
printf(" Infix to Postfix, then Evaluation\n");
printf("----------------------------------------------------------------\n");
printf(" Infix=i, Postfix=p, Eval=e, Debug=d,Reset=r, Quit=q \n");
printf("----------------------------------------------------------------\n");
printf("Command = ");
scanf(" %c", &command);//command값 입력받기
switch(command) {
case 'i': case 'I'://command로 i나 I를 받을 때
getInfix();
break;
case 'p': case 'P'://command로 p나 P를 받을 때
toPostfix();
break;
case 'e': case 'E'://command로 e나 E를 받을 때
evaluation();
break;
case 'd': case 'D'://command로 d나 D를 받을 때
debug();
break;
case 'r': case 'R'://command로 r이나 R을 받을 때
reset();
break;
case 'q': case 'Q'://command로 q나 Q를 받을 때
break;
default:
printf("\n >>>>> Concentration!! <<<<<\n");//command로 그 외 것들을 받을 때
break;
}
}while(command != 'q' && command != 'Q');//command 값이 q가 아니고 Q가 아닌 동안에 반복
return 1;
}


void postfixPush(char x)
{
 postfixStack[++postfixStackTop] = x;//postfixStackTop값 1 증가시키고 postfixStack에 문자 넣기
}


char postfixPop()
{
 char x;
 if(postfixStackTop == -1)//postfixStackTop이 -1인 경우 postfix에 아무것도 들어있지 않으니 아무것도 빼지 않음
 return '\0';
 else {
 x = postfixStack[postfixStackTop--];//postfixStack맨 위의 문자 x에 넣고 postfixStackTop값 1 감소시키거 x값 return
 }
 return x;
}


void evalPush(int x)
{
 evalStack[++evalStackTop] = x;//evalStackTop값 1 증가시키고 evalStack에 숫자 넣기
}


int evalPop()
{
 if(evalStackTop == -1)//evalStackTop이 -1인 경우 evalStack에 아무것도 들어있지 않으니 아무것도 빼지 않음
 return -1;
 else
 return evalStack[evalStackTop--];//evalStack의 맨 위의 값 return시키고 evalStackTop값 1 감소
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()//infixExp변수 통해 문자열 입력 받기
{
 printf("Type the expression >>> ");
 scanf("%s",infixExp);//입력받은 문자열 infixExp에 저장
}


precedence getToken(char symbol)
{
switch(symbol) {//입력받은 문자 symbol이 뭐냐에 따라 return값 달라짐
case '(' : return lparen;//입력받은 문자 symbol이 '('이면 return lparen
case ')' : return rparen;//입력받은 문자 symbol이 ')'이면 return rparen
case '+' : return plus;//입력받은 문자 symbol이 '+'이면 return plus
case '-' : return minus;//입력받은 문자 symbol이 '-'이면 return minus
case '/' : return divide;//입력받은 문자 symbol이 '/'이면 return divide
case '*' : return times;//입력받은 문자 symbol이 '*'이면 return times
default : return operand;//앞에서 언급한 케이스 이외의 경우에는 return operand
}
}


precedence getPriority(char x)
{
return getToken(x);//문자 입력 받아 입력받은 문자를 매개변수로 하여 getToken값 return
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */

void charCat(char* c)
{
if (postfixExp == '\0')//postfixExp가 비어있을 때
strncpy(postfixExp, c, 1);//c에서 문자 하나 postfixExp에 넣기
else
strncat(postfixExp, c, 1);//기존에 postfixExp의 문자 맨 끝에 c의 글자 하나 복사해 붙여넣기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */

void toPostfix()
{
/* infixExp의 문자 하나씩을 읽기위한 포인터 */
char *exp = infixExp;
char x; /* 문자하나를 임시로 저장하기 위한 변수 */
/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
while(*exp != '\0')//exp문자열 띄어쓰기 나올 때까지
{
    if(getPriority(*exp) == operand){//getToken에 해당하는 문자가 없을 경우
        x = *exp;//x에 infixExp 넣기
        charCat(&x);//postfixExp에 x넣기
    }
    else if(getPriority(*exp)==lparen){//괄호'('를 만나면
        postfixPush(*exp);//postfix에 괄호 넣기
    }
    else if(getPriority(*exp)==rparen){//괄호')'를 만나면
        while((x=postfixPop())!='('){//괄호'('를 만날 때까지 postfixExp에 넣기
            charCat(&x);
        }
    }
    else {
        while(getPriority(postfixStack[postfixStackTop])>=getPriority(*exp)){//postfixStack의 맨 끝 문자를 getPriority에 넣은 값이 exp값을 넣은 값보다 작지 않은 이상 계속 반복하기
            x = postfixPop(); //x에 postfix맨 끝 문자 넣기
            charCat(&x);//postfixExp에 x 넣기
        }
        postfixPush(*exp);//postfixStack에 exp넣기
    }
    exp++;//exp문자열의 문자 다음 문자로 넘어가기
}

while(postfixStackTop != -1){//postfixStack맨끝부터 차례대로 비우면서 postfixExp에 넣기
    x = postfixPop();
    charCat(&x);
}
}


void debug()//오류 없는지 확인하기
{
printf("\n---DEBUG\n");
printf("infixExp = %s\n", infixExp);
printf("postExp = %s\n", postfixExp);
printf("eval result = %d\n", evalResult);
printf("postfixStack : ");
for(int i = 0; i < MAX_STACK_SIZE; i++)
printf("%c ", postfixStack[i]);
printf("\n");
}


void reset()//다시 처음 상태로 되돌리기
{
infixExp[0] = '\0';//infixExp에 들어있던 문자열 지우기
postfixExp[0] = '\0';//postfixExp에 들어있던 문자열 지우기
for(int i = 0; i < MAX_STACK_SIZE; i++)
postfixStack[i] = '\0';//postfixStack 차례차례 다 비우기

postfixStackTop = -1;//postfixStckTop다시 처음 상태로 되돌리기
evalStackTop = -1;//evalStackTop다시 처음 상태로 되돌리기
evalResult = 0;//evalResult에 계산한 값이 있든 없든 처음 상태로 되돌리기
}


void evaluation()
{
    int opr1, opr2, i;
    int length = strlen(postfixExp);//postfixExp길이 구해서 length변수에 넣기
    char symbol;
    evalStackTop = -1;//evalStackTop-1로 초기화

    for(i=0; i<length; i++){//차례대로 postfixExp문자 처음부터 끝까지 하나하나씩 읽기
        symbol = postfixExp[i];
        if(getToken(symbol) == operand){//getToken에서 지정한 게 아닌 경우
            evalPush(symbol-'0');//evalStack에 symbol-'0'한 값 넣기
        }
        else {
            opr2 = evalPop();//evalStack맨위 값 빼기
            opr1 = evalPop();//evalStack에서 opr2값 빼고 난 이후 맨위 값 빼기
            switch (getToken(symbol)){//symbol받아서 받아서 symbol별로 다르게 계산한 값 evalStack에 넣기. getToken에서 지정한 게 아닌 경우에는 안넣기
                case plus : evalPush(opr1 + opr2); break;
                case minus : evalPush(opr1 - opr2); break;
                case times : evalPush(opr1 * opr2); break;
                case divide : evalPush(opr1 / opr2); break;
                default: break;
            }
            
        }
    }
    evalResult = evalPop();//최종적으로 다 계산한 값 evalResult에 넣기
}