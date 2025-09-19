#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Для usleep

void* printY(void* unused){
    int a = 3;
    while(1){
        if(a % 2 == 0){
            printf("even ");
        } else {
            printf("odd ");
        }
        fflush(stdout); // Очищаем буфер вывода
        usleep(300000); // 300 мс задержка
    }
    return NULL;
}

void* printX(void* unused){
    int a = 4;
    int b = 0;
    while(1){
        if(b != 0){
            printf("%d ok ", a/b);
        } else {
            printf("0 divide ");
        }
        fflush(stdout);
        usleep(500000); // 500 мс задержка
    }
    return NULL;
}

void* printZ(void* unused){
    int a = 4;
    int b = 0;
    while(1){
        printf("%d sum ", a + b);
        fflush(stdout);
        usleep(200000); // 200 мс задержка
    }
    return NULL;
}

int main(){
    pthread_t threadId;
    pthread_create(&threadId, NULL, &printY, NULL);
    
    pthread_t threadId1;
    pthread_create(&threadId1, NULL, &printX, NULL);
    
    pthread_t threadId2;
    pthread_create(&threadId2, NULL, &printZ, NULL);
    
    while(1){
        printf("main ");
        fflush(stdout);
        usleep(400000); // 400 мс задержка для главного потока
    }
    
    return 0;
}