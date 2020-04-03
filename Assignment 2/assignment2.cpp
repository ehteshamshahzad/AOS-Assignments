/*
* Name: Ehtesham Shahzad
* Roll: Number: 19L-1891
* Assignment # 2
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

// To implement synchronization
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t semaP;

int input = 0;
int threadNum = 0;

// Function which the threads will call
void *threadFunction(void *args)
{
    // To get Thread ID
    pthread_t self_id1 = pthread_self();

    // To extract parameter
    int *num_ptr = (int *)args;
    int num = *num_ptr;

    // Locking thread
    // pthread_mutex_lock(&mutex);
    sem_wait(&semaP);

    threadNum++;
    cout << ">>>starting Thread " << threadNum << " the Thread ID is: " << self_id1 << "\n";

    // Printing first half
    if (threadNum == 1)
    {
        for (int i = 1; i <= num / 2; i++)
        {
            cout << "Thread " << threadNum << ": " << i << " , the Thread ID is: " << self_id1 << "\n";
        }
    }

    // Printing second half
    else
    {
        for (int i = num / 2 + 1; i <= num; i++)
        {
            cout << "Thread " << threadNum << ": " << i << " , the Thread ID is: " << self_id1 << "\n";
        }
    }

    cout << ">>>ending Thread " << threadNum << ", the Thread ID is: " << self_id1 << "\n";

    // Unlocking thread
    // pthread_mutex_unlock(&mutex);
    sem_post(&semaP);

    // Exiting thread
    pthread_exit(NULL);
}

//___________________________________________________

int main()
{
    // Initializing semaphore
    sem_init(&semaP, 0, 1);

    while (input < 10 || input > 100)
    {
        cout << "Enter a number between 10-100: ";
        cin >> input;
    }

    // Creating first thread
    pthread_t tid1;
    pthread_create(&tid1, NULL, &threadFunction, &input);

    // Creating second thread
    pthread_t tid2;
    pthread_create(&tid2, NULL, &threadFunction, &input);

    // Waiting for 1st thread to finish execution
    pthread_join(tid1, NULL);
    // Waiting for 2nd thread to finish execution
    pthread_join(tid2, NULL);

    // Destroying semaphore
    sem_destroy(&semaP);

    return 0;
}