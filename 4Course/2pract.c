#include <stdio.h>
#include <pthread.h>


void* printY(void* unused){
    while(1){
        printf("y");
    }
    return NULL;
}

int main(){
    pthread_t threadId;
    pthread_create(&threadId, NULL, &printY, NULL);
    while(1){
        printf("e");
    }
    return 0;
}