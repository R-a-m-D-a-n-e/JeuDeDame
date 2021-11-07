#include <stdlib.h>
#include <stdio.h>
#include "piece.h"
#include "coordonnees.h"
#include "capture.h"


maillon_piece_capture_t* piece_capture_creer(coordonnees_t xy)
{
	maillon_piece_capture_t* res=malloc(sizeof(maillon_piece_capture_t));
	
	res->piece_cap.xy=xy;
	res->suivant=NULL;
	res->precedent=NULL;

	return res;
}

void piece_capture_deteruire(maillon_piece_capture_t* p)
{	
	free(p);
}

liste_piece_capture_t* liste_piece_capture_initialiser()
{
	liste_piece_capture_t* res =malloc(sizeof(liste_piece_capture_t));

	res->debut=NULL;
	res->fin=NULL;
	res->taille=0;

	return res;
}

int liste_piece_capture_vide(liste_piece_capture_t l)
{
	if(l.taille == 0)
		return 1;
	return 0;
}

int liste_piece_capture_card(liste_piece_capture_t l)
{
	return l.taille;
}



void liste_piece_capture_afficher(liste_piece_capture_t l)
{
	maillon_piece_capture_t* i=l.debut;

	while(i!=NULL)
	{
		printf("x = %d ; y = %d\n",i->piece_cap.xy.x,i->piece_cap.xy.y);
		i=i->suivant;
	}

}


void liste_piece_capture_ajouter(liste_piece_capture_t* l,maillon_piece_capture_t* p)
{
	if(liste_piece_capture_vide(*l))
	{
		l->debut=p;
		l->fin=p;
	}
	else
	{
		l->debut->precedent=p;
		p->suivant=l->debut;
		l->debut=p;
	}
	
	l->taille++;

}

maillon_piece_capture_t* liste_piece_capture_extraire_debut(liste_piece_capture_t* l)
{
	maillon_piece_capture_t* p=l->debut;

	if(l->taille==0)
		return NULL;

	if(l->taille==1)
	{
		l->debut=NULL;
		p->suivant=NULL;
		l->fin=NULL;
	}
	else
	{
		l->debut=p->suivant;
		p->suivant->precedent=NULL;
		p->suivant=NULL;
	}

	
	l->taille--;

	return p;
}

void liste_piece_capture_detruire(liste_piece_capture_t* l)
{
	while(!(liste_piece_capture_vide(*l)))
	{
		piece_capture_deteruire(liste_piece_capture_extraire_debut(l));
		
	}
	
	free(l);
	
}












