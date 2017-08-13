#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

struct Node {
	int data;
	struct Node* next;
};

void addEdge (struct Node** head, int data) {
	while ((*head)->next != NULL)
		head = &((*head)->next);
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->data = data;
	node->next = NULL;
	(*head)->next = node;
	head = &((*head)->next);
}

void topoSort (struct Node* adjlist[], int vertex, int visited[], int stack[], int* top) {
	if (visited[vertex] == 1)
		return;
	visited[vertex] = 1;
	struct Node** head = &adjlist[vertex];
	while ((*head)->next != NULL)
		head = &((*head)->next);
	struct Node** node = &adjlist[vertex];
	if ((*node)->next != NULL)
		do {
			topoSort(adjlist,(*node)->next->data,visited,stack,top);
			node = &((*node)->next);
		} while (node != head);
	stack[(*top)++] = vertex;
}

void topoWrap (struct Node* adjlist[]) {
	int visited[SIZE] = {0}, stack[SIZE];
	int* top = (int *)malloc(sizeof(int));
	*top = -1;
	for (int i=0;i<SIZE;i++) {
		if (!visited[i])
			topoSort(adjlist,i,visited,stack,top);
	}
	while ((*top)>-1)
		printf("%d\n",stack[--(*top)]);
}

int main () {
	struct Node* adjlist[SIZE];
	struct Node** head[SIZE];
	for (int i=0;i<SIZE;i++) {
		adjlist[i] = (struct Node*)malloc(sizeof(struct Node));
		adjlist[i]->data = i;
		adjlist[i]->next = NULL;
		head[i] = &adjlist[i];
	}
	addEdge(head[5],0);
	addEdge(head[5],2);
	addEdge(head[2],3);
	addEdge(head[3],1);
	addEdge(head[4],0);
	addEdge(head[4],1);
	addEdge(head[0],1);
	topoWrap(adjlist);
	return 0;
}
