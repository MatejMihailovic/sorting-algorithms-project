#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 100
#define MAXL1 21
#define MAXL2 1000

FILE *safe_open(char *fileName, char *mode);
void clearInputBuffer();
int getUserInput(); 
//A
void insertArray(int *arr_size, int arr[]);
void insertionSort(int arr_size, int arr[]);
void printArr(int arr[], int arr_size);
//B
typedef struct{
	char firstName[MAXL1];
	char lastName[MAXL1];
	int height;
}player;

int maxHeight(player players[], int players_num);
int minHeight(player players[], int players_num);
void swapPlayerValues(player players[], int a, int b);
void loadPlayers(FILE *pf, player players[], int players_num);
void printPlayers(player players[], int players_num);
void heapify(player players[], int players_num, int i);
void heapSort(player players[], int players_num);
void countingSort(int players_num, player players[]);

//C
typedef struct{
	double xcoord;
	double ycoord;
}dot;

void swapDotValues(dot dots[], int a, int b);
int loadDots(FILE *pf, dot dots[]);
int partition(dot dots[], int low, int high);
void quickSort(dot dots[], int low, int high, int counter);
void selectionSort(dot dots[], int low, int high);
void printDots(dot dots[], int dots_num);

int main(){
	int arr[MAXL], counter = 1;
	int arr_size, players_num, dots_num;
	char option1;
	player players[MAXL2];
	dot dots[MAXL2];
	do{
	puts("--------------------");
	fflush(stdin);
	printf("A. Insertion sort input array\nB. Heap and Counting sort players by height\nC. Quick sort dots\nChoose your option:");
	option1 = getUserInput();

	switch(option1){
			case 'A':{
			insertArray(&arr_size, arr);
			puts("--------------------");
			insertionSort(arr_size, arr);
			puts("--------------------");
			}break;
			case 'B':{
			FILE *f1 = safe_open("players.txt","r");
			puts("--------------------");
			fscanf(f1,"%d",&players_num);
			loadPlayers(f1, players, players_num);

			if ((players_num / 20) < (maxHeight(players, players_num) - minHeight(players, players_num))){ 
				heapSort(players, players_num);
				printPlayers(players, players_num);
			}else{
				countingSort(players_num, players);
				printPlayers(players, players_num);
			}
			fclose(f1);
			puts("--------------------");
			}break;
			case 'C':{
			FILE *f2 = safe_open("dots.txt","r");
			dots_num = loadDots(f2, dots);
			puts("--------------------");
			quickSort(dots, 0, dots_num-1, counter);
			printDots(dots, dots_num);
			fclose(f2);
			puts("--------------------");
			}break;
			default: exit(0);
		}
	}while (1);

	return 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getUserInput() {
    int c;
    do {
        c = getchar();
        clearInputBuffer(); // Clear buffer in case of extra characters
    } while (c == '\n' || c == EOF); // Skip newlines and EOF
    return c;
}

int maxHeight(player players[], int players_num){
	int i;
	int max = players[0].height;
	for(i = 1; i < players_num; i++){
		if(max < players[i].height){
			max = players[i].height;
		}
	}
	return max;
}

int minHeight(player players[], int players_num){
	int i;
	int minHeight = players[0].height;
	for(i = 1; i < players_num; i++){
		if(minHeight > players[i].height){
			minHeight = players[i].height;
		}
	}
	return minHeight;
}

FILE *safe_open(char *fileName, char *mode){
	FILE *pf = fopen(fileName, mode);
	if(pf == NULL){
		puts("File couldn't be open!");
		exit(1);
	}
	return pf;
}

void loadPlayers(FILE *pf, player players[], int players_num){
	int i;
	for(i = 0; i < players_num; i++){
		fscanf(pf,"%s %s %d", players[i].firstName, players[i].lastName, &players[i].height);
	}
}

int loadDots(FILE *pf, dot dots[]){
	int dots_num = 0;
	while((fscanf(pf,"%lf %lf",&dots[dots_num].xcoord,&dots[dots_num].ycoord))!=EOF){
			dots_num++;
		}
	return dots_num;
}

void insertArray(int *arr_size, int arr[]){
	int i;
	printf("Insert number of elements: "); scanf("%d",arr_size);
	printf("Insert array elements:\n");
	for(i = 0; i < *arr_size; i++){
		printf("arr[%d] = ",i);
		scanf("%d",&arr[i]);
	}
}

void insertionSort(int arr_size, int arr[]){
	int i, j, key;
	for(i = 1; i < arr_size; i++){
		key = arr[i];  
		j = i-1;
		while(j >= 0 && arr[j] > key){
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
	printArr(arr, arr_size);
}

void printArr(int arr[], int arr_size){
	int i;
	puts("Sorted array:");
	for(i = 0; i < arr_size; i++){
		printf("arr[%d] = %d\n", i, arr[i]);
	}
}

void countingSort(int players_num, player players[]){
	int i,j,max;
	int b = 0; 
	int k = players_num - 1;
	max = maxHeight(players, players_num);
	int counter[max];
	player a[players_num];
	for(i = 0; i <= max; ++i){
		counter[i] = 0;
	}
	for(i = 0; i < players_num; i++){
		counter[players[i].height]++;
	}
	for(i = 1 ; i <= max; i++){
		counter[i] += counter[i-1];
	}
	for(i=players_num-1;i>=0;i--){
		strcpy(a[counter[players[i].height]-1].firstName,players[i].firstName);
		strcpy(a[counter[players[i].height]-1].lastName,players[i].lastName);
		a[counter[players[i].height]-1].height = players[i].height;
		counter[players[i].height]--;
	}
	for(i = players_num-1; i >= 0; i--){
		strcpy(players[b].firstName,a[i].firstName);
		strcpy(players[b].lastName,a[i].lastName);
		players[b].height = a[i].height;
		b++;
	}
}

void swapPlayerValues(player players[], int a, int b){
	if((strcmp(players[a].firstName, players[b].firstName) != 0) && (strcmp(players[a].lastName, players[b].lastName) != 0)){
	player temp[MAXL];
	temp[0] = players[a];
	players[a] = players[b];
	players[b] = temp[0];
	}else
	return;
}

void swapDotValues(dot dots[], int a, int b){
	dot temp[MAXL];
	temp[0] = dots[a];
	dots[a] = dots[b];
	dots[b] = temp[0];
}

void heapify(player players[], int players_num, int i){
    int minHeight = i;
    int left,right; 
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (left < players_num && players[left].height < players[minHeight].height)
      minHeight = left;
    if (right < players_num && players[right].height < players[minHeight].height)
      minHeight = right;
    if (minHeight != i) {
      swapPlayerValues(players, i, minHeight);
      heapify(players, players_num, minHeight);
    }
}

void heapSort(player players[], int players_num){
    for (int i = players_num / 2 - 1; i >= 0; i--){
      heapify(players, players_num, i);
    }
    for (int i = players_num - 1; i > 0; i--){
      swapPlayerValues(players, 0, i);
      heapify(players, i, 0);
    }
}

int partition(dot dots[], int low, int high){
	dot pivot[1];
	pivot[0].xcoord = dots[high].xcoord;
	pivot[0].ycoord = dots[high].ycoord;
  	int i = low - 1;
  	int j;
  	for (j = low; j < high; j++) {
    	if ((dots[j].xcoord < pivot[0].xcoord)||((dots[j].xcoord == pivot[0].xcoord)&&(dots[j].ycoord < pivot[0].ycoord))){
      		i++;
      		swapDotValues(dots, i, j);
		}
    }
  swapDotValues(dots, i+1, high);
  return (i + 1);
}

void quickSort(dot dots[], int low, int high,int counter){
	if(low < high){
	//pi is pivot element, left from him are smaller elements, 
	//right from him are bigger elements
    int pi = partition(dots, low, high);
	//If rec. depth passes 5, inside quicksort we call selection sort 
	//which sorts rest of arr that isn't
    	if(counter > 5){//
			selectionSort(dots,low,high);
			printf("%d %d \n",low,high);
		}
    quickSort(dots, low, pi - 1, counter+1);
    quickSort(dots, pi + 1, high, counter+1);
    }
}

void selectionSort(dot dots[], int low, int high){
    int i, j, min_idx;
    for (i = low; i < high-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < high; j++)
  			if ((dots[j].xcoord < dots[min_idx].xcoord)||((dots[j].xcoord == dots[min_idx].xcoord)&&(dots[j].ycoord < dots[min_idx].ycoord)))
            min_idx = j;
            
        swapDotValues(dots, min_idx, i);
    }
}

void printPlayers(player players[], int players_num){
	int i;
	for(i = 0; i < players_num; i++){
		printf("%s %s %d\n",players[i].firstName, players[i].lastName, players[i].height);
	}
}

void printDots(dot dots[], int dots_num){
	int i;
	for(i = 0; i < dots_num; i++){
		printf("%.2lf %.2lf\n",dots[i].xcoord, dots[i].ycoord);
	}
}

