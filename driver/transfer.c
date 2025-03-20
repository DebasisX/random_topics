#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SOURCE_FILE "/media/debasis/DEBASIS/example.txt"  // USB file
#define DEST_FILE "/home/user/Documents/copy.txt"        // Laptop destination
#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];  // Shared buffer
size_t bytesRead = 0;      // Number of bytes read
int done = 0;              // Flag to indicate read completion

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

FILE *source, *dest;

void *reader_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        bytesRead = fread(buffer, 1, BUFFER_SIZE, source);
        if (bytesRead == 0) { // EOF reached
            done = 1;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *writer_thread() {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        while (bytesRead == 0 && !done) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (done && bytesRead == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        fwrite(buffer, 1, bytesRead, dest);
        bytesRead = 0;

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t reader, writer;

    source = fopen(SOURCE_FILE, "rb");
    if (source == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    dest = fopen(DEST_FILE, "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(source);
        return EXIT_FAILURE;
    }

    pthread_create(&reader, NULL, reader_thread, NULL);
    pthread_create(&writer, NULL, writer_thread, NULL);

    // wait 
    pthread_join(reader, NULL);
    pthread_join(writer, NULL);

    fclose(source);
    fclose(dest);

    printf("File copied successfully!\n");
    return EXIT_SUCCESS;
}
