#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int Remplir[2];
int Etat[2];
#define MAX_BASSIN 5
int f_flags;

void travail_pere() {
  f_flags = fcntl(Etat[0], F_GETFL);
  f_flags |= O_NONBLOCK;
  fcntl(Etat[0], F_SETFL, f_flags);

  int N = 10;

  close(Remplir[0]);

  int entier1 = 1;
  int entier2 = -1;
  int entier3;

  for (int i = 0; i < N; i++) {
    if (write(Remplir[1], &entier1, sizeof(int)) == -1 ) { // le pere ecrite N fois 1 dans le tube Remplir
      perror("Erreur ecriture");
      exit(4);
    }

    sleep(1);     // on attend une seconde

    if (read(Etat[0], &entier3, sizeof(int)) > 0) {     // pere tente de lire qqc dans read
      write(Remplir[1], &entier2, sizeof(int));           // si cela marche, il ecrit -1 dans Remplir
    }

  }
  close(Remplir[1]);

  int retour_fils;
  if (wait(&retour_fils) == -1) {     // le pere attend la fin de son fils
    perror("Pas de fils");
    exit(46);
  }
  printf("\nRetour de mon fils : %d\n", WEXITSTATUS(retour_fils));      // le pere affiche le retour de son fils
}


void travail_fils() {
  int entier;
  int bassin = 0;
  int max_bassin = 5;

  close(Remplir[1]);

  while (read(Remplir[0], &entier, sizeof(int))) {  // le fils lit un entier tant qu'il le peut
    if (entier > 0) {     // si l'entier est positif, il incrémente bassin avec ce dernier
      bassin = bassin + entier;
      printf("*"); fflush(stdout);

      if (bassin >= max_bassin) {          // si bassin > max_bassin, le fils ecrit ecrit la valeur de bassin dans etat
        if (write(Etat[1], &bassin, sizeof(int)) == -1) {
          perror("erreur ecriture");
          exit(45);
        }
      }
    }
    else{                      // sinon si l'entier n'est pas positif, bassin mis a zero
      bassin = 0;
      printf("\n");
    }
  }

  exit(1);      // le fils ne peut plus lire, il s'arrete avec code retour 1
}


int main(int argc, char const *argv[]) {
  if (pipe(Remplir) == -1 || pipe(Etat) == -1) {
    perror("Erreur création tube.");
    exit(1);
  }

  if (pipe(Etat) == -1) {
    perror("Erreur création tube.");
    exit(1);
  }

  switch(fork()) {
    case -1:
      perror("Erreur création fils");
      exit(1);

    case 0:
      travail_fils();

    default:
      travail_pere();
    }

  return 0;
}
