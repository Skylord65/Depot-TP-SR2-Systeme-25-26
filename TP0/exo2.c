#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char const *argv[]) {
    if(argc!=4) {
        perror("pas le bon nombre d'argument");
        exit(1);
    }
    int nf = atoi(argv[1]);
    int nb = atoi(argv[2]);
    unsigned int ns = atoi(argv[3]);
    int chocolat = 1;
    int tube_chocolat[2];
    //int tube_boite[2];

    if(pipe(tube_chocolat) != 0) {
        perror("pipe chocolat");
        exit(1);
    }

    // if(pipe(tube_boite) != 0) {
    //     perror("pipe boite");
    //     exit(1);
    // }

    pid_t pids[nf];

    for(int i = 0; i < nf; i++) {
        pids[i] = fork();
        switch (pids[i]) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            //close(tube_boite[0]);
            close(tube_chocolat[1]);
            int nb_chocolat = 0;
            int boite = 1;
            int nb_max = i==0 ? 6 : 6*i+6;
            int nb_boite_produite = 0;
            int temp;
            //printf("avant read\n");
            while (read(tube_chocolat[0], &temp, sizeof(int))>0) {
                //printf("après read\n");
                nb_chocolat++;
                if (nb_chocolat==nb_max) {
                    //write(tube_boite[1], &boite, sizeof(int));
                    printf("Emballage %d : nouvelle boite de %d produite\n", i, nb_max);
                    nb_chocolat = 0;
                    nb_boite_produite++;
                }
            }
            printf("Emballage %d : j'ai produit %d boites de %d chocolats\n", i, nb_boite_produite, nb_max);
            //close(tube_boite[1]);
            close(tube_chocolat[0]);
            return i;
            break;
        default:
            break;
        }
    }

    close(tube_chocolat[0]);
    for(int n = 0; n < nb; n++) {
        int chocolat_produit = 0;
        printf("Usine : je produis 60 chocolats\n");
        while (chocolat_produit<60) {
            //printf("patate\n");
            write(tube_chocolat[1], &chocolat, sizeof(int));
            chocolat_produit++;
        }
        sleep(ns);
    }
    close(tube_chocolat[1]);
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
