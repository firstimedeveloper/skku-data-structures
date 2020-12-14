#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500000

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
	int pivot = list[left]->loc;
	int low = left + 1, high = right;
	while (1) {
		while (low < right && list[low]->loc < pivot)
			low++; // Move low until pivot < L[low]
		while (high > left && list[high]->loc >= pivot)
			high--; // Move high until pivot >= L[low]
		if (low < high)
		// Swap list[low] and list[high].
			swap(list[low], list[high]);
		else break;
	}
	swap(list[left], list[high]);
	return high;// return the pivot position.
}
int Partitionb(Data* list, int left, int right) {
	int pivot = list[left]->b;
	int low = left + 1, high = right;
	while (1) {
		while (low < right && list[low]->b < pivot)
			low++; // Move low until pivot < L[low]
		while (high > left && list[high]->b >= pivot)
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

void QuickSortb(Data* list, int left, int right)
{
	if (left < right) {
		// The mid refers to the pivot position.
		int mid = Partitionb(list, left, right);
		// All elements are less than the pivot.
		QuickSort(list, left, mid - 1);
		// All elements are greater than the pivot.
		QuickSort(list, mid + 1, right);
	}
}


void Merge(Data* list, int left, int mid, int right) {
	Node* sorted[MAX_SIZE];
	int first = left, second = mid + 1, i = left;
	// Merge two lists by comparing elements in sequence.
	while (first <= mid && second <= right) {
		if (list[first]->loc <= list[second]->loc)
			sorted[i++] = list[first++];
		else
			sorted[i++] = list[second++];
	}
	// For remaining items, add them in sequence.
	if (first > mid)
		for (int j = second; j <= right; j++)
			sorted[i++] = list[j];
	else
		for (int j = first; j <= mid; j++)
			sorted[i++] = list[j];
	// Copy the sorted list to the list.
	for (int j = left; j <= right; j++)
		list[j] = sorted[j];
}

void Mergeb(Data* list, int left, int mid, int right) {
	Node* sorted[MAX_SIZE];
	int first = left, second = mid + 1, i = left;
	// Merge two lists by comparing elements in sequence.
	while (first <= mid && second <= right) {
		if (list[first]->b >= list[second]->b)
			sorted[i++] = list[first++];
		else
			sorted[i++] = list[second++];
	}
	// For remaining items, add them in sequence.
	if (first > mid)
		for (int j = second; j <= right; j++)
			sorted[i++] = list[j];
	else
		for (int j = first; j <= mid; j++)
			sorted[i++] = list[j];
	// Copy the sorted list to the list.
	for (int j = left; j <= right; j++)
		list[j] = sorted[j];
}

void IterMergeSort(Data* list, int n) {
	// Merge subarrays in bottom up manner. First merge subarrays of
	// size 1 to create sorted subarrays of size 2, then merge subarrays
	// of size 2 to create sorted subarrays of size 4, and so on.
	for (int size = 1; size <= n - 1; size = 2 * size) {
		// Pick starting point of different subarrays of current size
		for (int left_start = 0; left_start < n - 1; left_start += 2 * size) {
			// Find ending point of left subarray.
			// mid+1 is starting point of right
			int mid = left_start + size - 1;
			int right_end;
			if (left_start + 2 * size -1 < n-1) 
				right_end = left_start + 2 * size -1;
			else right_end = n - 1;
			//int right_end = MIN(left_start + 2 * size - 1, n - 1);
			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
			Merge(list, left_start, mid, right_end);
		}
	}
}

void MergeSort(Data* list, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2; // Equal partitioning
		MergeSort(list, left, mid); // Sorting sublists
		MergeSort(list, mid + 1, right); // Sorting sublists
		Merge(list, left, mid, right); // Merging two sublists
	}
}

void MergeSortb(Data* list, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2; // Equal partitioning
		MergeSort(list, left, mid); // Sorting sublists
		MergeSort(list, mid + 1, right); // Sorting sublists
		Mergeb(list, left, mid, right); // Merging two sublists
	}
}



int DeleteLamps(Data *list, bool* obs, int num) {
	int count = 0;
	
	for(int i=0; i<num; i++) {
        //printf("obs[list[i]->pos] %d %d\n", list[i]->pos, list[i]->b);
		if (obs[list[i]->pos]) continue;
		if (list[i]->b == 1) continue;
		
		for(int j=0; j<num; j++) {
			if (list[i]->b < list[j]->b || j==i) continue;
			if (obs[list[j]->pos]) continue;
			
			if (list[i]->loc - list[i]->b <= list[j]->loc-list[j]->b && list[j]->loc + list[j]->b <= list[i]->loc + list[i]->b) {
				//printf("useless\n");
                obs[list[j]->pos] = true;
				count++;
			}
			if (list[j]->loc - list[j]->b <= list[i]->loc-list[i]->b && list[i]->loc + list[i]->b <= list[j]->loc + list[j]->b) {
				//printf("useless\n");
                obs[list[i]->pos] = true;
				count++;
			}
		}
	}
	
	
	return num-count;
}


int main() {
	int numOfLamps;
	scanf(" %d", &numOfLamps);
	//Node *nodes[MAX_SIZE];
	Node **nodes = (Node **)malloc(sizeof(Node) * numOfLamps);

    int brightness[MAX_SIZE];
    int location[MAX_SIZE];
	
	
	for(int i=0; i<numOfLamps; i++) {
		int location, brightness;
		scanf(" %d %d", &location, &brightness);
		Node *node = (Node *)malloc(sizeof(Node));
		node->pos = i;
		node->b = brightness;
		node->loc = location;

		nodes[i] = node;
	}
	bool *obsolete = (bool *)malloc(sizeof(bool) * numOfLamps);
	for (int i=0; i<numOfLamps; i++)
		obsolete[i] = false;
	int count = DeleteLamps(nodes, obsolete, numOfLamps);
	
	MergeSort(nodes, numOfLamps-1);
	printf("%d\n", count);
	for (int i=0; i<numOfLamps; i++) {
		if (!obsolete[nodes[i]->pos])
			printf("%d ", nodes[i]->pos+1);
	}
	
	free(obsolete);
	free(nodes);
	
}