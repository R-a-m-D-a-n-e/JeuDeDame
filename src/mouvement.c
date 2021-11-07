#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "coordonnees.h"
#include "capture.h"
#include "mouvement.h"



maillon_mouvement_t* mouvement_creer()
{
	maillon_mouvement_t* res=malloc(sizeof(maillon_mouvement_t));
	
	res->mouvement.position=liste_coordonnees_initialiser();
	res->mouvement.capture=liste_piece_capture_initialiser();
	res->suivant=NULL;
	res->precedent=NULL;
	return res;
}

void mouvement_deteruire(maillon_mouvement_t* m)
{	
	liste_piece_capture_detruire(m->mouvement.capture);
	liste_coordonnees_detruire(m->mouvement.position);
	free(m);
}

liste_mouvement_t* liste_mouvement_initialiser()
{
	liste_mouvement_t* res =malloc(sizeof(liste_mouvement_t));

	res->debut=NULL;
	res->fin=NULL;
	res->taille=0;

	return res;
}

int liste_mouvement_vide(liste_mouvement_t l)
{
	if(l.taille == 0)
		return 1;
	return 0;
}

int liste_mouvement_card(liste_mouvement_t l)
{
	return l.taille;
}



void liste_mouvement_afficher(liste_mouvement_t l)
{
	maillon_mouvement_t* i=l.debut;

	while(i!=NULL)
	{
		printf("la piece en mouvement : \n");
		piece_afficher(i->mouvement.piece);
		printf("\n");
		printf("liste des positions : \n");
		liste_coordonnees_afficher(*(i->mouvement.position));
		printf("\n");
		printf("liste des pieces captures : ");
		liste_piece_capture_afficher(*(i->mouvement.capture));
		i=i->suivant;
	}

}



void liste_mouvement_ajouter(liste_mouvement_t* l,maillon_mouvement_t* m)
{
	if(liste_mouvement_vide(*l))
	{
		l->debut=m;
		l->fin=m;
	}
	else
	{
		l->debut->precedent=m;
		m->suivant=l->debut;
		l->debut=m;
	}
	
	l->taille++;

}

maillon_mouvement_t* liste_mouvement_extraire_debut(liste_mouvement_t* l)
{
	maillon_mouvement_t* m=l->debut;

	if(l->taille==1)
	{
		l->debut=NULL;
		m->suivant=NULL;
		l->fin=NULL;
	}
	else
	{
		l->debut=m->suivant;
		m->suivant->precedent=NULL;
		m->suivant=NULL;
	}

	
	l->taille--;

	return m;
}

void liste_mouvement_detruire(liste_mouvement_t* l)
{
	while(!(liste_mouvement_vide(*l)))
	{
		mouvement_deteruire(liste_mouvement_extraire_debut(l));
		
	}
	
	free(l);
	
}












