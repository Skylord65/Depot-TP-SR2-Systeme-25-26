#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>

// exo à finir si l'envie vient un jour

#define MONTANT_MAX 20

typedef struct tuple_s
{
    char s[2];
    int q;
}Produit;


int main(int argc, char const *argv[]) {
    if(argc!=4) {
        perror("pas le bon nombre d'argument");
        exit(1);
    }
    int nf = atoi(argv[1]);
    pid_t pids[nf];
    int tube_client[2];
    int tube_fournisseur[nf][2];

    for(int j = 0; j<nf; j++) {
        if(pipe(tube_fournisseur[j])) {
            perror("pipe fournisseur");
            exit(1);
        }
    }

    if(pipe(tube_client)) {
        perror("pipe client");
        exit(1);
    }

    for(int i = 0; i < nf; i++) {
        pids[i] = fork();
        switch (pids[i])
        {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            Produit p;
            if(read(tube_fournisseur[i][0], &p, sizeof(struct tuple_s))==-1) {
                perror("produit read fournisseur");
                exit(1);
            }
            // randomizer
            break;
        default:
            break;
        }
    }

    // envoyer produit et quantité

    // traiter montant

    // int *status = malloc(sizeof(int));
    // for(int k = 0; k < nf; k++) {
    //     wait(status);
    //     //printf("Valeur retournee par le fils %d = %ld\n", pids[k], WEXITSTATUS(*status));
    // }
    // free(status);

    //int nb_boite = 0;
    //while (read(tube_boite[0], NULL, sizeof(int)>0)) {
    //    nb_boite++;
    //}
    return 0;
}
