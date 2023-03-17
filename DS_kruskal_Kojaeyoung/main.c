#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100	//최대 vertex의 개수를 100으로 정함
#define MAX_EDGES 4950		//최대 edge의 개수 정함
#define SWAP(a,b)  {int temp; temp = a; a = b; b = temp;}	//a와 b를 교환해주는 스왑함수

typedef struct Edge{		//Edge란 구조체 선언 - 2개의 vertex와 weight값
	int v1;
	int v2;
	int weight;
}Edge;

int parent[MAX_VERTICES];		//각 vertex의 패런트 노드
Edge e[MAX_EDGES];				//edge에 관한 배열


void Init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;		//패런트 노드 초기화
	}
}

void Union(int p1, int p2) {		//forest에서 두 트리를 연결 매개변수는 두 트리 각각의 루트노드
	if (p1 < p2)
		parent[p2] = p1;
	else
		parent[p1] = p2;
}

int Find(int v) {		//vertex가 어떤 트리에 속하는 지, 해당 트리의 root 노드를 반환
	while (parent[v] >= 0) {
		v = parent[v];
	}
	return v;
}


void sort(int edges) {		//Edge 리스트를 weight 순서대로 정렬시켜 줌
	for (int i = edges; i > 1; i--) {	//소팅의 알고리즘은 편하게 버블소팅으로 함.
		for (int j = 1; j < i; j++){
			if (e[j - 1].weight > e[j].weight){
				SWAP(e[j - 1].weight, e[j].weight);
				SWAP(e[j - 1].v1, e[j].v1);
				SWAP(e[j - 1].v2, e[j].v2);
			}
		}
	}
}


int CheckCycle(int v1, int v2) {		//cycle 판별 함수 - 두 vertices에 대해 find통해 조상같으면 cycle임

	if (Find(v1) == Find(v2)) {		//두 vertex에 대해 같은 집합에 속해있는가?
		//같은 집합에 속해있으면 cycle이 형성될 것임
		return 0;
	}
	else {
		//그렇지 않다면 같은 집합에 속해있지 않아 cycle 형성안해서 괜찮음.
		Union(Find(v1), Find(v2));
		return 1;
	}
}


void Kruskal(int vertices, int edges) {
	int weightcount = 0;		//MST의 weight값 출력할거임
	int edgecount = 0;			//edgecount가 vertex개수 - 1이 되면 종료할 거임

	printf("+-----------------------------------------------------------------+\n");


	for (int i = 0; i < edges && edgecount != vertices - 1; i++) {
		if (CheckCycle(e[i].v1, e[i].v2)) {		//사이클 형성하지 않는다면
			edgecount += 1;
			weightcount += e[i].weight;
			printf("|-- 선택된 %d번째 edge: vertex(%d) <--> vertex(%d)  ::||:: weight (%d)|\n", edgecount, e[i].v1, e[i].v2, e[i].weight);
		}
		else {		//사이클을 형성하면 거부
			printf("|/// 거부된 edge: vertex (%d) <--> vertex (%d)                   ///|\n", e[i].v1, e[i].v2);
		}
	}
	printf("+-----------------------------------------------------------------+\n");
	printf("|---완성된 MST의 weight 총합은 : %d 입니다.                   -----|\n", weightcount);
	printf("|   MST의 edge들과 weight 총합 출력으로 완료 했습니다.            |\n");
	printf("|---> 프로그램을 종료합니다.                                      |\n");
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
	printf("|   진행하기 위해서 Spanning Tree를 만들어야 합니다.              |\n");
	printf("|   아래 형식에 따라 입력하십시오.                                |\n");
	printf("|---(1) vertex의 개수를 입력하십시오. (단, 1<x<100 범위로 제한  ) |\n");
	printf("|--->");
}

void ShowVertex(int vertices) {
	printf("+-----------------------------------------------------------------+\n");
	printf("|--- %d개의 vertices 생성                                          |\n", vertices);
	printf("|  ");
	for (int i = 0; i < vertices; i++) {
		printf("%d  ", i);
	}
	printf("\n+-----------------------------------------------------------------+\n");
}

void InputScreenEdge(int vertices) {
	int maxedgenum = vertices * (vertices - 1) / 2;
	printf("+-----------------------------------------------------------------+\n");
	printf("|---(2) edge의 개수를 입력하십시오. (단, %d<x<%d를 준수하십시오)    |\n", vertices - 1, maxedgenum);
	printf("|--->");
}

void InputScreenEdgeWeight() {
	printf("+-----------------------------------------------------------------+\n");
	printf("|---(3) edge를 다음 형식에 맞추어 입력하십시오.                   |\n");
	printf("|--- (vertex1) (vertex2) (weight)                                 |\n");
	printf("|--- ex) 0 6 4  (0번 vertex와 6번 vertex를 weight값 4인 edge연결) |\n");

}

int main(){
	int vertices, edges; //생성하는 vertex의 개수, edge의 개수

	InitialScreen();	//처음 안내화면
	InputScreenVertex();		//vertex 개수 입력
	scanf_s("%d", &vertices);
	Init(vertices);

	ShowVertex(vertices);		//vertex 개수만큼 vertex이름이 정수로 붙여짐

	InputScreenEdge(vertices);	//edge 개수 입력 (단, vertex 개수에 따라 맥스값 제한)
	scanf_s("%d", &edges);

	InputScreenEdgeWeight();	//edge 개수만큼 edge를 설정
	for (int i = 0; i < edges; i++) {
		printf("\n|--- %d번째 edge 입력: ", i+1);
		scanf_s("%d %d %d", &e[i].v1 , &e[i].v2, &e[i].weight);
	}

	sort(edges);		//edge의 weight 순으로 정렬시켜줌

	Kruskal(vertices, edges);		//Kruskal 알고리즘을 통해 MSP완성
									//완성 시 선택된 edge들 출력, 그리고 weight 총합 출력
	system("pause");
	return 0;
}
