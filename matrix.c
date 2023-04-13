#include <stdio.h>
#include <stdlib.h>

int print_matrix(int **arr, int row, int column){//arr함수 시작주소 받고 행 값 row, 열 값 column 받기
    for (int i=0; i<row; i++){
        for (int j=0; j<column; j++){       
            printf(" %d ", arr[i][j]);//행렬값 차례대로 출력
        }
        printf("\n");
    }

    return 0;
}

int free_matrix(int **arr, int row, int column){//arr함수 시작주소 받고 행 값 row, 열 값 column 받기
    for (int i=0; i<column; i++){
        free(arr[i]);//arr함수의 열 차례대로 메모리 해제 시켜서 1차원으로 만들기
    }
    free (arr);//완전히 메모리 해제시키기

    return 0;
}


int addition_matrix(int **arr1, int **arr2, int row, int column){//함수 arr1, arr2 두 개 시작주소 받고 두 함수의 행 값 row, 열 값 column 받기
    int **arr3;//더블포인터 arr3 선언
    arr3 = (int**)malloc(sizeof(int*)*row);//arr3 동적할당으로 row만큼 공간 할당받기
    for (int i=0; i<row; i++){
        arr3[i] = (int*)malloc(sizeof(int)*column);//arr3의 앞서 배정받은 1차원 공간 각 행에 column만큼 공간 할당받기
        for (int j=0; j<column; j++){
            arr3[i][j] = arr1[i][j] + arr2[i][j];//arr3배열의 i행,j열에 두 배열 arr1, arr2의 i행,j열의 값 더해서 넣기
        }
    }
    print_matrix(arr3, row, column);//arr3값 차례대로 출력
    free_matrix(arr3, row, column);//arr3 동적할당 받은거 메모리 해제

    return 0;
}

int subtraction_matrix(int **arr1, int **arr2, int row, int column){//함수 arr1, arr2 두 개 시작주소 받고 두 함수의 행 값 row, 열 값 column 받기
    int **arr3;//더블포인터 arr3 선언
    arr3 = (int**)malloc(sizeof(int*)*row);//arr3 동적할당으로 row만큼 공간 할당받기
    for (int i=0; i<row; i++){
        arr3[i] = (int*)malloc(sizeof(int)*column);//arr3의 앞서 배정받은 1차원 공간 각 행에 column만큼 공간 할당받기
        for (int j=0; j<column; j++){
            arr3[i][j] = arr1[i][j] - arr2[i][j];//배열 arr1의 i행, j열 값에서 arr2의 i행, j열 값을 빼서 나온 결과값을 arr배열의 i행, j열에 넣기
        }
    }
    print_matrix(arr3, row, column);//arr값 차례대로 출력
    free_matrix(arr3, row, column);//arr3 동적할당 받은거 메모리 해제

    return 0;
}

int transpose_matrix(int **arr, int row, int column){//함수 arr 시작주소 받고 행 값 row, 열 값 column 받기
    int **array;//더블포인터 array 선언
    array = (int**)malloc(sizeof(int*)*column);//array 동적할당으로 column만큼 공간 할당받기
    for (int i=0; i<column; i++){
        array[i] = (int*)malloc(sizeof(int)*row);//array의 앞서 배정받은 1차원 공간 각 행에 row만큼 공간 할당받기
        for (int j=0; j<row; j++){
            array[i][j] = arr[j][i];//arr의 j행, i열 값을 array의 i행, j열에 넣기
        }
    }
    print_matrix(array, column, row);//array값 차례대로 출력
    free_matrix(array, column, row);//array동적할당 받은거 메모리 해제

    return 0;
}

int multiply_matrix(int **arr1, int **arr2, int row, int rowcolumn, int column){//함수 arr1, arr2 두 개 시작주소 받고 arr1의 행 값 row, arr1의 열값이자 arr2의 행값인 rowcolumn받고 arr2의 열 값 column 받기
    int **arr3;//더블포인터 arr3 선언
    int sum=0;//값 다 더해놓을 변수 sum 값 0으로 해서 선언
    arr3 = (int**)malloc(sizeof(int*)*row);//arr3 동적할당으로 row만큼 공간 할당받기
    for (int i=0; i<row; i++){
        arr3[i] = (int*)malloc(sizeof(int)*column);//arr3의 앞서 배정받은 1차원 공간 각 행에 column만큼 공간 할당받기
    }
    for (int i=0; i<row; i++){
        for (int j=0; j<column; j++){
            for(int k=0; k<rowcolumn; k++){
                sum = sum + arr1[i][k]*arr2[k][j];//k값 0부터 rowcolumn-1까지 반복해서 arr1[i][k]*arr2[k][j]값 다 더해서 sum에 넣기 
            }
            arr3[i][j] = sum;//다 더해서 나온 sum값 arr3[i][j]에 저장
        }
    }
    
    print_matrix(arr3, row, column);//arr3값 차례대로 출력
    free_matrix(arr3, row, column);//arr3동적할당 받은거 메모리 삭제

    return 0;
}

