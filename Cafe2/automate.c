#include <stdio.h>
#include <string.h>
#include "automate.h"
#include <stdlib.h>

void init_par_defaut(automate *A) {
	int i, j ;
	A-> nb_etats = NB_MAX_ETATS ;
	A-> etat_initial = 0 ;
	for (i=0 ; i<NB_MAX_ETATS ; i++)
		A->etats_finals[i]=0 ;
	for (i=0 ; i<NB_MAX_ETATS ; i++) 
		for (j=0 ; j<NB_MAX_ENTREES ; j++)
			A->transitions[i][j]=i ;
	for (i=0 ; i<NB_MAX_ETATS ; i++) 
		for (j=0 ; j<NB_MAX_ENTREES ; j++)
                        strcpy(A->sortie[i][j], "entree_invalide") ;
}
	
	
void init_mon_automate(automate *A) {
	init_par_defaut(A) ;
	A->nb_etats = 2 ;
	A->transitions[0]['2'] = 1 ;
	A->transitions[0]['r'] = 0 ;
	A->transitions[0]['c'] = 0 ;
	A->transitions[1]['2'] = 1 ;
	A->transitions[1]['r'] = 0 ;
	A->transitions[1]['c'] = 0 ;

	strcpy(A->sortie[0]['2'], "credit:20c") ;
	strcpy(A->sortie[0]['r'], "") ;
	strcpy(A->sortie[0]['c'], "") ;
	strcpy(A->sortie[1]['2'], "CLING!-credit:20c") ;
	strcpy(A->sortie[1]['r'], "CLING!") ;
	strcpy(A->sortie[1]['c'], "Boisson_servie") ;
}



void lire_entree(int *s) {
	char c ;
	scanf("\n%c", &c) ;
	*s=(int)c ;
}

void ecrire_sortie(char message[]) {
	printf("%s\n", message) ;
}

void simule_automate(automate *A) {
	int etat_courant, etat_suivant ;
	int symbole_entree= ' ' ;

	etat_courant = A->etat_initial ;
	while (1) {
		lire_entree(&symbole_entree);
		if (symbole_entree==(int)'q'){
			exit(1);
		}else{
			etat_suivant=A->transitions[etat_courant][(char)symbole_entree];
			ecrire_sortie(A->sortie[1][(char)symbole_entree]);
			etat_courant=etat_suivant;		
		}
	}
}

void lecture_automate(automate *A, FILE *f){
	int nb_trans, i ;
	int depart, arrivee ;
	char entree ;
	/* ici il faut appeler init_par_defaut, puis lire le nombre d'états,
	le nombre d'états finals, et tous les états finals */
	init_par_defaut(A);

	int nb_et, nb_etats_fin;
	int etat_fin;
	fscanf(f, "%d", &nb_et) ;
	A->nb_etats=nb_et;

	fscanf(f, "%d", &nb_etats_fin) ;
	for (i=0 ; i< nb_etats_fin ; i++) {
		fscanf(f, "%d", &etat_fin) ;
		A->etats_finals[etat_fin]=1;
	} ;
	
	/* nombre de transitions */
	fscanf(f, "%d", &nb_trans) ;
	for (i=1 ; i<= nb_trans ; i++) {
		fscanf(f, "%d %c %d", &depart, &entree, &arrivee) ;
		A->transitions[depart][(int)entree] = arrivee ;
		A->sortie[depart][(int)entree][0] = '\0' ;
	} ;

	/* terminer par la lecture des sorties */
	int nb_sorties;
	char message[];
	fscanf(f,"%d",&nb_sorties);
	for(int i=1;i<=nb_sorties;i++) {
		fscanf(f, "%d %c %s", &depart, &entree, message);/* scanner un string depuis un fichier? */
		strcpy(&A->sortie[depart][(int)entree],&message);
	}
