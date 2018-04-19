#include <stdio.h>
#include "automate.h

int main(int argc, char *argv[]){
    automate A;
    if (argc != 2){
        printf("USAGE: ./test_automate nom_fichier\n");
        exit(1);
    }
    FILE *f = fopen(argv[1],"r");
    lecture_automate(&A,f);
    simule_automate(&A);
    return 0;
}
