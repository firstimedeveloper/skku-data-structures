#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

typedef struct {
	int pos;
	int b;
	int loc;
} Node;

typedef Node * Data;


void swap(Node* xp, Node* yp) 
{ 
	Node *temp = (Node *)malloc(sizeof(Node));
    *temp = *xp; 
    *xp = *yp; 
    *yp = *temp; 
	free(temp);
} 

int Partition(Data* list, int left, int right) {
	Node * pivot = list[left];
	int low = left + 1, high = right;
	while (1) {
		while (low < right && list[low] < pivot)
			low++; // Move low until pivot < L[low]
		while (high > left && list[high] >= pivot)
			high--; // Move high until pivot >= L[low]
		if (low < high)
		// Swap list[low] and list[high].
			swap(list[low], list[high]);
		else break;
	}
	swap(list[left], list[high]);
	return high;// return the pivot position.
}

void QuickSort(Data* list, int left, int right)
{
	if (left < right) {
		// The mid refers to the pivot position.
		int mid = Partition(list, left, right);
		// All elements are less than the pivot.
		QuickSort(list, left, mid - 1);
		// All elements are greater than the pivot.
		QuickSort(list, mid + 1, right);
	}
}

void BubbleSort(Data* list, int n) {
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			// Compare each pair of adjacent items.
			if (list[j]->b < list[j + 1]->b) {
				// Swap if they are in the wrong order.
				swap(list[j], list[j + 1]);
			}
		}
	}
}

void Sort(Data* list, int n) {
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			// Compare each pair of adjacent items.
			if (list[j]->loc > list[j + 1]->loc) {
				// Swap if they are in the wrong order.
				swap(list[j], list[j + 1]);
			}
		}
	}
}

int DeleteLamps(Data *list, bool* obs, int num) {
	int count = 0;
	
	for(int i=0; i<num; i++) {
        //printf("obs[list[i]->pos] %d %d\n", list[i]->pos, list[i]->b);
		if (obs[list[i]->pos]) continue;
		
		for(int j=i+1; j<num; j++) {
			if (obs[list[j]->pos]) continue;
			
			if (list[i]->loc - list[i]->b <= list[j]->loc-list[j]->b && list[j]->loc + list[j]->b <= list[i]->loc + list[i]->b) {
				//printf("useless\n");
                obs[list[j]->pos] = true;
				count++;
			}
		}
	}
	
	
	return num - count;
}


int main() {
	int numOfLamps;
	scanf(" %d", &numOfLamps);
	
	Node **nodes = (Node **)malloc(sizeof(Node *) * numOfLamps);
	
	for(int i=0; i<numOfLamps; i++) {
		int location, brightness;
		scanf(" %d %d", &location, &brightness);
		Node *node = (Node *)malloc(sizeof(Node));
		node->pos = i;
		node->b = brightness;
		node->loc = location;

		nodes[i] = node;
	}
	BubbleSort(nodes, numOfLamps);
	
	bool *obsolete = (bool *)malloc(sizeof(bool) * numOfLamps);
	for (int i=0; i<numOfLamps; i++) {
		obsolete[i] = false;
	}
	int count = DeleteLamps(nodes, obsolete, numOfLamps);
	
	Sort(nodes, numOfLamps);
	printf("%d\n", count);
	for (int i=0; i<numOfLamps; i++) {
		if (!obsolete[nodes[i]->pos])
			printf("%d ", nodes[i]->pos+1);
	}
	
	
}