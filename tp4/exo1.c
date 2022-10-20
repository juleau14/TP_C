#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int tube[2];

void compter(int N) {
  char c;
  for (int i = 1; i <= N; i++) {
    c = i + '0';
    write(tube[1], &c, sizeof(char));
    sleep(1);
  }
}

int main(int argc, char const *argv[]) {
  int N;
  N = 5;
  char car;
  int retour_fils;

  if (pipe(tube) == -1) {
    perror("Erreur création tube");
    exit(1);
  }

  switch(fork()) {
    case -1:
      perror("Erreur création fils");
      exit(1);

    case 0:
      close(tube[1]);
      while(read((tube[0]), &car, sizeof(char))) {
        printf("[FILS] ");
        write(1, &car, sizeof(char));
        printf("\n");
      }
      close(tube[0]);
      exit(1);

    default:
      close(tube[0]);
      compter(N);
      close(tube[1]);
      if (wait(&retour_fils) == -1) {
        perror("Pas de fils");
        exit(0);
      }
      printf("[PERE] retour de mon fils : %d\n", WEXITSTATUS(retour_fils));
      exit(0);
  }
}
