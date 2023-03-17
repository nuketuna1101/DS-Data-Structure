#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100	//�ִ� vertex�� ������ 100���� ����
#define MAX_EDGES 4950		//�ִ� edge�� ���� ����
#define SWAP(a,b)  {int temp; temp = a; a = b; b = temp;}	//a�� b�� ��ȯ���ִ� �����Լ�

typedef struct Edge{		//Edge�� ����ü ���� - 2���� vertex�� weight��
	int v1;
	int v2;
	int weight;
}Edge;

int parent[MAX_VERTICES];		//�� vertex�� �з�Ʈ ���
Edge e[MAX_EDGES];				//edge�� ���� �迭


void Init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;		//�з�Ʈ ��� �ʱ�ȭ
	}
}

void Union(int p1, int p2) {		//forest���� �� Ʈ���� ���� �Ű������� �� Ʈ�� ������ ��Ʈ���
	if (p1 < p2)
		parent[p2] = p1;
	else
		parent[p1] = p2;
}

int Find(int v) {		//vertex�� � Ʈ���� ���ϴ� ��, �ش� Ʈ���� root ��带 ��ȯ
	while (parent[v] >= 0) {
		v = parent[v];
	}
	return v;
}


void sort(int edges) {		//Edge ����Ʈ�� weight ������� ���Ľ��� ��
	for (int i = edges; i > 1; i--) {	//������ �˰����� ���ϰ� ����������� ��.
		for (int j = 1; j < i; j++){
			if (e[j - 1].weight > e[j].weight){
				SWAP(e[j - 1].weight, e[j].weight);
				SWAP(e[j - 1].v1, e[j].v1);
				SWAP(e[j - 1].v2, e[j].v2);
			}
		}
	}
}


int CheckCycle(int v1, int v2) {		//cycle �Ǻ� �Լ� - �� vertices�� ���� find���� �������� cycle��

	if (Find(v1) == Find(v2)) {		//�� vertex�� ���� ���� ���տ� �����ִ°�?
		//���� ���տ� ���������� cycle�� ������ ����
		return 0;
	}
	else {
		//�׷��� �ʴٸ� ���� ���տ� �������� �ʾ� cycle �������ؼ� ������.
		Union(Find(v1), Find(v2));
		return 1;
	}
}


void Kruskal(int vertices, int edges) {
	int weightcount = 0;		//MST�� weight�� ����Ұ���
	int edgecount = 0;			//edgecount�� vertex���� - 1�� �Ǹ� ������ ����

	printf("+-----------------------------------------------------------------+\n");


	for (int i = 0; i < edges && edgecount != vertices - 1; i++) {
		if (CheckCycle(e[i].v1, e[i].v2)) {		//����Ŭ �������� �ʴ´ٸ�
			edgecount += 1;
			weightcount += e[i].weight;
			printf("|-- ���õ� %d��° edge: vertex(%d) <--> vertex(%d)  ::||:: weight (%d)|\n", edgecount, e[i].v1, e[i].v2, e[i].weight);
		}
		else {		//����Ŭ�� �����ϸ� �ź�
			printf("|/// �źε� edge: vertex (%d) <--> vertex (%d)                   ///|\n", e[i].v1, e[i].v2);
		}
	}
	printf("+-----------------------------------------------------------------+\n");
	printf("|---�ϼ��� MST�� weight ������ : %d �Դϴ�.                   -----|\n", weightcount);
	printf("|   MST�� edge��� weight ���� ������� �Ϸ� �߽��ϴ�.            |\n");
	printf("|---> ���α׷��� �����մϴ�.                                      |\n");
	printf("+-----------------------------------------------------------------+\n");

}



void InitialScreen() {
	printf("+-----Data Structure Assignment-----------------------------------|\n");
	printf("|     Find a MSP by using Kruskal's Algorithm                     |\n");
	printf("|                                          Computer Science Major |\n");
	printf("|                                          2017320108 Ko Jaeyoung |\n");
	printf("+-----------------------------------------------------------------+\n");
}

void InputScreenVertex() {
	printf("+-----------------------------------------------------------------+\n");
	printf("|   �����ϱ� ���ؼ� Spanning Tree�� ������ �մϴ�.              |\n");
	printf("|   �Ʒ� ���Ŀ� ���� �Է��Ͻʽÿ�.                                |\n");
	printf("|---(1) vertex�� ������ �Է��Ͻʽÿ�. (��, 1<x<100 ������ ����  ) |\n");
	printf("|--->");
}

void ShowVertex(int vertices) {
	printf("+-----------------------------------------------------------------+\n");
	printf("|--- %d���� vertices ����                                          |\n", vertices);
	printf("|  ");
	for (int i = 0; i < vertices; i++) {
		printf("%d  ", i);
	}
	printf("\n+-----------------------------------------------------------------+\n");
}

void InputScreenEdge(int vertices) {
	int maxedgenum = vertices * (vertices - 1) / 2;
	printf("+-----------------------------------------------------------------+\n");
	printf("|---(2) edge�� ������ �Է��Ͻʽÿ�. (��, %d<x<%d�� �ؼ��Ͻʽÿ�)    |\n", vertices - 1, maxedgenum);
	printf("|--->");
}

void InputScreenEdgeWeight() {
	printf("+-----------------------------------------------------------------+\n");
	printf("|---(3) edge�� ���� ���Ŀ� ���߾� �Է��Ͻʽÿ�.                   |\n");
	printf("|--- (vertex1) (vertex2) (weight)                                 |\n");
	printf("|--- ex) 0 6 4  (0�� vertex�� 6�� vertex�� weight�� 4�� edge����) |\n");

}

int main(){
	int vertices, edges; //�����ϴ� vertex�� ����, edge�� ����

	InitialScreen();	//ó�� �ȳ�ȭ��
	InputScreenVertex();		//vertex ���� �Է�
	scanf_s("%d", &vertices);
	Init(vertices);

	ShowVertex(vertices);		//vertex ������ŭ vertex�̸��� ������ �ٿ���

	InputScreenEdge(vertices);	//edge ���� �Է� (��, vertex ������ ���� �ƽ��� ����)
	scanf_s("%d", &edges);

	InputScreenEdgeWeight();	//edge ������ŭ edge�� ����
	for (int i = 0; i < edges; i++) {
		printf("\n|--- %d��° edge �Է�: ", i+1);
		scanf_s("%d %d %d", &e[i].v1 , &e[i].v2, &e[i].weight);
	}

	sort(edges);		//edge�� weight ������ ���Ľ�����

	Kruskal(vertices, edges);		//Kruskal �˰����� ���� MSP�ϼ�
									//�ϼ� �� ���õ� edge�� ���, �׸��� weight ���� ���
	system("pause");
	return 0;
}
