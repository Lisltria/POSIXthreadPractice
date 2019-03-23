#include <iostream>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

struct argument {
	int id;
	int time;
};

void *argpass1(void *threadarg){
	struct argument *p = (struct argument *) threadarg;
	sleep(1);
//	cout << "#" << p->id << " is " << p->time << endl;
	printf("#%d is %d\n",p->id,p->time);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t threads[10];
	int rc;
	struct argument data[10];
	for(int i = 0 ; i < 10; i++) {
		data[i].id = i+1;
		data[i].time = i *10;
		rc = pthread_create(&threads[i],NULL,argpass1,(void*)&data[i]);
		if(rc) {
			cout << "rc = " << strerror(errno) <<endl;
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
