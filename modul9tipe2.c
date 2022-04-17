// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 64

int fileToSize(char filename[]){
    char line[MAX_LEN], text[MAX_LEN][MAX_LEN];
    char* token;

    FILE* myfile = fopen(filename, "r");

    int i = 0;
    while(fgets(line, MAX_LEN, myfile)) {
        token = strtok(line, "\n");        
        strcpy(text[i], token);
        ++i;
    }

    fclose(myfile);
	
	return atoi(text[0]);
}

void isFileValid(char filename[]){
    FILE* myfile = fopen(filename, "r");

    if(myfile == NULL){
      printf("Error: file invalid!");   
      exit(1);             
    }
}

void printFile(char filename[]){
    int i=0, j;
    char line[MAX_LEN], text[MAX_LEN][MAX_LEN];
    char* token;

    FILE* myfile = fopen(filename, "r");

    while(fgets(line, MAX_LEN, myfile)) {
        token = strtok(line, "\n");
        printf("%s\n", token);
        ++i;
    }
    
    fclose(myfile);
}

void fileToArr(int size, char filename[], int arr[size][size]){
    int i=0, j;
    char line[MAX_LEN], text[MAX_LEN][MAX_LEN];
    char* token;

    FILE* myfile = fopen(filename, "r");

    while(fgets(line, MAX_LEN, myfile)) {
        token = strtok(line, "\n");
        strcpy(text[i], token);
        ++i;
    }

    for (i=0;i<size;i++){
        for (j=0;j<size;j++){
            arr[i][j] = (text[i+1][(2*j)])-48;
        }
    }
    
    fclose(myfile);
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void DFD(int size, int path[size], int l, int r, int arr[size][size], int *count, char outFile[]){
    int i, j, valid;

    if (l == r){
        valid = 1;
        for(j=0;j<size-1&&valid==1;j++){
            valid = arr[path[j]][path[j+1]];
        }
        if(valid==1){
            FILE* myfile = fopen(outFile, "a");
            for(j=0;j<size-1;j++){
                fprintf(myfile, "%d-", path[j]);
            }
            fprintf(myfile, "%d\n", path[size-1]);
            *count=*count + 1;
            fclose(myfile);
        }
    } else {
        for (i = l; i <= r; i++)
        {
            swap((path+l), (path+i));
            DFD(size, path, l+1, r, arr, count, outFile);
            swap((path+l), (path+i));
        }
    }
}

void hPath(int size, int arr[size][size], char filename[]){
    int i, j, node[size], count=0;

    for(i=0;i<size;i++){
        node[i]=i;
    }
    
    char outFile[MAX_LEN]="jalur-";
    strcat(outFile, filename);
    FILE* myfile = fopen(outFile, "w"); fclose(myfile);

    DFD(size, node, 0, size-1, arr, &count, outFile);
    printf("Banyak Hamilton Path: %d\nHamilton Path:\n", count);
    if (count==0) {
        FILE* myfile = fopen(outFile, "a");
        fprintf(myfile, "Tidak Ada Hamilton Path");
        fclose(myfile);
    }
    printFile(outFile);
}

int main() {
    int size;
    char filename[MAX_LEN];

    printf("Masukkan nama file: ");
    scanf("%s", &filename);

    isFileValid(filename);

    size = fileToSize(filename);
    int arr[size][size];
    fileToArr(size, filename, &arr);

    hPath(size, arr, filename);

    return 0;
}
