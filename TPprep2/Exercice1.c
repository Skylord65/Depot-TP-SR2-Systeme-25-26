#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int fils(int tube[2]) {
    close(tube[1]);
    void* message;
    int retour;
    while (retour=read(tube[0],message, sizeof(message)))
    {
        if(retour==-1){
            perror("read");
            exit(1);
        }
        printf("Fils - Recu de mon pere : %s\n",message);
    }
    close(tube[0]);
    return 0;
}

int main(int argc, char const *argv[])
{

    if(argc!=2){
        printf("problème dans le nombre de paramètre");
        exit(1);
    }

    int tube[2], NE = atoi(argv[1]);
    
    if(pipe(tube)==-1) {
        perror("pipe");
        exit(1);
    }
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(1);
        break;
    case 0:
        fils(tube);
    default:
        break;
    }

    close(tube[0]);
    int i = 0;
    while (i<NE)
    {

        char message[] = "Je suis ton père...";
        if(write(tube[1], message, sizeof(message)==-1)) {
            perror("write");
            exit(1);
        }
        printf("Pere - Message %d envoye\n", i+1);
        i++;
    }
    close(tube[1]);
    int *status;
    waitpid(pid, status, 0);
    return 0;
}
