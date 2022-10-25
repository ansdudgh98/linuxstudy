#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* exc_history_num(int num);
void function_pwd();
void function_cat(char *command);
void function_ls();
void function_cd(char *path);
char* gets(char* str);
void function_mkdir(char *dir_name);
void write_history(char *command);
void read_history();
void read_history_num(int num);
void copy_file(char *filename,char *cpfilename);
void removefile(char *filename);
void command_ln(char *oldpath,char *newpath);
void print_stat(char *pathname);
void chmod_print(char *permission,char *filename);
void print_ps();

typedef struct alias{
	char shortword[255];
	char longword[255];
}alias;


alias a[100];

void main_print(){
	char userinput[100];
	char *strArr[10] = {NULL,};
	int i = 0;
	int aliasindex = 0;
	printf("Command:");
	gets(userinput);
	while(userinput[0]=='\0'){
		printf("Command:");
		gets(userinput);
	}

	char saveuserinput[255];
	strcpy(saveuserinput,userinput);
	for(int k=0;k<100;k++){
		if(strcmp(a[k].shortword,userinput)==0){
			strcpy(userinput,a[k].longword);
			break;
		}
	}
	if(*(userinput+0) == '!'){
		char *cc = malloc(sizeof(char)*255);
		char *str = strtok_r(userinput,"!",&cc);
		int ch_num = atoi(str);
		if(ch_num==0){
			printf("plz input 0 or not str\n");
			main_print();
		}
		char *cp_result= malloc(sizeof(char)*255);
		strcpy(cp_result,exc_history_num(ch_num));
		strcpy(userinput,cp_result);
		strcpy(saveuserinput,cp_result);
	}
	if(strcmp(userinput,"cat")==0){
		printf("error\n");
		main_print();
	}
	char *ptr = strtok(userinput," ");
	while(ptr!=NULL){
		strArr[i] = ptr;
		i++;
		ptr= strtok(NULL," ");
	}
	strcpy(userinput,strArr[0]);
	
	if(strcmp(userinput,"exit")==0){
		write_history(saveuserinput);
		printf("exit\n");
	}
	else if(strcmp(strArr[0],"cat")==0){
		for(int j=1;j<=i-1;j++){
			if(strArr[j]==NULL){
				printf("No such File or directory");
			}
			function_cat(strArr[j]);
		}
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(userinput,"cd")==0){
		if(strArr[1] == NULL){
			function_cd("/home/linux");
			main_print();
		}
		write_history(saveuserinput);
		function_cd(strArr[1]);
		main_print();
		
	}	
	else if(strcmp(userinput,"pwd")==0){
		function_pwd();
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(userinput,"mkdir")==0){
		if(strArr[1] ==NULL){
			printf("Error:PLZ Input directory Name");
			main_print();
		}
		else{
			function_mkdir(strArr[1]);
		}
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(userinput,"ls")==0){
		function_ls();
		printf("\n");
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(userinput,"history")==0){
		if(strArr[1] ==NULL){
			write_history(saveuserinput);
			read_history();
			main_print();
		}
		else{
			int strtoint = atoi(strArr[1]);
			read_history_num(strtoint);
		}
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(userinput,"ps")==0){
		print_ps();
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(strArr[0],"cp")==0){
		if(strArr[2] == NULL){
			printf("new file name is NULL");
			main_print();
		}
		copy_file(strArr[1],strArr[2]);
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(strArr[0],"rm")==0){
		for(int j=1;j<=i-1;j++){
			if(strArr[j]==NULL){
				printf("No such File or directory");
			}
			removefile(strArr[j]);
		}
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(strArr[0],"ln")==0){
		if(strArr[1] ==NULL){
			printf("file name is NULL");
			main_print();
		}
		if(strArr[2]==NULL){
			printf("link name is NULL");
			main_print();
		}
		command_ln(strArr[1],strArr[2]);
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(strArr[0],"stat")==0){
		print_stat(strArr[1]);
		main_print();
	}
	else if(strcmp(strArr[0],"chmod")==0){
		if(strArr[1] ==NULL){
			printf("permission is NULL");
			main_print();
		}
		if(strArr[2]==NULL){
			printf("filename is NULL");
		}
		chmod_print(strArr[1],strArr[2]);
		write_history(saveuserinput);
		main_print();
	}
	else if(strcmp(userinput,"alias")==0){
		int indexcount=0;
		if(strArr[1]==NULL){
			while(indexcount<100){
				if(a[indexcount].shortword[0]=='\0'){
					break;
				}
				else{
				printf("alias %s=%s\n",a[indexcount].shortword,a[indexcount].longword);
				indexcount++;
				}
			}
			main_print();
		}
		char *firstword = strtok(strArr[1],"=");
		char *secondword = strtok(NULL," ");
		int count=0;
		while(count<100){
			if((strcmp(a[count].shortword,firstword)==0)){
				strcpy(a[count].longword,secondword);
				break;
			}
			else if(a[count].shortword[0]=='\0'){
				strcpy(a[count].longword,secondword);
				strcpy(a[count].shortword,firstword);
				break;
			}
			count++;
		}
		write_history(saveuserinput);
		main_print();
		
	}
	else {
		printf("%s: command not found\n",userinput);
		main_print();
	}
}

int main(){
	main_print();
	return 0;

}





