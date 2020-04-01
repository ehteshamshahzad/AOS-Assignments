/*
* Name: Ehtesham Shahzad
* Roll: Number: 19L-1891
* Assignment # 2
*/

#include <iostream>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *args)
{
    pthread_t self_id1 = pthread_self();
    int *num_ptr = (int *)args;
    int num = *num_ptr;
    
    pthread_mutex_lock(&mutex);
    cout << ">>>starting Thread 1 the Thread ID is: " << self_id1 << "\n";

    for (int i = 1; i <= num / 2; i++)
    {
        cout << "Thread 1: " << i << " , the Thread ID is: " << self_id1 << "\n";
    }

    cout << ">>>ending Thread 1, the Thread ID is: " << self_id1 << "\n";
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

//___________________________________________________

void *thread2(void *args)
{
    pthread_t self_id2 = pthread_self();
    int *num_ptr = (int *)args;
    int num = *num_ptr;

    pthread_mutex_lock(&mutex);
    cout << ">>>starting Thread 2 the Thread ID is: " << self_id2 << "\n";

    for (int i = num / 2 + 1; i <= num; i++)
    {
        cout << "Thread 2: " << i << " , the Thread ID is: " << self_id2 << "\n";
    }

    cout << ">>>ending Thread 2, the Thread ID is: " << self_id2 << "\n";
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

//___________________________________________________

int main()
{
    int input = 0;

    while (input < 10 || input > 100)
    {
        cout << "Enter a number between 10-100: ";
        cin >> input;
    }

    pthread_t tid1;
    pthread_create(&tid1, NULL, &thread1, &input);

    pthread_t tid2;
    pthread_create(&tid2, NULL, &thread2, &input);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}