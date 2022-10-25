#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
struct passwd *getpwuid(uid_t uid);
int link(const char *oldpath,const char *newpath);
int lstat(const char *pathname, struct stat *statbuf);
int chown(const char *pathname,uid_t owner,gid_t group);
int chmod(const char *file,mode_t mode);
DIR * opendir(const char *name);
struct dirent *readdir(DIR *dir);
void function_cat(char *command);


void command_ln(char *oldpath,char *newpath){
	int result = link(oldpath,newpath);

        if(result == EOF){
                printf("error");
        }
}


void print_stat(char *pathname){
	
    struct stat finfo;
    printf("File type: ");
	if (stat(pathname, &finfo) == -1) {
    		printf("error");
	}
    switch(finfo.st_mode & S_IFMT) {
        case S_IFBLK: printf("block device\n"); break;
        case S_IFCHR: printf("character device\n"); break;
        case S_IFDIR: printf("directory\n"); break;
        case S_IFREG: printf("regular file\n"); break;
    }

    printf("I-node number:            %ld\n", (long) finfo.st_ino);
    printf("Mode:                     %lo (octal)\n", (unsigned long) finfo.st_mode);
    printf("Link count:               %ld\n", (long) finfo.st_nlink);
    printf("Ownership:                UID=%ld GID=%ld\n", (long)finfo.st_uid, (long)finfo.st_gid);
    printf("Preferred I/O block size: %ld bytes\n", (long) finfo.st_blksize);
    printf("File size:                %lld bytes\n", (long long) finfo.st_size);
    printf("Blocks allocated:         %lld\n", (long long) finfo.st_blocks);
    printf("Last status change:       %s", ctime(&finfo.st_ctime));
    printf("Last file access:         %s", ctime(&finfo.st_atime));
    printf("Last file modification:   %s", ctime(&finfo.st_mtime));	
}

void chmod_print(char *permission,char *filename){
	int num_permission;
	sscanf(permission,"%o",&num_permission);
	int result = chmod("testchmod",num_permission);
	if(result == -1)
		printf("error");
	
}





void print_ps(){
	printf("    PID      CMD\n");
	int uid = getuid();
	DIR *dir ;
	struct dirent *entry;
	struct stat fileinfo;
	dir = opendir("/proc");
	char path[100] = "/proc/";
	if(dir!=NULL){
		while((entry = readdir(dir))!=NULL){
			char path[100] = "/proc/";
			strcat(path,entry->d_name);
			strcat(path,"/cmdline");
			stat(path,&fileinfo);
			int a;
			a= atoi(entry->d_name);
			if((fileinfo.st_uid==uid)){
				printf("%s",entry->d_name);
				printf("           ");
				function_cat(path);
				printf("\n");
			}
			/*if(fileinfo.st_uid==uid){
				printf("%s",path);
				printf("%s"
			}*/
			
		}
	}
}




