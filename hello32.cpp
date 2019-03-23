#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
using namespace std;

void *hello32(void *threadid) {
	
	sleep(1);
	printf("Hello World #%ld\n",(long)threadid);
	pthread_exit(NULL);
}

int main(int argc,char *argv[]) {
	pthread_t threads[32];
	long t;
	int rc;
	for(t = 0; t < 32; t++) {
		rc = pthread_create(&threads[t],NULL,hello32,(void *)t);
		if(rc) {
			printf("Error:return code from pthread_create() is %d\n",rc);
			printf("%d = %s\n",rc,strerror(rc));
		}
	}
	printf("Create complete.\n");
	pthread_exit(NULL);
}
