#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>

#define MONTANT_MAX 20

int main(int argc, char const *argv[]) {
    
    if(argc!=3) {
        printf("pas le bon nombre de parametre\n");
        exit(1);
    }

    int nbs = atoi(argv[1]);
    int nbf = atoi(argv[2]);
    int pid = (int)getpid();

    while (1)
    {
        int i = 0;
        sleep(nbs);
        while (i<nbf) {
            printf("Mon numéro est %d\n", pid);
            i++;
        }
    }
    
    return 0;
}
