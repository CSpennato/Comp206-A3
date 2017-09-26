#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int crack(int key, char path[]){
	int i = 0;
	char data[1005];
	char *data2 = (char*) calloc(1005, sizeof(char));
	
	FILE *file;
	file = fopen(path, "r");
	if(file == NULL){
		printf("Error: The text file doesn't exist \n");
		return 0;
	}
	do{
		data[i] = fgetc(file);
		if(data[i] == '\0'){
			break;
		}else if(feof(file) && i == 0){
			printf("Error, the text file is empty \n");
			return 0;
		}
		i++;
	}while(1);
	fclose(file);
	
	for (int j = 0; j < i; j++){
		if(data[j] > key - 1){
			data[j] = data[j] - key;
		}else{
			data[j] = data[j] + (256 - key);
		}
	}
	for(int k = 0; k < i/2+1; k++){
		char tmp = data[k];
		data[k] = data[i-1-k];
		data[i-1-k] = tmp;
	}

	int bool = 1;
	for(int j = 0; j < i; j++){
		if(data[j] != ' ' && (data[j] > 122 || data[j] < 65 || (data[j]>90 && data[j] <97))) {
			bool = 0;
			break;	
			}
	}
	if(bool == 1){
		printf("%d\n", key);
		for(int l = 0; l <= i; l++){
			printf("%c", data[l]);
			}
		printf("\n");
	}
	return bool;
}

void main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error: Incorrect number of arguments \n");
		return;
	}

	char *path = argv[argc-1];
	char *answer;
	int z,y = 0;

	for(int i = 0; i <=255; i++){
		if(crack(i, path) == 1){
			return;
		}	
	}
}


