#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void receive(char *path, char *in){
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
				printf("Received: %s", in);
				break;
			}
			i++;
		}
	fclose(input);
	return;
}

int send(char *path, char *out, char *name){
	printf("Send:	  ");
	char tmp[1005];
	strcpy(tmp, out);
	fgets(out ,1001, stdin);
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
	fputc('[', output);
	fwrite(name, 1, strlen(name), output);
	fputc(']', output);
	fputc(' ', output);
	fwrite(out, 1, strlen(out), output);
	fclose(output);
	return 1;
}

void main(int argc, char *argv[]){
	char *in = (char*) calloc(1005, sizeof(char));
	char *out = (char*) calloc(1005, sizeof(char));;
	int i = 0;
	int bool = 1;

	if(argc != 4){
		printf("Incorrect num of arguments.\n");
		return;
	}

	FILE *input;
	input = fopen(argv[argc-3], "r");
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
				printf("Received: %s", in);
				
				break;
			}
			i++;
		}
	}
	fclose(input);

	while(1){
		int tmp = send(argv[argc-2], out, argv[argc-1]);
		if(tmp == 0){
			return;
		}
		while(tmp == 2){
			tmp = send(argv[argc-2], out, argv[argc-1]);
			if(tmp == 0){
				return;
			}
		}
		receive(argv[argc-3], in);
	}
}
