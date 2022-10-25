#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

char * getcwd(char *buf,size_t size);
int chdir(const char *path);
int mkdir(const char *pathname,mode_t mode);
int remove(const char *path);
void function_pwd(){
	char cwd[100];
	if(getcwd(cwd,sizeof(cwd)) != NULL){
		printf("%s\n",cwd);
	}
	else{
		perror("getcwd() error");
	}
}

void function_cat(char *command){
	int fd;
	char buf;
	int len=1;
	if(strcmp(command,"")==0){
		fprintf(stderr,"Write File Name PLZ");		
	}
	else{
		fd = open(command,O_RDONLY);
		if(fd==-1)
			printf("cat:%s:No such File or Directory \n",command);
			
		else{
			while(len!=0){
				len=read(fd,&buf,1);
				if(len==-1){
					fprintf(stderr,"File error\n");
					break;
				}	
				printf("%c",buf);
			}	
		}
	
	}
	
}

void function_ls(){
	char *cwd = (char *)malloc(sizeof(char)*1024);
	DIR* dir =NULL;
	struct dirent *entry=NULL;

	getcwd(cwd,1024);

	if((dir=opendir(cwd))==NULL){
		printf("current directory error \n");
	}

	while((entry=readdir(dir))!=NULL){
		printf("%s\t",entry->d_name);
	}
	free(cwd);

}


void function_cd(char *path){
 	int result ;
	result=chdir(path);
	if(result==0){
		function_pwd();
	}
	else{
		if(fopen(path,"r")){
			printf("No Such Directory\n");
		}
		else{
			printf("No Such File or Directory\n");
		}
	}	
}

void function_mkdir(char *dir_name){
	int result;
	result = mkdir(dir_name,0755);
	
	if(result == 0){
		printf("성공a");
	}
	else{
		printf("mkdir: cannot create directory '%s' : File exists\n",dir_name);
	}

}

void write_history(char *command){
	char *filename = "history_log.txt";
	FILE *file = fopen(filename,"a");
	int len;
	char *ch_line = "\n";
	
	if(file == NULL){
		int fd = creat(filename,S_IRWXU);
		file = fopen(filename,"w");	
	}
	fputs(command,file);
	fputs("\n",file);
	fclose(file);

}

void read_history(){
	char *filename = "history_log.txt";
	FILE *file = fopen(filename,"r");
	char str[255];
	int i = 0 ;
	while((fgets(str,100,file))!=NULL){
		printf("%d ",i+1);
		printf("%s",str);
		i++;
	}
		fclose(file);
}

void read_history_num(int num){
	char *filename = "history_log.txt";
	FILE *file = fopen(filename,"r");
	char str[255];
	int i,j= 1;

	while(feof(file)!=1){
		fgets(str,100,file);
		i++;	
	}
	int fseeknum = fseek(file,0,SEEK_SET);
	if(fseeknum==-1)
		fprintf(stderr,"파일 위치 오류");
	for(j=0;j<(i-num);j++){
		fgets(str,100,file);
	}
	
	while((feof(file)!=1)){
		j++;
		printf("%d ",j);
		printf("%s",str);
		fgets(str,100,file);
	}

}

char* exc_history_num(int num){
	char *filename = "history_log.txt";
	FILE *file = fopen(filename,"r");
	char *command = malloc(sizeof(char)*100);
	int i,j=0;
	char str[255];
	while((fgets(str,100,file)!=NULL)){
		i++;
	}
	if(i<num){
		printf("plz input !num small than history num");
	}
	int fseeknum = fseek(file,0,SEEK_SET);
        if(fseeknum==-1)
                fprintf(stderr,"파일 위치 오류");
	while(1){
		fgets(str,100,file);
		if(j==(num-1)){
			strcpy(command,str);
			break;
		}
		if(j==i){
			break;
		}		
		j++;	
	}

	strtok(command,"\n");
	return command;
}	

void copy_file(char *filename,char *cpfilename){
	FILE *file = fopen(filename,"r");
	FILE *cpfile = fopen(cpfilename,"w");
	int charnum;
	if(file == NULL){
		printf("Not found %s\n",filename);
		return;
	}

	char value;
	while(charnum!=EOF){
		charnum = fgetc(file);
		value = charnum + '0';
		fputc(charnum,cpfile);
	}
	fclose(file);
	fclose(cpfile);

}

void removefile(char *filename){
	int result = remove(filename);

	if(result == -1 )
		printf("dir is not empty");	
}


