#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    if(argc!=3) {
        perror("pas le bon nombre d'argument");
        exit(1);
    }
    int nf = atoi(argv[1]);
    int nm = atoi(argv[2]);

    pid_t pids[nf];

    for(int i = 0; i < nf; i++) {
        pids[i] = fork();
        switch (pids[i]) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            int id = (int)getpid();
            for (int j = 0; j < nm; j++) {
                printf("Activite rang %d : identifiant = %d\n", i, id);
            }
            return i;
            break;
        default:
            break;
        }
    }

    int *status = malloc(sizeof(int));
    for(int k = 0; k < nf; k++) {
        wait(status);
        printf("Valeur retournee par le fils %d = %ld\n", pids[k], WEXITSTATUS(*status));
    }
    free(status);
    return 0;
}
