#ifndef __COORDONNEES
#define __COORDONNEES
#include "piece.h"
//Coordonnee
struct coordonnees_s
{
	int x,y;
};
typedef struct coordonnees_s coordonnees_t;

typedef struct maillon_coordonnees_s
{
	coordonnees_t xy;
	struct maillon_coordonnees_s *suivant,*precedent;
} maillon_coordonnees_t;

typedef struct liste_coordonnee_s
{
	maillon_coordonnees_t* debut,*fin;
	int taille;
}liste_coordonnees_t;


maillon_coordonnees_t* coordonnees_creer(coordonnees_t xy);
void coordonnees_deteruire(maillon_coordonnees_t* c);
liste_coordonnees_t* liste_coordonnees_initialiser();
int liste_coordonnees_vide(liste_coordonnees_t l);
int liste_coordonnees_card(liste_coordonnees_t l);
void liste_coordonnees_afficher(liste_coordonnees_t l);
void liste_coordonnees_ajouter(liste_coordonnees_t* l,maillon_coordonnees_t* coord);
maillon_coordonnees_t* liste_coordonnees_extraire_debut(liste_coordonnees_t* l);
void liste_coordonnees_detruire(liste_coordonnees_t* l);
int cmp_coordonnees(coordonnees_t coord1,coordonnees_t coord2);// 1-> "=" / 2->">" 3->"<" 
int coordonnees_valid(coordonnees_t coord);


#endif

