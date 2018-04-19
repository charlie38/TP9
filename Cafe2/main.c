#include <stdio.h>
#include "automate.h

int main(int argc, char *argv[]){
    automate A;
    if (argc != 2){
        printf("USAGE: ./test_automate nom_fichier\n");
        exit(1);
    }
    char *nom_fichier = argv[1];
    FILE *f = fopen(nom_fichier,"r");
    lecture_automate(&A,f);
    return 0;
}
