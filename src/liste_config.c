
#include<stdio.h>
#include<stdlib.h>
#include"piece.h"
#include "damier.h"
#include"partie.h"

maillon_configuration* maillon_configuration_creer(partie_t* p)
{
	int i,j;	
	maillon_configuration* res=malloc(sizeof(maillon_configuration)); 

	res->damier=creer_damier(); 

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			res->damier[i][j]=p->damier[i][j];
		}
	}

	res->suiv=NULL;
	res->prec=NULL;
	return res;
}

void maillon_configuration_detruire(maillon_configuration* m)
{
	detruire_damier(m->damier);
	free(m);
}


//elle marche en parallele avec la liste des coups si (pas de coups) on cree
void creer_liste_configuration(partie_t* p)
{
	maillon_configuration* m=maillon_configuration_creer(p);
	p->liste_config=malloc(sizeof(liste_configuration));
	
	p->liste_config->debut=m;
	p->liste_config->fin=m;
	p->liste_config->taille=1;
}

//sinon on ajoute
void ajout_liste_configuration(partie_t* p)
{
	maillon_configuration* m=maillon_configuration_creer(p);


	m->suiv=p->liste_config->debut;
	p->liste_config->debut=m;
	m->suiv->prec=m;
	
	p->liste_config->taille++;

	
}
maillon_configuration* liste_configuration_extraire_debut(liste_configuration* l)
{
	maillon_configuration* m=l->debut;

	if(l->taille==0)
		return NULL;

	if(l->taille==1)
	{
		l->debut=NULL;
		l->fin=NULL;
		m->suiv=NULL;
	}
	else
	{
		l->debut=m->suiv;
		m->suiv->prec=NULL;
		m->suiv=NULL;
	}

	
	l->taille--;

	return m;
}

void liste_configuration_detruire(liste_configuration* l)
{

	maillon_configuration* j;
	maillon_configuration* i=l->debut;
	
	while(i!=NULL)
	{
		j=i->suiv;
		maillon_configuration_detruire(i);
		i=j;
	}
	free(l);
}





