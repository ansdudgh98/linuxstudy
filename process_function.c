#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t pid = getpid();
	pid_t ppid = getppid();
	printf("MY pid = %d\n",pid);
	printf("My ppid = %d\n",ppid);
}
