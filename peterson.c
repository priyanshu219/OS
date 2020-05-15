#include <stdio.h>
#include <pthread.h>

int flag[2];
int turn;
int ans;

void delay(int milli_seconds) 
{ 
    clock_t start_time = clock();  
    // printf("%ld", start_time);
    while (clock() < start_time + milli_seconds); 
} 

void lock_init(){
	flag[0] = flag[1] = 0;
	turn = 0;
	ans = 0;
}

void lock(int self){
	flag[self] = 1;
	turn = 1-self;
	while(flag[1-self] && turn == 1-self);
}

void unlock(int self){
	flag[self] = 0;
}

void *algorithm(void *thread){

	int self = (int *)thread;
	lock(self);
	printf("Thread Executing: %d\n", self);
	for(int i = 0; i < 20; i++)
		ans++;
	unlock(self);
}

int main(){

	pthread_t p1, p2;
	lock_init();
	int i = 10;

	do{
	    pthread_create(&p1, NULL, algorithm, (void *)0);   
	    pthread_create(&p2, NULL, algorithm, (void *)1);
	    delay(1000);
	 //    pthread_join(p1, NULL);
		// pthread_join(p2, NULL);
	}while(i--);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	printf("ans: %d\n", ans);
}