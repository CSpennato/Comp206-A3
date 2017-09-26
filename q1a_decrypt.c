#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
	if(argc != 3){
		printf("Error: Incorrect number of arguments \n");
		return;
	}

	int key = strtol (argv[argc-2], NULL, 10);
	int i = 0;
	char data[1005];
	char *path = argv[argc-1];
	
	FILE *file;
	file = fopen(path, "r");
	if(file == NULL){
		printf("Error: The text file doesn't exist \n");
		return;
	}
	do{
		data[i] = fgetc(file);
		if(data[i] == '\0'){
			break;
		}else if(feof(file) && i == 0){
			printf("Error, the text file is empty \n");
			return;
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
	for(int l = 0; l <= i; l++){
		if(l != i){
			printf("%c", data[l]);
		}else{
			printf("%c \n", data[l]);
		}
	}
}
