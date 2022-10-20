#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>


void Affiche_inode(struct stat* Infos) {
  if (S_ISREG(Infos->st_mode) != 0) {
    printf("Type: Fichier ordinaire  ");
  }

  else if (S_ISDIR(Infos->st_mode) != 0) {
    printf("Type: Directory  ");
  }

  else if (S_ISFIFO(Infos->st_mode) != 0) {
    printf("Type: Fichier tube  ");
  }

  else if (S_ISCHR(Infos->st_mode) != 0) {
    printf("Type: Periferique caractere  ");
  }

  else if (S_ISBLK(Infos->st_mode) != 0) {
    printf("Type: Peripherique bloc  ");
  }

  printf("Taille octets: %d  ", Infos->st_size);

  time_t temps;
  temps = Infos->st_ctime;
  printf("Date modif: %s", ctime(&temps));
}


void Afficher_dir_inodes(const char * dir_name) {
  DIR * dir_id;
  struct dirent * struct_current_el;
  struct stat Infos;
  int rs;

  dir_id = opendir(dir_name);

  if (dir_id == NULL) {
    perror("erreur opendir");
    exit(1);
  }

  while ((struct_current_el = readdir(dir_id)) != NULL) {
    rs = stat(struct_current_el->d_name, &Infos);
    if (rs == -1) {
      perror("erreur rssss");
      exit(1);
    }
    Affiche_inode(&Infos);
  }

}


int main(int argc, char const *argv[]) {
  if (argc == 1) {
    printf("Veuillez entrer des arguments\n");
    exit(1);
  }

  int rs;
  struct stat Infos;

  if (argc == 2) {
    rs = stat(argv[1], &Infos);
    if (rs == -1) {
      perror("Erreur stat");
      exit(1);
      }
    if (S_ISDIR(Infos.st_mode) != 0) {
      Affiche_inode(&Infos);
      Afficher_dir_inodes(argv[1]);
    }
  }

  else {
    for (int i = 1; i < argc; i++) {
      rs = stat(argv[i], &Infos);
      if (rs == -1) {
        perror("erreur stat");
        exit(1);
      }
  }


  return 0;
}
}
