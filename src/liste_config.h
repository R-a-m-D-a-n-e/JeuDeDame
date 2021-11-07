#ifndef _LISTE_CONF_H_
#define _LISTE_CONF_H_
#include"piece.h"
#include "partie.h"

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

maillon_configuration* maillon_configuration_creer(partie_t* p);
void maillon_configuration_detruire(maillon_configuration* m);
void creer_liste_configuration(partie_t* p);
void ajout_liste_configuration(partie_t* p);
void liste_configuration_detruire(liste_configuration* l);

#endif
