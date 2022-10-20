#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


void fnc_date() {
  int retour_fils;
  wait(&retour_fils);
  execlp("date", "date", NULL);
  perror("erreur fonction ls");
  exit(1);
}

void fnc_ls () {
  execlp("ls", "ls", "-al", NULL);
  perror("erreur fonction date");
  exit(1);
  }

int main(int argc, char const *argv[]) {
  pid_t pid;

  switch (pid = fork()) {
    case -1:
      perror("Echec creation fils");
      exit(1);
    case 0:
      fnc_ls();
    default:
      fnc_date();

  }

  return 0;
}
