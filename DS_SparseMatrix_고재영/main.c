#include <stdio.h>
#include <stdlib.h>

//�� �ڵ�� Sparse Matrix ������ ���� �ڵ��Դϴ�. 2017320108 ���翵.
 
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

 typedef struct {		//������ ����� ���� ���� ���ο� ����ü ���� 
 	matrixPointer hdnode[MAX_SIZE];
 	matrixPointer node;
 }SparseMatrix;

SparseMatrix *first, *second, *result;	//�۷ι��� ���� 
 
void mread(SparseMatrix *sm){		//����� �����ϴµ��� ����ϴ� �Լ� 
	
	int numRows, numCols, numTerms, numHeads, i;	//������ ��ü ��, ��, ������ ������Ʈ �� 
	int row, col, value, currentRow;				//�Է¹��� ������ ������Ʈ�� ���� �ޱ� ���� ��, ��, �� ���� 
	matrixPointer temp, last;
	
	printf("|                                                           |\n");
	printf("|-----���� �������� �Է����ֽʽÿ�.                         |\n");
	printf("|---(1) �������� ��                                       |\n"); 
	printf("|---(2) �������� ��                                       |\n");
	printf("|---(3) �������� nonzero element�� ����                   |\n");
	printf("|                                                           |\n");
	printf("|-----��, ������ �Է� �� �������� �Է��Ͻʽÿ�.             |\n");
	printf("|---ex) 3 5 6                                               |\n");
	printf("|                                                           |\n");
	printf("+===========================================================+\n"); 
	printf("|                                                           |\n");
	printf("|     >>�� ���� �Է� :  ");
	scanf("%d %d %d", &numRows, &numCols, &numTerms);					//������ ��ü ū Ʋ�� ������ �Է¹���. 
	
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = numTerms;/////////
	
	if(!numHeads)	//����� �ϳ��� ��� �ڱ� �ڽ� ����Ŵ 
		sm->node->right = sm->node;
	else {
		//��� ��� �ʱ�ȭ 
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
		printf("|-----%d���� nonzero element �� �Է��ϼ���.                 |\n", numTerms);
		printf("|-----��, (��) (��) (��) ������ �Է��Ͻÿ�.                 |\n");
		printf("|---ex) 3 5 6                                               |\n");
		printf("|                                                           |\n");
		printf("+===========================================================+\n");
		
		for(i = 0; i < numTerms; i++){
			printf("|                                                           |\n");
			printf("|     >> %d ��° nonzero element �Է� :  ", i+1);
			scanf("%d %d %d", &row, &col, &value);
			printf("|                                                           |\n");
			
			if (row > currentRow) {	//���� �� �Ѿ��  
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


void mwrite(SparseMatrix * sm){		//����� ����մϴ�. 
	int i, row, col;
	matrixPointer temp;
	matrixPointer head = sm->node->right;
	
	printf("|                                                           |\n");
	printf("|                                                           |\n");
	printf("|-----|| ����� %d �� %d �� �������� �����߽��ϴ�\n", sm->node->u.entry.row, sm->node->u.entry.col);
	printf("|-----|| 0�� �ƴ� ������ ������ %d �� �Դϴ�.               |\n", sm->node->u.entry.value);
	printf("|                                                           |\n");
	
	printf("|-----(1) ������ ����� �� / �� / ��                        |\n");
	for( i = 0; i < sm->node->u.entry.row; i++){
		for(temp = head->right; temp != head; temp = temp->right)
			printf("|       %4d%4d%4d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next;
	} 
	
	printf("|                                                           |\n");
	printf("|-----(2) ������ ����� �ð�ȭ�� ǥ��                       |\n");
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

// readElement�Լ��� �����ϴ� ���� �����ϰ� ����� �Լ��Դϴ�.
// sm�̶�� ��Ŀ��� ��� ���� ��ǥ�κ��� ���� ��ȯ�ϴ� �Լ��Դϴ�. 
int readElement(SparseMatrix *sm, int row, int col){ 
	matrixPointer temp;
	matrixPointer head = sm->hdnode[row];
	
	for(temp = head->right; temp != head; temp = temp->right){	//���� �����Ѵٸ� ��ȯ 
		if(temp->u.entry.col == col)
			return temp->u.entry.value;
	}
	return 0;//��忡 ���� �������� �ʴ´ٴ� ���� 0�̱� ������ 0�� ��ȯ 

} 

//������ d�� ������ ����� ������ �Լ�, ������ a,b�� �ǿ���� �� �������Դϴ� 
void madd(SparseMatrix *sm, SparseMatrix *a, SparseMatrix *b){
	int numRows = a->node->u.entry.row, numCols = a->node->u.entry.col, numTerms, numHeads, i;	//������ ��ü ��, ��, ������ ������Ʈ �� 
	int row, col, value, currentRow;				//�Է¹��� ������ ������Ʈ�� ���� �ޱ� ���� ��, ��, �� ���� 
	matrixPointer temp, last;
	
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = 0; //���� ������ 0���� �ʱ�ȭ�ϰ� ��� �߰��� ������ �÷��ݴϴ� 
	
	if(!numHeads)	//����� �ϳ��� ��� �ڱ� �ڽ� ����Ŵ 
		sm->node->right = sm->node;
	else {
		//��� ��� �ʱ�ȭ 
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
				 
				if(value == 0)	//���� ����� 0�̸� ��带 ������ �ʿ���� 
					continue;

				//���� ��� ���� ��� ����  
				sm->node->u.entry.value++; //0�� �ƴ� ���� ������ ���� ��� ����� ���Ұ��� �þ�� �Ŵϱ� �÷��� 
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
		//�� ���� �� �ݾ��� 
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
	int numRows = a->node->u.entry.row, numCols = b->node->u.entry.col, numTerms, numHeads, i;	//������ ��ü ��, ��, ������ ������Ʈ �� 
	int row, col, value, currentRow;				//�Է¹��� ������ ������Ʈ�� ���� �ޱ� ���� ��, ��, �� ���� 
	int k;
	matrixPointer temp, last;
		
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = 0;
	
	if(!numHeads)	//����� �ϳ��� ��� �ڱ� �ڽ� ����Ŵ 
		sm->node->right = sm->node;
	else {
		//��� ��� �ʱ�ȭ 
		for (i = 0; i < numHeads; i++){
			temp = malloc(sizeof(struct matrixNode));
			sm->hdnode[i] = temp;
			sm->hdnode[i]->tag = head;
			sm->hdnode[i]->right = temp;
			sm->hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = sm->hdnode[0];
		
		for(row = 0; row < numRows; row++){		//ù ��° ����� row������  
			for(col = 0; col < numCols; col++){		//�� ��° ����� col ������  
				value = 0;
				for(k = 0; k < a->node->u.entry.col; k++){
					value += readElement(a, row, k) * readElement(b, k, col);
				}
			
				if(value == 0)	//���� ����� 0�̸� ��带 ������ �ʿ���� 
					continue;
				//���� ��� ���� ��� ����
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
		//�� ���� �� �ݾ��� 
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
	
	int numRows = a->node->u.entry.col, numCols = a->node->u.entry.row, numTerms, numHeads, i;	//������ ��ü ��, ��, ������ ������Ʈ �� 
	int row, col, value, currentRow;				//�Է¹��� ������ ������Ʈ�� ���� �ޱ� ���� ��, ��, �� ���� 
	matrixPointer temp, last;
	
	numHeads = (numCols > numRows) ? numCols: numRows;
	sm->node = malloc(sizeof(struct matrixNode)); 
	sm->node->tag = entry;
	sm->node->u.entry.row = numRows;
	sm->node->u.entry.col = numCols;
	sm->node->u.entry.value = a->node->u.entry.value; //��ġ�� �ص� ������ ������ ������ ���� 
	
	if(!numHeads)	//����� �ϳ��� ��� �ڱ� �ڽ� ����Ŵ 
		sm->node->right = sm->node;
	else {
		//��� ��� �ʱ�ȭ 
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
				if(value == 0)	//���� ����� 0�̸� ��带 ������ �ʿ���� 
					continue;

				//���� ��� ���� ��� ����  
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
		//�� ���� �� �ݾ��� 
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
	int a, b, c;	//a, b, c�� �޴� �󿡼� ����ڰ� �Է��� ó���ϱ� ���� �����Դϴ�. 
	first = (SparseMatrix*) malloc(sizeof(SparseMatrix)); 
	second = (SparseMatrix*) malloc(sizeof(SparseMatrix)); 
	result = (SparseMatrix *) malloc(sizeof(SparseMatrix)); 
 
	printf("+===========================================================+\n");
	printf("|                                                           |\n");
	printf("|            Sparse Matrices Operation                      |\n");
	printf("|                               Data Structure Assignment   |\n");
	printf("|                                    ��ǻ���а� 2017320108  |\n");
	printf("|                                                    ���翵 |\n");
	printf("|                                                           |\n");
	printf("|                                                           |\n");
	//�ʱ� ���� �޴� â�� ��ϴ�. 
	do{
		printf("+===========================================================+\n");
		printf("|---�۾� ����  (���ϴ� �۾��� ���� �۾� ��ȣ�� �Է��Ͻÿ� ) |\n");
		printf("|-----[1] Sparse Martix A ����                              |\n");
		printf("|-----[2] Sparse Martix A ����                              |\n");
		printf("|-----[3] Sparse Martix B ����                              |\n");
		printf("|-----[4] Sparse Martix B ����                              |\n");
		printf("|-----[5] A�� B �� ��� ����                                |\n");
		printf("|-----[6] A�� B �� ��� ����                                |\n");
		printf("|-----[7] ��� A�� Transpose                                |\n");
		printf("|-----[8] ��� B�� Transpose                                |\n");
		printf("|-----[9] ����                                              |\n");
		printf("+===========================================================+\n"); 
		printf("|                                                           |\n");
		printf("|     >>���ϴ� �۾� ��ȣ :  ");
		scanf("%d", &a);		//�۾� ��ȣ�� ���� �б�˴ϴ�. 
		
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
		} else if (a == 5){	//����  
			if((first->node->u.entry.col == second->node->u.entry.col) &&
				(first->node->u.entry.row == second->node->u.entry.row)){	//���� ����:   
					madd(result, first, second);
					mwrite(result);		
			}else {
				printf("|                                                           |\n");
				printf("|                                                           |\n");
				printf("|---**���� ���� �Ҹ���:  �� ����� ũ�Ⱑ ���� �ʽ��ϴ�.    |\n");
				printf("+===========================================================+\n"); 						
			}
		} else if (a == 6){ //����  
			if(first->node->u.entry.col == second->node->u.entry.row){	//���� ����: ���� ���� ������ ��ġ�ؾ��մϴ�  
					mmult(result, first, second);
					mwrite(result);		
			}else {
				printf("|                                                           |\n");
				printf("|                                                           |\n");
				printf("|---**���� ���� �Ҹ���:  ������ ���� ���� ���� ���� ����ġ  |\n");
				printf("+===========================================================+\n"); 						
			}	
		} else if (a == 7){	//A ��ġ 
			Transpose(result, first);
			mwrite(result);
		} else if (a == 8){ //B ��ġ 
			Transpose(result, second);
			mwrite(result);
		} else if (a == 9){ // ���� 
			printf("|                                                           |\n");
			printf("|                                                           |\n");
			printf("|-----[9]�� �۾� ����:  ���α׷��� �����մϴ�.              |\n");
			printf("|                                                           |\n");
			printf("+===========================================================+\n"); 
			break; 
		} else {
			printf("|                                                           |\n");
			printf("|                                                           |\n");
			printf("|-----**ERROR**  ���������� �Է��Դϴ�. �����մϴ�.         |\n");
			printf("|                                                           |\n");
			printf("+===========================================================+\n");
			break;			
		}
	} while(1);
	return 0;
}
