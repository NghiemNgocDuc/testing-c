#include "challenge.h"

sem_t lock;

int acc_up;
int acc_down;
int val;

void init(int n){sem_init(&lock,0,n);}

void clean(){sem_destroy(&lock);}

void reset_accs()
{
  acc_up = 0;
  acc_down = 0;
}

void set_val(int nval){val = nval;}
int get_acc_up(){return acc_up;}
int get_acc_down(){return acc_down;}
int get_val(){return val;}

// goal: Multiple threads call this function where each thread repeats incrementing acc_up
//   and then sleeping an arbitrary number of times.
//   you don't want a sleeping thread to prevent other threads from working though
// param argp.N: how many times each thread increases acc_up
// param argp.T: how long (in microseconds) a thread sleeps after incrementing acc_up
// return: meh, not important
// assumptions:
//   locks have been set up (init(1) called at some prior point)
//   acc_up = 0 (reset_accs() called prior)
//
// TODO: add locks to synchronise function in an efficient manner
void* count_up(void* argp)
{
     int N = (*(struct args*)argp).N;
     int T = (*(struct args*)argp).T;
     for(int i = 0; i < N; i++) {
         sem_wait(&lock);
         acc_up++;
         sem_post(&lock);
         if(T){usleep(T);}
     }
     return NULL;
}

// goal: Multiple threads call this function where each thread repeats decrement val, incrementing acc_down 
//   and then sleeping until val hits 0.
//   you don't want a sleeping thread to prevent other threads from working though
// param argp.T: how long (in microseconds) a thread sleeps after incrementing acc_down
// return: meh, not important
// assumptions:
//   locks have been set up (init(1) called at some prior point)
//   acc_down = 0 (reset_accs() called prior)
//   val set (set_val(_) called prior)
//
// TODO: add locks to synchronise function in an efficient manner
void* count_down(void* argp)
{
     int T = (*(struct args*)argp).T;
     sem_wait(&lock);
     while(val > 0) {
         val--;
         acc_down++;
         sem_post(&lock);
         if(T){usleep(T);}
         sem_wait(&lock);
     }
     sem_post(&lock);
     return NULL;
}
