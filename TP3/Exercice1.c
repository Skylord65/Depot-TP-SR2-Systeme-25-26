#define POSIX_C_SOURCE_ 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

struct s_arg
{
    int rang;
    int nf;
};

void *thread(void *p){
    pthread_t id = pthread_self();
    srand(id);
    struct s_arg* arg = p;
    for (int i = 0; i < arg->nf; i++)
    {
        int t = rand()%100;
        usleep(t);
        printf("Activite rang %d : identifiant = %ld (delai = %d)\n", arg->rang, id,t);
    }
    int *res;
    *res = arg->rang;
    pthread_exit((void*)res);
}

int main(int argc, char const *argv[])
{

    if(argc!=3) {
        printf("pas le bon nombre de parametre\n");
        exit(1);
    }

    int NA = atoi(argv[1]);
    int NF = atoi(argv[2]);

    pthread_t ptid[NA];
    void *res = NULL;
    if(argc!=3) {
        printf("paramètre");
        exit(1);
    }
    for (int i = 0; i<NA; i++){
        struct s_arg* arg;
        arg->nf = NF;
        arg->rang = i;
        if(pthread_create(&ptid[i], NULL, thread, arg)!=0){
            perror("création thread");
            exit(1);
        }
    }

    for (int i = 0; i<NA; i++){
        if(pthread_join(ptid[i], &res)!=0){
            perror("création thread");
            exit(1);
        }
        printf("Valeur retournee par le fils %d = %d\n", (int)ptid[i], (int*)res);
    }
    return 0;
}
