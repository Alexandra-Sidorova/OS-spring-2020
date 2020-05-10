#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semapthore.h>

sem_t Access;
sem_t Empty;
sem_t Full;

const int BufferSize = 10;
int Start = 0;
int End = 0;
int* Buffer;

void* Producer(void* arg)
{
    int i;
    int id = *(int*)arg;
    
    for(i = 0; i < 5; i++)
    {
        sem_wait(&Empty);
        sleep(rand() % 11 + 10);
        sem_wait(&Access);
        Buffer[Start] = 10 * id + i + 1;
        printf("Producer #%d producered element #%d\n", id, i + 1);
        printf("Start=%d End=%d   %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d\n", Start, End, Buffer[0], Buffer[1],
            Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7], Buffer[8], Buffer[9]);
        Start = (Start + 1) % BufferSize;
        sem_post(&Access);
        sem_post(&Full);
    }
}

void* Consumer(void* arg)
{
    int i;
    int id = *(int*)arg;
    
    for(i = 0; i < 5; i++)
    {
        sem_wait(&Full);
        sleep(rand() % 11 + 10);
        sem_wait(&Access);
        Buffer[End] = 0;
        printf("Consumer #%d consumered element #%d\n", id, i + 1);
        printf("Start=%d End=%d   %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d\n", Start, End, Buffer[0], Buffer[1],
            Buffer[2], Buffer[3], Buffer[4], Buffer[5], Buffer[6], Buffer[7], Buffer[8], Buffer[9]);
        End = (End + 1) % BufferSize;
        sem_post(&Access);
        sem_post(&Empty);
    }
}

int main()
{
    pthread_t threads[10];
    int i, j;
    
    Buffer = (int*)malloc(BufferSize * sizeof(int));
    memset(Buffer, 0, BufferSize * sizeof(int));
    
    sem_init(&Access, 0, 1);
    sem_init(&Empty, 0, BufferSize);
    sem_init(&Full, 0, 0);
    
    for(i = 0; i < 5; i++)
    {
        j = i + 5;
        pthread_create(&threads[i], NULL, (void*)Producer, (void*)&i);
        pthread_create(&threads[j], NULL, (void*)Consumer, (void*)&j);
    }
    
    for(i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
        pthread_join(threads[5 + i], NULL);
    }
    
    sem_destroy(&Access);
    sem_destroy(&Full);
    sem_destroy(&Empty);
}