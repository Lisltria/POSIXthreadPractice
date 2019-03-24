#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS	4

void *BusyWork(void *t)
{
   long i, tid;
   double result=0.0;
   tid = (long)t;
   printf("Thread %ld starting...\n",tid);
   for (i=0; i<1000000; i++) {
     result = result + sin(i) * tan(i);
     }
   printf("Thread %ld done. Result = %e\n",tid, result);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	int rc; 
	long t;

/* Initialize and set thread detached attribute */
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	for(t=0;t<NUM_THREADS;t++) {
   		printf("Main: creating thread %ld\n", t);
   		rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t); 
   		if (rc) {
     		printf("ERROR; return code from pthread_create() is %d\n", rc);
    		exit(-1);
     	}
  	}

/* We're done with the attribute object, so we can destroy it */
	pthread_attr_destroy(&attr);

/* The main thread is done, so we need to call pthread_exit explicitly to
*  permit the working threads to continue even after main completes.
*/
	printf("Main: program completed. Exiting.\n");
	pthread_exit(NULL);
}
