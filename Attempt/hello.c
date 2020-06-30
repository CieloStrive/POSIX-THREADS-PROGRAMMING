#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM 4

pthread_attr_t attr;

void *hello(void *tid ){
    long id = (long)tid;
    printf("hello from thred #%ld \n",id);
    pthread_exit(NULL);
}

int main(){
    long ID[NUM];
    pthread_t pthread[NUM];
    size_t stack_size;

    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &stack_size);
    printf("default stack size is %li \n", stack_size);
    stack_size = 10000;
    printf("memory set for each thread is %li \n", stack_size);
    pthread_attr_setstacksize(&attr, stack_size);
    printf("creating threads with stack size of %li bytes \n", stack_size);

    for (int i = 0; i < NUM; i++){
        ID[i] = i;
        int rc = pthread_create(&pthread[i], NULL, hello, (void *)ID[i]);
        if(rc){
            printf("return from creating thread #%ld, code is %d \n", ID[i], rc);
            exit(-1); // exit from program and report error code -1
        }
    }
    printf("Main: program completed. Exiting.\n");
    system("pause");
    pthread_exit(NULL);
    return 0;
}