//This code demonstrates the implementation of how the race condition, Dirty COW, is fixed

#include <stdio.h>
#include <pthread.h>

//Shared variable
int counter = 0;

//Mutex to protect 'counter'
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        //Lock before modifying the shared variable
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    //Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    //Create two threads that both run increment()
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    //Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //Print the final counter value
    printf("Final counter value (fixed): %d\n", counter);

    //Destroy the mutex when done
    pthread_mutex_destroy(&lock);

    return 0;
}
