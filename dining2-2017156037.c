#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *func(int n);
pthread_t philosopher[5];
sem_t chopstick[5];
sem_t room; //room: 카운팅 세마포어 변수

int main()
{
     int i;
     void *msg;

     for(i=0;i<4;i++)
     {
          sem_init(&room,0,4); //세마포어의 공유여부, 초기화 값
     }
     for(i=0;i<5;i++)
     {
          sem_init(&chopstick[i],0,1); //세마포어의 공유여부, 초기화 값
     }
     for(i=0;i<5;i++)
     {
          pthread_create(&philosopher[i],NULL,(void *)func,(int *)i);
     }
     for(i=0;i<5;i++)
     {
          pthread_join(philosopher[i],&msg);
     }
     printf("\n");
      for(i=0;i<5;i++)
      {
          sem_destroy(&chopstick[i]);
      }
      for(i=0;i<4;i++)
      {
          sem_destroy(&room);
      }
     return 0;
}

void *func(int n)
{
     printf ("\nPhilosopher %d is thinking ",n);
     sem_wait(&room);
     printf("\nPhilosopher %d is in the dining room ", n);
     sem_wait(&chopstick[n]);
        sleep(3);
     sem_wait(&chopstick[(n+1)%5]);
        printf ("\nPhilosopher %d is eating ",n);
        sleep(2);

     sem_post(&chopstick[(n+1)%5]);
     sem_post(&chopstick[n]);
     sem_post(&room);

     printf ("\nPhilosopher %d finished eating ",n);

}