int main(void){
    int row, column, rowcolumn;//행 값 입력받을 변수 row, 열 값 입력받을 변수 column, 변수 rowcolumn선언
    int **A;//2차원 배열 만들 A 더블포인터로 선언
    int **B;//2차원 배열 만들 B 더블포인터로 선언

    printf("[----- [ 윤혜준 ] [2022041021] -----\n");

    printf("행렬의 행과 열 값 입력 : ");
    scanf("%d %d", &row, &column);//차례대로 행 값 row, 열 값 column 받기
    A = (int**)malloc(sizeof(int*)*row);//row만큼 동적할당
    B = (int**)malloc(sizeof(int*)*row);//row만큼 동적할당

    for (int i=0; i<row; i++){
        A[i]=(int*)malloc(sizeof(int)*column);//row만큼 동적할당 한 곳의 각 원소마다 다시 column만큼 동적할당
        B[i]=(int*)malloc(sizeof(int)*column);//row만큼 동적할당 한 곳의 각 원소마다 다시 column만큼 동적할당
    }

    for (int i=0; i<row; i++){
        for (int j=0; j<column; j++){
            A[i][j] = i*column+j;//A행렬에 값 넣기
            B[i][j] = i + j*row;//B행렬에 값 넣기
        }
    }

    printf("\n\n-------------------------\n");
    printf("행렬 A\n");
    printf("-------------------------\n");
    print_matrix(A, row, column);//A행렬 출력

    printf("\n\n-------------------------\n");
    printf("행렬 B\n");
    printf("-------------------------\n");
    print_matrix(B, row, column);//B행렬 출력

    printf("\n\n-------------------------\n");
    printf("두 행렬 A, B를 A + B를 한 행렬\n");
    printf("-------------------------\n");
    addition_matrix(A, B, row, column);//A,B행렬 더한 값 구하고 출력

    printf("\n\n-------------------------\n");
    printf("두 행렬 A, B를 A - B를 한 행렬\n");
    printf("-------------------------\n");
    subtraction_matrix(A, B, row, column);//A행렬에서 B행렬 뺀 값 구하고 출력

    free_matrix(A, row, column);//A행렬 메모리 해제
    free_matrix(B, row, column);//B행렬 메모리 해제


    printf("행렬의 행과 열, 그리고 행과 열 값 모두 다 사용될 값 입력 : ");
    scanf("%d %d %d", &row, &column, &rowcolumn);//차례대로 row값, column값, rowcolumn값 입력받기
    A = (int**)malloc(sizeof(int*)*row);//row만큼 동적할당
    B = (int**)malloc(sizeof(int*)*rowcolumn);//rowcolumn만큼 동적할당

    for (int i=0; i<row; i++){
        A[i]=(int*)malloc(sizeof(int)*rowcolumn);//row만큼 동적할당 한 곳의 각 원소마다 다시 rowcolumn만큼 동적할당
        for (int j=0; j<rowcolumn; j++){
            A[i][j] = i*rowcolumn + j;//A행렬에 값 넣기
        }
    }

    for (int i=0; i<rowcolumn; i++){
        B[i]=(int*)malloc(sizeof(int)*column);//rowcolumn만큼 동적할당 한 곳의 각 원소마다 다시 column만큼 동적할당
        for (int j=0; j<column; j++){
            B[i][j] = i*column + j;//B행렬에 값 넣기
        }
    }

    printf("\n\n-------------------------\n");
    printf("행렬 A의 전치행렬 T\n");
    printf("-------------------------\n");
    transpose_matrix(A, row, rowcolumn);//A행렬의 전치행렬 T의 값 구하고 출력

    printf("\n\n-------------------------\n");
    printf("두 행렬 A, B를 A X B한 행렬\n");
    printf("-------------------------\n");
    multiply_matrix(A, B, row, rowcolumn, column);//A행렬과 B행렬 곱한 값 구하고 출력

    free_matrix(A, row, rowcolumn);//A행렬 메모리 해제
    free_matrix(B, rowcolumn, column);//B행렬 메모리 해제

    return 0;
}