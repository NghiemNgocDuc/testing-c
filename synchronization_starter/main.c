#include <stdio.h>
#include <pthread.h>
#include "challenge.h"

int main()
{
    int NUM_THREADS = 4;
    int N = 10;   // each count_up thread increments N times
    int T = 1000; // sleep time in microseconds
    int VAL = 20; // starting val for count_down

    pthread_t up_threads[NUM_THREADS];
    pthread_t down_threads[NUM_THREADS];

    struct args a;
    a.N = N;
    a.T = T;

    init(1);
    reset_accs();
    set_val(VAL);

    // spawn threads
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&up_threads[i], NULL, count_up, &a);
        pthread_create(&down_threads[i], NULL, count_down, &a);
    }

    // join threads
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(up_threads[i], NULL);
        pthread_join(down_threads[i], NULL);
    }

    printf("acc_up:   %d (expected %d)\n", get_acc_up(), NUM_THREADS * N);
    printf("acc_down: %d (expected %d)\n", get_acc_down(), VAL);
    printf("val:      %d (expected 0)\n", get_val());

    clean();
    return 0;
}
