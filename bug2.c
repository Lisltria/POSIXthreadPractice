#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NTHREADS	8
#define ARRAY_SIZE      500000
pthread_attr_t attr;
void *Hello(void *threadid)
{
   double A[ARRAY_SIZE];
   int i; 
   long tid;
   size_t thisstacksize;

   tid = (long)threadid;
   sleep(3);
   for (i=0; i<ARRAY_SIZE; i++)
   {
      A[i] = i * 1.0;
   }
   printf("%ld: Hello World!   %f\n", tid, A[ARRAY_SIZE-1]);
   pthread_attr_getstacksize(&attr,&thisstacksize);
   printf("%ld: Thread stack size = %li bytes \n", tid, thisstacksize);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NTHREADS];
	size_t stacksize;
	int rc; 
	long t;
	pthread_attr_init(&attr);
	stacksize = ARRAY_SIZE * sizeof (double) + 10000;
	pthread_attr_setstacksize (&attr, stacksize);
	pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
	pthread_attr_getstacksize (&attr, &stacksize);
	printf("Thread stack size = %li bytes (hint, hint)\n",stacksize);
	for(t=0;t<NTHREADS;t++){
  		rc = pthread_create(&threads[t], &attr, Hello, (void *)t);
  		if (rc){
    		printf("ERROR; return code from pthread_create() is %d\n", rc);
    	exit(-1);
    	}
  	}
	printf("Created %ld threads.\n", t);
	pthread_exit(NULL);
}