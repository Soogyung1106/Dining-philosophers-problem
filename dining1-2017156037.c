#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *func(int n);
pthread_t philosopher[5];
pthread_mutex_t chopstick[5]={1};

int main()
{
     int i;
     void *msg;
     for(i=0;i<5;i++)
     {
          pthread_mutex_init(&chopstick[i],NULL);
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
          pthread_mutex_destroy(&chopstick[i]);
      }
     return 0;
}

void *func(int n)
{
     printf ("\nPhilosopher %d is thinking ",n);
     printf("\nPhilosopher %d is in the dining room ", n);
     pthread_mutex_lock(&chopstick[n]);
        sleep(3);
     pthread_mutex_lock(&chopstick[(n+1)%5]);
        printf ("\nPhilosopher %d is eating ",n);
        sleep(2);

     pthread_mutex_unlock(&chopstick[(n+1)%5]);
     pthread_mutex_unlock(&chopstick[n]);

     printf ("\nPhilosopher %d finished eating ",n);
}
