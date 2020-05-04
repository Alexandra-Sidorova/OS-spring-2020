#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

int Data;
int ReadCount;

void* Writer(void* arg)
{
    int i;
    int id = *(void*)arg;
    
    for(i = 0; i < 5; i++)
    {
        sleep(rand() % 11 + 10);
        if (sem_wait($semaphore) != 0)
        {
            printf("Error writer sem_wait!\n");
            break;
        } 
        printf("Writer #%d starts writing. ReadCount = %d, Data = %d\n", id, ReadCount, Data);
        sleep(3);
        Data++;
        printf("Writer #%d ends writing. ReadCount = %d, Data = %d\n", id, ReadCount, Data);
        if (sem_post($semaphore) != 0)
        {
            printf("Error writer sem_post!\n");
            break;
        }
    }
}

void* Reader(void* arg)
{
    int i;
    int id = *(void*)arg;
    
    for(i = 0; i < 5; i++)
    {
        sleep(rand() % 11 + 10);
        if (sem_wait($semaphore) != 0)
        {
            printf("Error reader sem_wait!\n");
            break;
        } 
        ReadCount++;
        printf("Reader #%d starts reading. ReadCount = %d, Data = %d\n", id, ReadCount, Data);
        sleep(3);
        printf("Reader #%d ends reading. ReadCount = %d, Data = %d\n", id, ReadCount, Data);
        ReadCount--;
        if (sem_post($semaphore) != 0)
        {
            printf("Error reader sem_post!\n");
            break;
        }
    }
}

int main()
{
    pthread_t threads[10];
    int i;
    
    if(sem_init(&semaphore, 0, 1) != 0)
    {
        printf("Error sem_init!\n");
        return -1;
    }
    
    for(i = 0; i < 5; i++)
    {
        if (pthread_create(&threads[i], NULL, Writer, (void*)&i) != 0)
        {
            printf("Error pthread_create %d\n", i);
            return -1;
        }
        if (pthread_create(&threads[5 + i], NULL, Reader, (void*)&i) != 0)
        {
            printf("Error pthread_create %d\n", 5 + i);
            return -1;
        }
    }
    
    for(i = 0; i < 5; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("Error pthread_join %d\n", i);
            return -1;
        }
        if (pthread_join(threads[5 + i], NULL) != 0)
        {
            printf("Error pthread_create %d\n", 5 + i);
            return -1;
        }
    }
    
    if(sem_destroy(&semaphore) != 0)
    {
        printf("Error sem_destroy!\n");
        return -1;
    }
    
    printf("End Data = %d\n", Data);
    
    return 0;
}