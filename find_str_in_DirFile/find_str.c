#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define MAXLinelen 1024

int strStack[256];

//find str in directory
void strDir();


int main(){
	strDir();
}

void strDir(){

	int count = 0;
	char countchar[100];
	char *targetStr = "test";
	char *filename = NULL;
	char filenameTemp[32];
	char resultStr[256];
	struct 	dirent *de;


	DIR *dr = opendir(".");
	if(dr == NULL){
		perror("dr not exist or can't access!");
		return;
	}
	

	strcpy(resultStr, "./");
	while((de = readdir(dr)) != NULL ){
		char filecontext[1024];
		filename = malloc(strlen(de->d_name)+1);
		filename = de->d_name;
		printf("filename = de->name: %s\n", filename);

		FILE *fp = fopen(filename, "r");
		if(fp == NULL){
			perror("open file fail");
			return;
		}
		while(fgets(filecontext, MAXLinelen, fp) != NULL){
			int index = 0;
			char *ret;
			while((ret = strstr(filecontext+index, targetStr)) != NULL){
				strcpy(filenameTemp, filename);
				strcat(filenameTemp, " ");

				count ++;
				index = ret-filecontext + 1;
			}
		}
		strcat(resultStr, filenameTemp);
		memset(filenameTemp, 0, strlen(filenameTemp)+1);
	}
	sprintf(countchar, "Count:%d", count);
	strcat(resultStr, countchar);
	printf("result = %s\n",resultStr);
	return;
}
