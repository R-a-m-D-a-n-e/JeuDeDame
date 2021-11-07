#ifndef __FORME_DE_PRISE
#define __FORME_DE_PRISE
#include "piece.h"
#include "coordonnees.h"
#include "damier.h"
#include "partie.h"
#include "forme_de_prise.h"
//Declaration des canstantes et types

typedef struct prise_possible_s
{
	coordonnees_t xy;
	int nb_prise;
	struct prise_possible_s *E,*W,*N,*S;
}prise_possible_t;


typedef struct tab_prise_possible_s
{
	prise_possible_t *tab;
	int taille;
	int prise_max;
}tab_prise_possible_t;


////////////////       deteruire tab        //////////////


//Declaration des fonctions
tab_prise_possible_t* tab_prise_creer(char c);

void tab_initialiser_xy_forme_a(prise_possible_t* tab);

void tab_initialiser_xy_forme_b(prise_possible_t* tab);

void tab_initialiser_xy_forme_c(prise_possible_t* tab);

void tab_initialiser_xy_forme_d(prise_possible_t* tab);

void tab_forme_prise_afficher(prise_possible_t* tab,int taille);

int tab_forme_prise_min(prise_possible_t* tab,int taille);

void swap_prise_possible(prise_possible_t *p1,prise_possible_t *p2);

void tab_forme_prise_trie(prise_possible_t* tab,int taille);

void tab_initialiser_pointeur_forme_ab(prise_possible_t* tab);

void tab_initialiser_pointeur_forme_cd(prise_possible_t* tab);

//void tab_supprimer_prise_non_valid(prise_possible_t* tab,int* taille);

void supprimer_cases_non_valid(partie_t* partie,prise_possible_t* tab,int taille);

void prise_possible_nb(prise_possible_t* tab,int taille);

int max_4nb(int A,int B,int C,int D);

coordonnees_t piece_prise_coordonnees(coordonnees_t coord1,coordonnees_t coord2);

void piece_prise_max(coordonnees_t *tab,int n,prise_possible_t prise1,prise_possible_t prise2);

void supprimer_les_prise_min(coordonnees_t *tab,int n,int max,char* c,prise_possible_t prise1,prise_possible_t prise2);

void supprimer_le_chemain_min(coordonnees_t *tab,int n,int max,prise_possible_t prise1,prise_possible_t prise2);

int prise_max(partie_t* partie,prise_possible_t* prise,int taille);

tab_prise_possible_t* creer_forme_prise_possible(partie_t *partie,char c);

void afficher_pionteur2(tab_prise_possible_t *prise);

void forme_prise_detruire(tab_prise_possible_t *prise);

void prise_obligatoire_f(partie_t *partie,tab_prise_possible_t **prise);


#endif









