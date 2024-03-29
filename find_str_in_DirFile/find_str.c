#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "find_str.h"

#define MAXLinelen 1024


//find str in directory
Task* strDir(Task *task);

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("you should enter ./ str dir");
		return -1;
	}

	char countchar[100];
	Task *task = malloc(sizeof(struct Task));
	task->target = argv[1];
	task->dir = argv[2];
	task->fileN = malloc(sizeof(char)*255);
	memset(task->fileN, 0, sizeof(task->fileN));
	task = strDir(task);
	sprintf(countchar, "Count:%d", task->count);
	strcat(task->fileN,countchar);
	printf("main result :%s\n",task->fileN);
}

Task* strDir(Task *task){

	int count = 0;
	char *Dir = NULL;
	char *targetStr = task->target;
	char *filename = NULL;
	char *filepath = NULL;
	char filenameTemp[32];
	char resultStr[256];
	struct 	dirent *de;




	memset(resultStr, 0, sizeof(resultStr));
	memset(filenameTemp, 0, sizeof(filenameTemp));

	if(strstr(task->dir,"./") == NULL){
		//recur 1
		if(strcmp(task->dir,".") == 0 || strcmp(task->dir,"root") == 0){
			Dir = malloc(strlen(".")+1);
			Dir = ".";
		}
		else{
			Dir = malloc(strlen("./")+strlen(task->dir)+1);
			strcpy(Dir,"./");
			strcat(Dir,task->dir);
		}
	}
	else{
		Dir = malloc(strlen(task->dir)+1);
		strcpy(Dir,task->dir);

	}

	




	DIR *dr = opendir(Dir);
	if(dr == NULL){
		perror("dr not exist or can't access!");
		return NULL;
	}


	while((de = readdir(dr)) != NULL ){
		char filecontext[1024];
		filename = malloc(strlen(de->d_name)+1);
		//filepath = malloc(strlen(Dir)+strlen("/")+strlen(de->d_name)+1);
		filepath = malloc(strlen(task->dir)+strlen("/")+strlen(de->d_name)+1);
		filename = de->d_name;
		if(strcmp(de->d_name,".") != 0 && strcmp(de->d_name,"..") != 0){
			int ii = 0;
			if(strstr(de->d_name,".") == NULL && de->d_type != 8){
				//a folder
				Task *t = malloc(sizeof(struct Task));
				t->target = targetStr;
				t->dir = malloc(sizeof(char)*50);
				strcpy(t->dir,Dir);
				strcat(t->dir,"/");
				strcat(t->dir,de->d_name);
				t->fileN = malloc(sizeof(char)*30);
				memset(t->fileN, 0, sizeof(t->fileN));
				t->count = 0;
				t = strDir(t);
				count += t->count;
				strcat(task->fileN,t->fileN);

			}			
			else{
				//strcpy(filepath,Dir);
				strcpy(filepath,task->dir);
				strcat(filepath,"/");
				strcat(filepath,filename);
				memset(filenameTemp, 0, strlen(filenameTemp)+1);

				FILE *fp = fopen(filepath, "r");
				if(fp == NULL){
					perror("open file fail");
					return NULL;
				}
				while(fgets(filecontext, MAXLinelen, fp) != NULL){
					int index = 0;
					char *ret;
					while((ret = strstr(filecontext+index, targetStr)) != NULL){
						
						strcpy(filenameTemp, filepath);
						strcat(filenameTemp, " ");

						count ++;
						task->count ++;
						index = ret-filecontext + 1;
					}
				}
	
				strcat(resultStr, filenameTemp);				
				memset(filenameTemp, 0, strlen(filenameTemp)+1);
			}
		}
	}
	strcat(task->fileN, resultStr);
	task->count = count;
	return task;
}
