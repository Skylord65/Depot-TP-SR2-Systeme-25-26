#define _POSIX_C_SOURCE 2008209L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>

#define MONTANT_MAX 20

void handler(int sig) {
    int id = (int)getpid();
    if(sig == SIGINT) {
        printf(">> SIGINT recu par %d\n", id);
    }
}

int main(int argc, char const *argv[]) {
    
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, NULL);

    pid_t pid = fork();
    if(pid==0) {
        int gpid = (int)getpid();
        while (1)
        {
            int i = 0;
            sleep(1);
            while (i<1) {
                printf("Mon numéro est %d\n", gpid);
                i++;
            }
        }
    } else if(pid==-1) {
        perror("erreur du fork");
        exit(1);
    }

    wait(NULL);
    return 0;
}