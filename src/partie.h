#ifndef __PARTIE
#define __PARTIE
#include "piece.h"
#include "coordonnees.h"
#include "capture.h"
#include "mouvement.h"
#include "damier.h"


//Declaration des types et constante


////////////structure pour liste configuration

typedef struct maillon_s{
	cases_t** damier; 
	struct maillon_s * suiv;
	struct maillon_s * prec;
}maillon_configuration;

typedef struct liste_s{
	maillon_configuration* debut;
	maillon_configuration* fin;
	int taille;	
	}liste_configuration;

///////////structure pour partie
typedef struct partie_s
{
	cases_t **damier;
	liste_mouvement_t* liste_coups;
	liste_configuration* liste_config;
	joueur_t trait;
}partie_t;


//Declaration des fonctions partie

void afficher_fin(joueur_t j);
void affiche_joueur(partie_t* partie);
int case_vide(cases_t c);
void modifier_case(partie_t* partie,piece_t piece,coordonnees_t xy);
void changer_joueur(partie_t *partie);
void affiche_plateau(partie_t *partie);
void modif_damier(partie_t* partie);
void annuler_mouvement(partie_t *partie);
coordonnees_t saisie_case(partie_t* partie);
partie_t* partie_creer();
void partie_detruire(partie_t *partie);
int test_fin_parite(partie_t* partie);



//Declaration des fonctions liste configuration

maillon_configuration* maillon_configuration_creer(partie_t* p);
void maillon_configuration_detruire(maillon_configuration* m);
void creer_liste_configuration(partie_t* p);
void ajout_liste_configuration(partie_t* p);
maillon_configuration* liste_configuration_extraire_debut(liste_configuration* l);
void liste_configuration_detruire(liste_configuration* l);



#endif






