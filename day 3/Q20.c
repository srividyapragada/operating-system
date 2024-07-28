#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, rw_mutex;
int num_readers = 0;
int data = 0;

void *reader(void *arg) {
    int reader_id = (int)arg;
    while (1) {
        sem_wait(&mutex);
        num_readers++;
        if (num_readers == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Reading data
        printf("Reader %d is reading data: %d\n", reader_id, data);

        sem_wait(&mutex);
        num_readers--;
        if (num_readers == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        // Reader waiting before reading again
        sleep(1);
    }
}

void *writer(void *arg) {
    int writer_id = (int)arg;
    while (1) {
        sem_wait(&rw_mutex);

        // Writing data
        data++;
        printf("Writer %d is writing data: %d\n", writer_id, data);

        sem_post(&rw_mutex);

        // Writer waiting before writing again
        sleep(2);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
