#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encrypt(int key, char *path){
	char *data = (char*) calloc(1005, sizeof(char));
	
	strcpy(data, path);
	int i = strlen(data);
	
	for (int j = 0; j < i; j++){
		if(data[j] < 256 - key){
			data[j] = data[j] + key;
		}else{
			data[j] = data[j] - (256 - key);
		}
	}
	for(int k = 0; k < i/2+1; k++){
		char tmp = data[k];
		data[k] = data[i-1-k];
		data[i-1-k] = tmp;
	}
	return data;
}

char* decrypt(int key, char *path){
	char *data = (char*) calloc(1005, sizeof(char));
	
	strcpy(data, path);
	int i = strlen(data);
	
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
	return data;
}

void receive(int key, char *path, char *in){
	int bool = 1;
	int i = 0;
	FILE *input;
	input = fopen(path, "r");

	do{
		int j= 0;
		while(1){
			char c = fgetc(input);
			if(c == EOF){
				break;
			}
			if(in[j] != c){
				bool = 0;
				break;
			}
			j++;
		}
			fseek(input, 0, SEEK_SET);
		}while(bool == 1);
	memset(in, 0, strlen(in));
	while(1){
			in[i] = fgetc(input);
			if(feof(input)){
				in[i] = '\0';
				printf("Received: %s", decrypt(key, in));
				break;
			}
			i++;
		}
	fclose(input);
	return;
}

int send(int key, char *path, char *out, char *name){
	printf("Send:	  ");
	char tmp[1005], tmp2[1005], tmp3[1005], tmp4[1005];
	strcpy(tmp, out);
	fgets(out ,1001, stdin);
	strcpy(tmp2, out);
	strcpy(tmp3, "[");
	strcat(tmp3, name);
	strcpy(tmp4, "] ");
	strcat(tmp3, tmp4);
	strcat(tmp3, tmp2);
	strcpy(tmp2, encrypt(key, tmp3)); 
	if(feof(stdin)){
		return 0;
	}
	for(int i = 0; i < strlen(out); i++){
		if(tmp[i] != out[i]){
			break;
		}else if(i == strlen(out) - 1){
			return 2;
		}
	}

	FILE *output;
	output = fopen(path, "w");
	fwrite(tmp2, 1, strlen(tmp2), output);
	fclose(output);
	return 1;
}

void main(int argc, char *argv[]){
	char *in = (char*) calloc(1005, sizeof(char));
	char *out = (char*) calloc(1005, sizeof(char));;
	int i = 0;
	int bool = 1;
	int key = strtol (argv[argc-1], NULL, 10);

	if(argc != 5){
		printf("Incorrect num of arguments.\n");
		return;
	}

	FILE *input;
	input = fopen(argv[argc-4], "r");
	if(input == NULL){
		printf("Nothing received yet.\n");
		input = fopen(argv[argc-3], "w");
	}else{
		while(1){
			in[i] = fgetc(input);
			if(feof(input) && i == 0){
				printf("Nothing received yet.\n");
				break;
			}else if(feof(input)){
				in[i] = '\0';
				printf("Received: %s", decrypt(key, in));			
				break;
			}
			i++;
		}
	}
	fclose(input);
	
	while(1){
		int tmp = send(key, argv[argc-3], out, argv[argc-2]);
		if(tmp == 0){
			return;
		}
		while(tmp == 2){
			tmp = send(key, argv[argc-3], out, argv[argc-2]);
			if(tmp == 0){
				return;
			}
		}
		receive(key, argv[argc-4], in);
	}
}
