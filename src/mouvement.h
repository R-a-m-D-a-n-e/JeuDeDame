#ifndef __MOUVEMENT
#define __MOUVEMENT
#include "piece.h"
#include "coordonnees.h"
#include "capture.h"

//Declaration des types et constantes

typedef struct mouvement_s
{
	piece_t piece;
	liste_coordonnees_t* position;
	liste_piece_capture_t* capture;

}mouvement_t;

typedef struct maillon_mouvement_s
{
	mouvement_t mouvement;
	struct maillon_mouvement_s *suivant,*precedent;
}maillon_mouvement_t;

typedef struct liste_mouvement_s
{
	maillon_mouvement_t *debut,*fin;
	int taille;
}liste_mouvement_t;

//Declaration des fonctions

maillon_mouvement_t* mouvement_creer();
void mouvement_deteruire(maillon_mouvement_t* m);
liste_mouvement_t* liste_mouvement_initialiser();
int liste_mouvement_vide(liste_mouvement_t l);
int liste_mouvement_card(liste_mouvement_t l);
void liste_mouvement_afficher(liste_mouvement_t l);
void liste_mouvement_ajouter(liste_mouvement_t* l,maillon_mouvement_t* m);
maillon_mouvement_t* liste_mouvement_extraire_debut(liste_mouvement_t* l);
void liste_mouvement_detruire(liste_mouvement_t* l);

#endif





