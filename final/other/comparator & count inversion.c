#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
 char id[20]; // Mã hồ sơ ID
 int priority; // Mức ưu tiên P
 int deadline; // Hạn xử lý D (số ngày còn lại)
 int processingTime; // Thời gian xử lý dự kiến T
} Profile;

void swap(int* a, int* b)
{
 
    int temp = *a;
    *a = *b;
    *b = temp;
}

int merge(int arr[], Profile** list, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
	int count = 0;
    while (i < n1 && j < n2) {
        if (compare(list[L[i]], list[R[j]]) >= 0) {
            arr[k] = L[i];
            i++;
        }
        else {
			count += n1 - i;
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

	return count;
}
 
// l is for left index and r is right index of the
// sub-array of arr to be sorted
int mergeSort(int arr[], Profile** list, int l, int r){
	int count = 0;
	if (l < r) {

        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        count += mergeSort(arr, list, l, m);
        count += mergeSort(arr, list, m + 1, r);
 
        count += merge(arr, list, l, m, r);
    }
	return count;
}

Profile* createProfile(char* id, int p, int d, int t){
	Profile* new = (Profile*) malloc(sizeof(Profile));

	strcpy(new->id,id);
	new->priority = p;
	new->deadline = d;
	new->processingTime = t;

	return new;
}

int compare(Profile* p1, Profile* p2){
	if(p1->priority > p2->priority){
		return 1;
	}
	else if(p1->priority == p2->priority){
		if(p1->deadline < p2->deadline){
			return 1;
		} 
		else if(p1->deadline == p2->deadline){
			if(p1->processingTime > p2->processingTime){
				return 1;
			}
			else if(p1->processingTime == p2->processingTime){
				return 0;
			}
		}
	}
	return -1;
}

int main(){
	
	int n;
	scanf("%d\n", &n);

	Profile** list = (Profile**) malloc(sizeof(Profile*) * n);

	for(int i = 0; i < n; i++){
		char* line = (char*) calloc(50,sizeof(char));
    	fgets(line,50,stdin);

		char* cmd = strtok(line," ");
    	int cmd2 = atoi(strtok(NULL," "));
		int cmd3 = atoi(strtok(NULL," "));
		int cmd4 = atoi(strtok(NULL," "));

		list[i] = createProfile(cmd,cmd2,cmd3,cmd4);

		free(line);
	}

	int index[n];
	for(int i = 0; i < n; i++){
		index[i] = i;
	}

	int count = mergeSort(index, list, 0, n-1);

	printf("%d\n", count);
	for(int i = 0; i < n; i++){
		printf("%s\n", list[index[i]]->id);
	}

  return 0;
}


