// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 200

int fileToSize(char filename[]){
    char line[MAX_LEN], text[MAX_LEN][MAX_LEN];
    char* token;

    // Membaca file
    FILE* myfile = fopen(filename, "r");

    // Output apabila file kosong
    if(myfile == NULL){
      printf("Error : file tidak ada");   
      exit(1);             
   }

   int i = 0;
    while(fgets(line, MAX_LEN, myfile)) {
        token = strtok(line, "\n");        
        strcpy(text[i], token);
        ++i;
    }

    // Menutup file
    fclose(myfile);
	
	return atoi(text[0]);
}

void printFile(char filename[]){
    int i=0, j;
    char line[MAX_LEN], text[MAX_LEN][MAX_LEN];
    char* token;

    // Membaca file
    FILE* myfile = fopen(filename, "r");

    while(fgets(line, MAX_LEN, myfile)) {
        token = strtok(line, "\n");
        printf("%s\n", token);
        ++i;
    }
    // Menutup file
    fclose(myfile);
}

void fileToArr(int size, char filename[], int arr[size][size]){
	
    // Kamus
    int i=0, j;
    char line[MAX_LEN], text[MAX_LEN][MAX_LEN];
    char* token;

    // Membaca file
    FILE* myfile = fopen(filename, "r");

    // Output apabila file kosong
    if(myfile == NULL){
      printf("Error : file tidak ada");   
      exit(1);             
   }

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

    // Menutup file
    fclose(myfile);
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void permutasi(int size, int a[size], int l, int r, int arr[size][size], int *count, char outFile[]){
    int i, j, valid;

    if (l == r){
        valid = 1;
        for(j=0;j<size-1&&valid==1;j++){
            valid = arr[a[j]][a[j+1]];
        }
        if(valid==1){
            FILE* myfile = fopen(outFile, "a");
            for(j=0;j<size-1;j++){
                fprintf(myfile, "%d-", a[j]);
            }
            fprintf(myfile, "%d\n", a[size-1]);
            *count=*count + 1;
            fclose(myfile);
        }
    } else {
        for (i = l; i <= r; i++)
        {
            swap((a+l), (a+i));
            permutasi(size, a, l+1, r, arr, count, outFile);
            swap((a+l), (a+i)); //backtrack
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

    permutasi(size, node, 0, size-1, arr, &count, outFile);
    printf("Banyak Hamilton Path: %d\nHamilton path:\n", count);
    if(count==0){printf("Tidak Ada Hamilton Path");}
    else{printFile(outFile);};
}

int main(){
    int size;
    char filename[MAX_LEN];

    printf("Masukkan nama file: ");
    scanf("%s", &filename);

    size = fileToSize(filename);
    int arr[size][size];
    fileToArr(size, filename, &arr);

    /*for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }*/

    hPath(size, arr, filename);

    return 0;
}