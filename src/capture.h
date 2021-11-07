#ifndef __CAPTURE
#define __CAPTURE
#include "piece.h"
#include "coordonnees.h"

//Piece capture

//Declaration des types et constantes

typedef struct piece_capture_s
{
	coordonnees_t xy;	
}piece_capture_t;

typedef struct maillon_piece_capture_s
{
	piece_capture_t piece_cap;
	struct maillon_piece_capture_s *suivant,*precedent;
}maillon_piece_capture_t;

typedef struct liste_piece_capture_s
{
	maillon_piece_capture_t *debut,*fin;
	int taille;
}liste_piece_capture_t;

//Declaration desfonctions

maillon_piece_capture_t* piece_capture_creer(coordonnees_t xy);
void piece_capture_deteruire(maillon_piece_capture_t* p);
liste_piece_capture_t* liste_piece_capture_initialiser();
int liste_piece_capture_vide(liste_piece_capture_t l);
int liste_piece_capture_card(liste_piece_capture_t l);
void liste_piece_capture_afficher(liste_piece_capture_t l);
//int liste_piece_capture_appartient(liste_piece_capture_t l,maillon_piece_capture_t p);
void liste_piece_capture_ajouter(liste_piece_capture_t* l,maillon_piece_capture_t* p);
maillon_piece_capture_t* liste_piece_capture_extraire_debut(liste_piece_capture_t* l);
void liste_piece_capture_detruire(liste_piece_capture_t* l);


#endif

