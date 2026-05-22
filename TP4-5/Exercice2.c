#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

int NT;
int SOLDE_INIT;
int NO;

int SOLDE;

sem_t sem;

void *f_thread(void *p) {
    int *cr = malloc(sizeof(int));
    srand(pthread_self());
    int operation = *(int*)p%2;
    for(int i = 0; i<NO; i++) {
        int montant = rand() % 10;
        
        sem_wait(&sem);
        if(operation == 0) {
            // DEBIT
            SOLDE = SOLDE-montant;
            if(SOLDE<0) {
                printf("debit insuffisant\n");
            }
            printf("debit %d solde %d\n", montant, SOLDE);

        } else {
            // CREDIT
            SOLDE = SOLDE+montant;
            printf("credit %d solde %d\n", montant, SOLDE);
        }
        sem_post(&sem);

        

        usleep(*cr);
        //printf("\tThread %d: Mon identificateur est %lu (délai : %d)\n",*(int *)p, pthread_self(), *cr); 
    }
    pthread_exit((void*)p);
}

int main(int argc, char const *argv[])
{
    if (argc != 4) {printf("USAGE : %s NT SOLDE_INIT NO\n", argv[0]); return 1;}

    NT = atoi(argv[1]);
    SOLDE_INIT = atoi(argv[2]);
    NO = atoi(argv[3]);

    sem_init(&sem, 0, 1);

    pthread_t ptid[10];

    int rang[10];
    for(int i = 0; i<NT; i++) {
        rang[i] = i;
        if (pthread_create(&ptid[i], NULL, f_thread, (void *)&rang[i]) != 0) {
            perror("Probleme lors de la creation du thread compagnon:");
            exit(67);
        }
    }

    for(int i = 0; i<NT; i++) {
        int *res = NULL;

        pthread_join(ptid[i], (void**)&res);
        //printf("Valeur retourné par le thread %ld = %d \n", ptid[i], *res);
    }



    printf("Solde = %d\n", SOLDE);

    return 0;
}
