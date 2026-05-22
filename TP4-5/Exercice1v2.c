#define POSIX_C_SOURCE_ 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>

struct s_arg
{
    int rang;
    int nl;
    int nm;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

void *thread(void *p){
    pthread_t id = pthread_self();
    srand(id);
    struct s_arg* arg = p;
    for (int i = 0; i < arg->nm; i++)
    {
        int t = rand()%1000;
        usleep(t);
        sem_wait(&sem);
        for(int j = 0; j<arg->nl;j++) {
            printf("Afficheur %d (%lu), j'affiche ligne %d/%d du message %d/%d\n", arg->rang, id, j,arg->nl, i, arg->nm);
        }
        sem_post(&sem);
    }
    printf("Afficheur %d (%lu), je me termine\n", arg->rang, id);
    int *res = malloc(sizeof(int));
    *res = arg->rang;
    pthread_exit((void*)res);
}

int main(int argc, char const *argv[])
{
    int NBT = atoi(argv[1]);
    int NBM = atoi(argv[2]);
    int NBL = atoi(argv[3]);

    pthread_t ptid[NBT];
    sem_init(&sem, 0, 1);

    int *res = NULL;
    if(argc!=4) {
        printf("paramètre");
        exit(1);
    }

    //pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i<NBT; i++){
        struct s_arg* arg = malloc(sizeof(struct s_arg));
        arg->nl = NBL;
        arg->nm = NBM;
        arg->rang = i;
        if(pthread_create(&ptid[i], NULL, thread, arg)!=0){
            perror("création thread");
            exit(1);
        }
    }

    for (int i = 0; i<NBT; i++){
        if(pthread_join(ptid[i], (void**)&res)!=0){
            perror("création thread");
            exit(1);
        }
    }
    printf("Fin de l'execution de thread principal\n");
    return 0;
}
