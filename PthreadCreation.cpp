#include <iostream>
#include <pthread.h>

void *prtHelloWorld(void *threadid) {
	long tid;
	tid = (long)threadid;
	std::cout << "Hello world, thread #" << tid << std::endl;
	pthread_exit(NULL);
}

int main(int argc, char *argv[] ) {
	pthread_t threads[6];
	int rc;
	long t;
	for( t = 0; t < 6; t++) {
		std::cout << "In main: " << t <<"th thread created." << std::endl;
		rc = pthread_create(&threads[t], NULL, prtHelloWorld, (void *)t);
		if(rc) {
			std::cout << "ERROR" << std::endl;
			exit(-1);
		}
	}
	
	pthread_exit(NULL);
	return 0;
}

