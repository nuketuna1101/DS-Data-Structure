#include <stdio.h>
#include <stdlib.h>

//이 코드는 Sparse Matrix 과제를 위한 코드입니다. 2017320108 고재영.
 
 #define MAX_SIZE 50
 typedef enum {head, entry} tagfield;
 typedef struct matrixNode *matrixPointer;
 
 typedef struct entryNode{
 		int row;
 		int col;
 		int value;
 }entryNode;
 
 typedef struct matrixNode {
 		matrixPointer down;
 		matrixPointer right;
 		tagfield tag;
 		union{
 				matrixPointer next;
				entryNode entry;	
		} u;
 }matrixNode;

 typedef struct {		//수업에 기반한 구조 토대로 새로운 구조체 생성 
 	matrixPointer hdnode[MAX_SIZE];
 	matrixPointer node;
 }SparseMatrix;

SparseMatrix *first, *second, *result;	//글로벌로 생성 
 
void mread(SparseMatrix *sm){		//행렬을 생성하는데에 사용하는 함수 
	
	int numRows, numCols, numTerms, numHeads, i;	//희소행렬 전체 행, 열, 논제로 엘리먼트 수 
	int row, col, value, currentRow;				//입력받을 논제로 엘리먼트의 값을 받기 위한 행, 열, 값 변수 
	matrixPointer temp, last;
	
	printf("|                                                           |\n");
	printf("|-----다음 세가지를 입력해주십시오.                         |\n");
	printf("|---(1) 희소행렬의 행                                       |\n"); 
	printf("|---(2) 희소행렬의 열                                       |\n");
	printf("|---(3) 희소행렬의 nonzero element의 개수                   |\n");
	printf("|                                                           |\n");
	printf("|-----단, 세가지 입력 시 공백으로 입력하십시오.             |\n");
	printf("|---ex) 3 5 6                                               |\n");
	printf("|                                                           |\n");
	printf("+===========================================================+\n"); 
	printf("|                                                           |\n");
	printf("|     >>세 가지 입력 :  ");
	scanf("%d %d %d", &numRows, &numCols, &numTerms);					//희소행렬 자체 큰 틀의 정보를 입력받음. 
	
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = numTerms;/////////
	
	if(!numHeads)	//밸류가 하나도 없어서 자기 자신 가리킴 
		sm->node->right = sm->node;
	else {
		//헤더 노드 초기화 
		for (i = 0; i < numHeads; i++){
			temp = malloc(sizeof(struct matrixNode));
			sm->hdnode[i] = temp;
			sm->hdnode[i]->tag = head;
			sm->hdnode[i]->right = temp;
			sm->hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = sm->hdnode[0];

		printf("|                                                           |\n");
		printf("|-----%d개의 nonzero element 값 입력하세요.                 |\n", numTerms);
		printf("|-----단, (행) (열) (값) 순서로 입력하시오.                 |\n");
		printf("|---ex) 3 5 6                                               |\n");
		printf("|                                                           |\n");
		printf("+===========================================================+\n");
		
		for(i = 0; i < numTerms; i++){
			printf("|                                                           |\n");
			printf("|     >> %d 번째 nonzero element 입력 :  ", i+1);
			scanf("%d %d %d", &row, &col, &value);
			printf("|                                                           |\n");
			
			if (row > currentRow) {	//다음 행 넘어가기  
				last->right = sm->hdnode[currentRow];
				currentRow = row;
				last = sm->hdnode[row];
			}
			  
			temp = malloc(sizeof(struct matrixNode));
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp;
			last = temp;
			
			sm->hdnode[col]->u.next->down = temp;
			sm->hdnode[col]->u.next = temp;
		}
		
		last->right = sm->hdnode[currentRow];
		
		for (i = 0; i < numCols; i++)
			sm->hdnode[i]->u.next->down = sm->hdnode[i];
		
		for( i = 0; i < numHeads - 1; i++)
			sm->hdnode[i]->u.next = sm->hdnode[i+1];
		sm->hdnode[numHeads-1]->u.next = sm->node;
		sm->node->right = sm->hdnode[0];
	}
	
}


void mwrite(SparseMatrix * sm){		//행렬을 출력합니다. 
	int i, row, col;
	matrixPointer temp;
	matrixPointer head = sm->node->right;
	
	printf("|                                                           |\n");
	printf("|                                                           |\n");
	printf("|-----|| 당신은 %d 행 %d 열 희소행렬을 생성했습니다\n", sm->node->u.entry.row, sm->node->u.entry.col);
	printf("|-----|| 0이 아닌 원소의 개수는 %d 개 입니다.               |\n", sm->node->u.entry.value);
	printf("|                                                           |\n");
	
	printf("|-----(1) 생성된 행렬의 행 / 열 / 값                        |\n");
	for( i = 0; i < sm->node->u.entry.row; i++){
		for(temp = head->right; temp != head; temp = temp->right)
			printf("|       %4d%4d%4d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next;
	} 
	
	printf("|                                                           |\n");
	printf("|-----(2) 생성된 행렬의 시각화된 표현                       |\n");
	for(row = 0; row < sm->node->u.entry.row; row++){
		for(col = 0; col < sm->node->u.entry.col; col++){
			printf("\t%3d ", readElement(sm, row, col));
		}
		printf("\n");
	}
	printf("|                                                           |\n");

	
}

void merase(SparseMatrix * sm){
		matrixPointer x, y;
		matrixPointer head = sm->node->right;
		int i, numHeads;
		
		for (i = 0; i < sm->node->u.entry.row; i++){
			y = head->right;
			while (y != head){
				x = y;
				y = y->right;
				free(x);
			}
			x = head;
			head = head->u.next;
			free(x);
		}
		y = head;
		while (y != sm->node) {
			x = y;
			y = y->u.next;
			free(x);
		}
		free(sm->node);
		sm->node = NULL;
}

// readElement함수는 연산하는 데에 유용하게 사용할 함수입니다.
// sm이라는 행렬에서 행과 열의 좌표로부터 값을 반환하는 함수입니다. 
int readElement(SparseMatrix *sm, int row, int col){ 
	matrixPointer temp;
	matrixPointer head = sm->hdnode[row];
	
	for(temp = head->right; temp != head; temp = temp->right){	//값이 존재한다면 반환 
		if(temp->u.entry.col == col)
			return temp->u.entry.value;
	}
	return 0;//노드에 값이 존재하지 않는다는 것은 0이기 때문에 0을 반환 

} 

//희소행렬 d는 연산의 결과로 생성된 함수, 희소행렬 a,b는 피연산될 두 희소행렬입니다 
void madd(SparseMatrix *sm, SparseMatrix *a, SparseMatrix *b){
	int numRows = a->node->u.entry.row, numCols = a->node->u.entry.col, numTerms, numHeads, i;	//희소행렬 전체 행, 열, 논제로 엘리먼트 수 
	int row, col, value, currentRow;				//입력받을 논제로 엘리먼트의 값을 받기 위한 행, 열, 값 변수 
	matrixPointer temp, last;
	
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = 0; //원소 개수는 0으로 초기화하고 노드 추가할 때마다 올려줍니다 
	
	if(!numHeads)	//밸류가 하나도 없어서 자기 자신 가리킴 
		sm->node->right = sm->node;
	else {
		//헤더 노드 초기화 
		for (i = 0; i < numHeads; i++){
			temp = malloc(sizeof(struct matrixNode));
			sm->hdnode[i] = temp;
			sm->hdnode[i]->tag = head;
			sm->hdnode[i]->right = temp;
			sm->hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = sm->hdnode[0];
		
		for(row = 0; row < numRows; row++){
			for(col = 0; col < numCols; col++){
				
				value = readElement(a, row, col) + readElement(b, row, col);
				 
				if(value == 0)	//덧셈 결과가 0이면 노드를 생성할 필요없음 
					continue;

				//덧셈 결과 토대로 노드 생성  
				sm->node->u.entry.value++; //0이 아닌 값이 나오면 덧셈 결과 행렬의 원소개수 늘어나는 거니까 올려줌 
				if (row > currentRow) {	//
					last->right = sm->hdnode[currentRow];
					currentRow = row;
					last = sm->hdnode[row];
				}
			  
				temp = malloc(sizeof(struct matrixNode));
				temp->tag = entry;
				temp->u.entry.row = row;
				temp->u.entry.col = col;
				temp->u.entry.value = value;
				last->right = temp;
				last = temp;
				
				sm->hdnode[col]->u.next->down = temp;
				sm->hdnode[col]->u.next = temp;
			}				
		}
		//행 종료 후 닫아줌 
		last->right = sm->hdnode[currentRow];
		
		for (i = 0; i < numCols; i++)
			sm->hdnode[i]->u.next->down = sm->hdnode[i];
		
		for( i = 0; i < numHeads - 1; i++)
			sm->hdnode[i]->u.next = sm->hdnode[i+1];
		sm->hdnode[numHeads-1]->u.next = sm->node;
		sm->node->right = sm->hdnode[0];
	}
}

void mmult(SparseMatrix *sm, SparseMatrix *a, SparseMatrix *b){
	int numRows = a->node->u.entry.row, numCols = b->node->u.entry.col, numTerms, numHeads, i;	//희소행렬 전체 행, 열, 논제로 엘리먼트 수 
	int row, col, value, currentRow;				//입력받을 논제로 엘리먼트의 값을 받기 위한 행, 열, 값 변수 
	int k;
	matrixPointer temp, last;
		
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = 0;
	
	if(!numHeads)	//밸류가 하나도 없어서 자기 자신 가리킴 
		sm->node->right = sm->node;
	else {
		//헤더 노드 초기화 
		for (i = 0; i < numHeads; i++){
			temp = malloc(sizeof(struct matrixNode));
			sm->hdnode[i] = temp;
			sm->hdnode[i]->tag = head;
			sm->hdnode[i]->right = temp;
			sm->hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = sm->hdnode[0];
		
		for(row = 0; row < numRows; row++){		//첫 번째 행렬의 row순서로  
			for(col = 0; col < numCols; col++){		//두 번째 행렬의 col 순서로  
				value = 0;
				for(k = 0; k < a->node->u.entry.col; k++){
					value += readElement(a, row, k) * readElement(b, k, col);
				}
			
				if(value == 0)	//덧셈 결과가 0이면 노드를 생성할 필요없음 
					continue;
				//곱셈 결과 토대로 노드 생성
				sm->node->u.entry.value++;  
				if (row > currentRow) {	//
					last->right = sm->hdnode[currentRow];
					currentRow = row;
					last = sm->hdnode[row];
				}
			  
				temp = malloc(sizeof(struct matrixNode));
				temp->tag = entry;
				temp->u.entry.row = row;
				temp->u.entry.col = col;
				temp->u.entry.value = value;
				last->right = temp;
				last = temp;
				
				sm->hdnode[col]->u.next->down = temp;
				sm->hdnode[col]->u.next = temp;			
			}				
		}
		//행 종료 후 닫아줌 
		last->right = sm->hdnode[currentRow];
		
		for (i = 0; i < numCols; i++)
			sm->hdnode[i]->u.next->down = sm->hdnode[i];
		
		for( i = 0; i < numHeads - 1; i++)
			sm->hdnode[i]->u.next = sm->hdnode[i+1];
		sm->hdnode[numHeads-1]->u.next = sm->node;
		sm->node->right = sm->hdnode[0];
	}	
	
	
	
}

void Transpose(SparseMatrix *sm, SparseMatrix *a){
	
	int numRows = a->node->u.entry.col, numCols = a->node->u.entry.row, numTerms, numHeads, i;	//희소행렬 전체 행, 열, 논제로 엘리먼트 수 
	int row, col, value, currentRow;				//입력받을 논제로 엘리먼트의 값을 받기 위한 행, 열, 값 변수 
	matrixPointer temp, last;
	
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = a->node->u.entry.value; //전치를 해도 원소의 개수는 변하지 않음 
	
	if(!numHeads)	//밸류가 하나도 없어서 자기 자신 가리킴 
		sm->node->right = sm->node;
	else {
		//헤더 노드 초기화 
		for (i = 0; i < numHeads; i++){
			temp = malloc(sizeof(struct matrixNode));
			sm->hdnode[i] = temp;
			sm->hdnode[i]->tag = head;
			sm->hdnode[i]->right = temp;
			sm->hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = sm->hdnode[0];
		
		for(row = 0; row < numRows; row++){
			for(col = 0; col < numCols; col++){
				
				value = readElement(a, col, row);
				if(value == 0)	//덧셈 결과가 0이면 노드를 생성할 필요없음 
					continue;

				//덧셈 결과 토대로 노드 생성  
				if (row > currentRow) {	//
					last->right = sm->hdnode[currentRow];
					currentRow = row;
					last = sm->hdnode[row];
				}
			  
				temp = malloc(sizeof(struct matrixNode));
				temp->tag = entry;
				temp->u.entry.row = row;
				temp->u.entry.col = col;
				temp->u.entry.value = value;
				last->right = temp;
				last = temp;
				
				sm->hdnode[col]->u.next->down = temp;
				sm->hdnode[col]->u.next = temp;
			}				
		}
		//행 종료 후 닫아줌 
		last->right = sm->hdnode[currentRow];
		
		for (i = 0; i < numCols; i++)
			sm->hdnode[i]->u.next->down = sm->hdnode[i];
		
		for( i = 0; i < numHeads - 1; i++)
			sm->hdnode[i]->u.next = sm->hdnode[i+1];
		sm->hdnode[numHeads-1]->u.next = sm->node;
		sm->node->right = sm->hdnode[0];
	}	
	
}


int main(void) {
	int a, b, c;	//a, b, c는 메뉴 상에서 사용자가 입력을 처리하기 위한 변수입니다. 
	first = (SparseMatrix*) malloc(sizeof(SparseMatrix)); 
	second = (SparseMatrix*) malloc(sizeof(SparseMatrix)); 
	result = (SparseMatrix *) malloc(sizeof(SparseMatrix)); 
 
	printf("+===========================================================+\n");
	printf("|                                                           |\n");
	printf("|            Sparse Matrices Operation                      |\n");
	printf("|                               Data Structure Assignment   |\n");
	printf("|                                    컴퓨터학과 2017320108  |\n");
	printf("|                                                    고재영 |\n");
	printf("|                                                           |\n");
	printf("|                                                           |\n");
	//초기 시작 메뉴 창이 뜹니다. 
	do{
		printf("+===========================================================+\n");
		printf("|---작업 선택  (원하는 작업을 위해 작업 번호를 입력하시오 ) |\n");
		printf("|-----[1] Sparse Martix A 생성                              |\n");
		printf("|-----[2] Sparse Martix A 삭제                              |\n");
		printf("|-----[3] Sparse Martix B 생성                              |\n");
		printf("|-----[4] Sparse Martix B 삭제                              |\n");
		printf("|-----[5] A와 B 간 행렬 덧셈                                |\n");
		printf("|-----[6] A와 B 간 행렬 곱셈                                |\n");
		printf("|-----[7] 행렬 A의 Transpose                                |\n");
		printf("|-----[8] 행렬 B의 Transpose                                |\n");
		printf("|-----[9] 종료                                              |\n");
		printf("+===========================================================+\n"); 
		printf("|                                                           |\n");
		printf("|     >>원하는 작업 번호 :  ");
		scanf("%d", &a);		//작업 번호에 따라 분기됩니다. 
		
		if(a == 1){
			mread(first);
			mwrite(first);
		} else if (a == 2){
			merase(first);
		} else if (a == 3){
			mread(second);
			mwrite(second);
		} else if (a == 4){
			merase(second);
		} else if (a == 5){	//덧셈  
			if((first->node->u.entry.col == second->node->u.entry.col) &&
				(first->node->u.entry.row == second->node->u.entry.row)){	//덧셈 조건:   
					madd(result, first, second);
					mwrite(result);		
			}else {
				printf("|                                                           |\n");
				printf("|                                                           |\n");
				printf("|---**덧셈 조건 불만족:  두 행렬의 크기가 같지 않습니다.    |\n");
				printf("+===========================================================+\n"); 						
			}
		} else if (a == 6){ //곱셈  
			if(first->node->u.entry.col == second->node->u.entry.row){	//곱셈 조건: 열과 행의 개수가 일치해야합니다  
					mmult(result, first, second);
					mwrite(result);		
			}else {
				printf("|                                                           |\n");
				printf("|                                                           |\n");
				printf("|---**곱셈 조건 불만족:  연산을 위한 열과 행의 개수 불일치  |\n");
				printf("+===========================================================+\n"); 						
			}	
		} else if (a == 7){	//A 전치 
			Transpose(result, first);
			mwrite(result);
		} else if (a == 8){ //B 전치 
			Transpose(result, second);
			mwrite(result);
		} else if (a == 9){ // 종료 
			printf("|                                                           |\n");
			printf("|                                                           |\n");
			printf("|-----[9]번 작업 실행:  프로그램을 종료합니다.              |\n");
			printf("|                                                           |\n");
			printf("+===========================================================+\n"); 
			break; 
		} else {
			printf("|                                                           |\n");
			printf("|                                                           |\n");
			printf("|-----**ERROR**  비정상적인 입력입니다. 종료합니다.         |\n");
			printf("|                                                           |\n");
			printf("+===========================================================+\n");
			break;			
		}
	} while(1);
	return 0;
}
