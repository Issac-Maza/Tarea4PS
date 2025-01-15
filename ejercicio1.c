#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <pthread.h>
int x = 7;
int i = 2;

void *h1(void *args){
    i = 1;
    x = x + i;
    i++;
    printf("1:%d\n",x);
}

void *h2(void *args){
    i++;
    x = x-i;
    printf("2:%d\n",x);
}

int main(void){
    pthread_t myThread1, myThread2;
    int aux = 0;
    pthread_create(&myThread2, NULL, &h1, (void *)&aux);
    pthread_create(&myThread1, NULL, &h1, (void *)&aux);
    pthread_join(myThread1, NULL);  
    pthread_join(myThread2, NULL);  
    printf("O: %d\n",x);
    return(0);
}
