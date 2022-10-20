#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void Afficher(const char *FICH) {      // afficher un fichier
    int fd = open(FICH, O_RDONLY);

    if (fd == -1)
    {
        perror("Erreur ouverture en lecture.");
        exit(1);
    }

    char car;
    size_t rr;
    size_t rw;


    while ((rr = read(fd, &car, sizeof(car))) != 0)
    {
        rw = write(1, &car, sizeof(car));

        if (rw < sizeof(char))
        {
            perror("Disque plein.");
            exit(1);
        }

    }

    if (rr == -1)
    {
        perror("Erreur lecture");
        exit(12);
    }

    close(fd);
}


int main(int argc, char const *argv[]) {
    pid_t pid;
    int borne;

    if (argc == 0) {    // on test s'il y a assez d'argument
        perror("Pas assez d'arguments.");
        exit(1);
    }

    if (strcmp(argv[argc - 2], ">") == 0) {
      borne = argc - 2;
      int dfd;
      dfd = open(argv[argc - 1], O_WRONLY|O_CREAT);
      if (dfd == -1) {
        perror("Erreur ouverture");
        exit(2);
      }
      int dr;
      dr = dup2(1, dfd);
      if (dr == -1) {
        perror("Erreur dup2");
        exit(22);
      }
    }

    else {
      borne = argc;
    }


    for (int i = 1; i < borne; i++) {
      switch (fork()) {
        case -1:
          perror("Erreur creation fils");
          exit(1);

        case 0:
          Afficher(argv[i]);
          break;

        default:
          break;
        }

    }

    return 0;
}
