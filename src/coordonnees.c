#include <stdlib.h>
#include <stdio.h>
#include "piece.h"
#include "coordonnees.h"


maillon_coordonnees_t* coordonnees_creer(coordonnees_t xy)
{
	maillon_coordonnees_t* res=malloc(sizeof(maillon_coordonnees_t));
	res->xy.x=xy.x;
	res->xy.y=xy.y;
	res->suivant=NULL;
	res->precedent=NULL;

	return res;
}

void coordonnees_deteruire(maillon_coordonnees_t* c)
{	
	free(c);
}

liste_coordonnees_t* liste_coordonnees_initialiser()
{
	liste_coordonnees_t* res =malloc(sizeof(liste_coordonnees_t));

	res->debut=NULL;
	res->fin=NULL;
	res->taille=0;

	return res;
}

int liste_coordonnees_vide(liste_coordonnees_t l)
{
	if(l.taille == 0)
		return 1;
	return 0;
}

int liste_coordonnees_card(liste_coordonnees_t l)
{
	return l.taille;
}



void liste_coordonnees_afficher(liste_coordonnees_t l)
{
	maillon_coordonnees_t* i=l.debut;

	while(i!=NULL)
	{
		printf("x = %d ; y = %d\n",i->xy.x,i->xy.y);
		i=i->suivant;
	}

}



void liste_coordonnees_ajouter(liste_coordonnees_t* l,maillon_coordonnees_t* coord)
{
	if(liste_coordonnees_vide(*l))
	{
		l->debut=coord;
		l->fin=coord;
	}
	else
	{
		l->debut->precedent=coord;
		coord->suivant=l->debut;
		l->debut=coord;
	}
	
	l->taille++;

}

maillon_coordonnees_t* liste_coordonnees_extraire_debut(liste_coordonnees_t* l)
{
	maillon_coordonnees_t* coord=l->debut;

	if(l->taille==0)
		return NULL;

	if(l->taille==1)
	{
		l->debut=NULL;
		coord->suivant=NULL;
		l->fin=NULL;
	}
	else
	{
		l->debut=coord->suivant;
		coord->suivant->precedent=NULL;
		coord->suivant=NULL;
	}

	
	l->taille--;

	return coord;
}

void liste_coordonnees_detruire(liste_coordonnees_t* l)
{
	while(!(liste_coordonnees_vide(*l)))
	{
		coordonnees_deteruire(liste_coordonnees_extraire_debut(l));
		
	}
	
	free(l);
	
}

int cmp_coordonnees(coordonnees_t coord1,coordonnees_t coord2)
{
	if(coord1.x>coord2.x)
		return 2;
	if(coord1.x<coord2.x)
		return 3;
	if(coord1.y>coord2.y)
		return 2;
	if(coord1.y<coord2.y)
		return 3;
	return 1;
}


int coordonnees_valid(coordonnees_t coord)
{
	if(coord.x<10 && coord.x>=0 && coord.y<10 && coord.y>=0 && (coord.y+coord.x)%2==0)
	{
		return 1;
	}

	return 0;
}







