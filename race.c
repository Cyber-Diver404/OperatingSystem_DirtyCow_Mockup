//This code implements and demonstrates the Dirty COW race condition

#include <stdio.h>
#include <pthread.h>

//Shared variable that both threads will modify
int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        counter++;   //NOT thread-safe aka race condition
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    //Create two threads that both run increment()
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    //Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //Expected value: 2,000,000
    //Actual value: will be lower because both threads step on each other
    printf("Final counter value: %d\n", counter);

    return 0;
}
