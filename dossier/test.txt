#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define NBMOTSMAX 20
/* Construction d’un tableau de pointeurs vers le d´ebut des mots d’une cha^ıne
* de caract`eres en vue de l’utilisation de la fonction execvp.
* Retourne le nombre de mots trouv´es.
*/
int Decoupe(char Chaine[], char *pMots[]){
  char *p;
  int NbMots=0;
  p=Chaine; /* On commence par le d´ebut */
/* Tant que la fin de la cha^ıne n’est pas atteinte et qu’on ne d´eborde pas */
  while ((*p)!=’\0’ && NbMots<NBMOTSMAX)
  {
    while ((*p)==’ ’ && (*p)!=’\0’) p++; /* Recherche du d´ebut du mot */
    if ((*p)==’\0’) break; /* Fin de chaine atteinte */
    pMots[NbMots++]=p; /* Rangement de l’adresse du 1er caract`ere du mot */
    while ((*p)!=’ ’ && (*p)!=’\0’) p++; /* Recherche de la fin du mot */
    if ((*p)==’\0’) break; /* Fin de cha^ıne atteinte */
    *p=’\0’; /* Marquage de la fin du mot */
    p++; /* Passage au caract`ere suivant */
  }
  pMots[NbMots]=NULL; /* Derni`ere adresse */
  return NbMots;
}






int main(int argc, char const *argv[]) {
  for (size_t i = 1; i < argc; i++) {
    pid_t pid;
    char *cmd[];
    cmd = Decoupe()
    switch (pid = fork()) {
      case -1:
        perror("Erreur creation fils");
        exit(1);
      case 0:
        execvp(argv[i], argv[i])
    }
  }

  return 0;
}
