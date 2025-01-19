#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3

void *thread(void *vargp);
char **ptr;

int main() {
    int i;
    pthread_t tid;
    char *msgs[N] = {
        "Hola desde izquierda",
        "Hola desde centro",
        "Hola desde derecha",
    };

    printf("Hola desde aquí\n");
    ptr = msgs;

    for (i = 0; i < N; i++) {
        int *arg = malloc(sizeof(int)); // Reservar memoria para el entero
        *arg = i; // Asignar el valor
        pthread_create(&tid, NULL, thread, arg); // Pasar el puntero
    }

    pthread_join(tid, NULL);
    printf("Hola desde allá\n");
    pthread_exit(NULL);
    printf("Final\n");
    return 0;
}

void *thread(void *vargp) {
    int myid = *((int *)vargp); // Desreferenciar el puntero para obtener el entero
    static int cnt = 0;
    printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
    free(vargp); // Liberar la memoria reservada para el entero
    return NULL;
}

