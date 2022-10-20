#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


void afficher_infos() {
  pid_t pid = getpid();
  pid_t ppid = getppid();
  pid_t gpig = getpgrp();
  uid_t upid = getuid();
  gid_t numgrp = getgid();

  printf("Pid = %d\n", pid);
  printf("Pid père = %d\n", ppid);
  printf("Pid groupe = %d\n", gpig);
  printf("Numéro utilisateur = %d\n", upid);
  printf("Numéro groupe utilisateur = %d\n", numgrp);
}


int main(int argc, char const *argv[]) {

int retour_fils;
pid_t pid;
switch(pid = fork()) {
  case -1:
    exit(1);
  case 0:
    afficher_infos();
    printf("fils : Je vais afficher : 0\n");
    exit(0);
  default:
    printf("pere : Je vais afficher : 0\n");
    wait(&retour_fils);
    printf("Retour fils = %d\n", WEXITSTATUS(retour_fils));
    exit(0);
  }
  return 0;
}
