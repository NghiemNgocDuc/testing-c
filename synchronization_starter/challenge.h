#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef CH_HEAD
#define CH_HEAD

struct args
{
  int N;
  int T;
};

void init(int n);
void clean();

void reset_accs();
void set_val(int nval);

int get_acc_up();
int get_acc_down();
int get_val();

// goal: a bunch of threads increment acc_up, then sleep, multiple times each
//   you don't want a sleeping thread to prevent other threads from working though
// param argp.N: how many times each thread increases acc_up
// param argp.T: how long (in microseconds) a thread sleeps after incrementing acc_up
// return: meh, not important
// assumptions:
//   locks have been set up (init(1) called at some prior point)
//   acc_up = 0 (reset_accs() called prior)
void* count_up(void* argp);

// goal: a bunch of threads increment acc_down, then sleep, val times total
//   you don't want a sleeping thread to prevent other threads from working though
// param argp.T: how long (in microseconds) a thread sleeps after incrementing acc_down
// return: meh, not important
// assumptions:
//   locks have been set up (init(1) called at some prior point)
//   acc_down = 0 (reset_accs() called prior)
//   val set (set_val(_) called prior)
void* count_down(void* argp);

#endif