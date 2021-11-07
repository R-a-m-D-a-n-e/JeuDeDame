#include <stdlib.h>
#include <stdio.h>
#include "piece.h"
#include "coordonnees.h"
#include "damier.h"
#include "partie.h"
#include "prise_dame.h"


void afficher_ensemble(dame_ensemble_t *ens)
{
	int i,j;

	for(i=0;i<ens->taille;i++)
	{
		printf("%d : \n",i);
		for(j=0;j<=ens->max;j++)
		{
			printf("(%d,%d)\t(%d,%d)\n",ens->Dame[i][j].capture.x,ens->Dame[i][j].capture.y,ens->Dame[i][j].position.x,ens->Dame[i][j].position.y);
		}
	
		printf("\n\n");
	}

}


dame_prise_t chercher_piece_cap_N(partie_t* partie,coordonnees_t xy)
{
	dame_prise_t res;

	res.capture=xy;
	res.position.x=xy.x+1;
	res.position.y=xy.y+1;

	do
	{
		res.capture.x++;
		res.capture.y++;
		
		res.position.x++;
		res.position.y++;

		if(coordonnees_valid(res.position) && partie->damier[res.capture.x][res.capture.y].piece.joueur != partie->trait && !case_vide(partie->damier[res.capture.x][res.capture.y]) && case_vide(partie->damier[res.position.x][res.position.y]) )
		{
			return res;
		}



	}while(coordonnees_valid(res.position) && case_vide(partie->damier[res.capture.x][res.capture.y]));

	res.capture=xy;
	res.position=xy;

	return res;
}

dame_prise_t chercher_piece_cap_S(partie_t* partie,coordonnees_t xy)
{
	dame_prise_t res;

	res.capture=xy;
	res.position.x=xy.x-1;
	res.position.y=xy.y-1;

	do
	{
		res.capture.x--;
		res.capture.y--;
		
		res.position.x--;
		res.position.y--;

		if(coordonnees_valid(res.position) && partie->damier[res.capture.x][res.capture.y].piece.joueur != partie->trait && !case_vide(partie->damier[res.capture.x][res.capture.y]) && case_vide(partie->damier[res.position.x][res.position.y]) )
		{
			return res;
		}

	}while(coordonnees_valid(res.position) && case_vide(partie->damier[res.capture.x][res.capture.y]));

	res.capture=xy;
	res.position=xy;

	return res;
}


dame_prise_t chercher_piece_cap_W(partie_t* partie,coordonnees_t xy)
{
	dame_prise_t res;

	res.capture=xy;
	res.position.x=xy.x+1;
	res.position.y=xy.y-1;

	do
	{
		res.capture.x++;
		res.capture.y--;
		
		res.position.x++;
		res.position.y--;

		if(coordonnees_valid(res.position) && partie->damier[res.capture.x][res.capture.y].piece.joueur != partie->trait && !case_vide(partie->damier[res.capture.x][res.capture.y]) && case_vide(partie->damier[res.position.x][res.position.y]) )
		{
			return res;
		}

	}while(coordonnees_valid(res.position) && case_vide(partie->damier[res.capture.x][res.capture.y]));

	res.capture=xy;
	res.position=xy;
	return res;
}

dame_prise_t chercher_piece_cap_E(partie_t* partie,coordonnees_t xy)
{
	dame_prise_t res;

	res.capture=xy;
	res.position.x=xy.x-1;
	res.position.y=xy.y+1;

	do
	{
		res.capture.x--;
		res.capture.y++;
		
		res.position.x--;
		res.position.y++;

		if(coordonnees_valid(res.position) && partie->damier[res.capture.x][res.capture.y].piece.joueur != partie->trait && !case_vide(partie->damier[res.capture.x][res.capture.y]) && case_vide(partie->damier[res.position.x][res.position.y]) )
		{
			return res;
		}

	}while(coordonnees_valid(res.position) && case_vide(partie->damier[res.capture.x][res.capture.y]));

	res.capture=xy;
	res.position=xy;

	return res;
}

int dame_ensemble_appartient(dame_prise_t** Dame,coordonnees_t xy,int i,int j)
{
	int k;

	for(k=0;k<j;k++)
	{
		if(cmp_coordonnees(Dame[i][k].capture,xy)==1)
		{
			return 1;
		}
	}

	return 0;
}

int dame_vecteur_appartient(dame_prise_t** Dame,int i,int ii,int j)
{
	int k;

	if(i==0)
		return 0;

	for(k=0;k<j;k++)
	{
		if(cmp_coordonnees(Dame[i][k].position,Dame[ii][k].position)!=1)
		{
			return 0;
		}
	}


	return 1;
}

int ajouter_ensemble(dame_prise_t** Dame,int i,int j,dame_prise_t move,coordonnees_t xy)
{
	if(dame_ensemble_appartient(Dame,move.capture,i,j))
	{
		return 0;
	}

	if(move.capture.x!=xy.x || move.capture.y!=xy.y )
	{
		Dame[i][j]=move;
		return 1;
	}

	return -1;
}


void dame_prise_max(dame_prise_t** Dame,int *i,int j,int *max)
{
	int k;


	if(j>*max)
	{
		*max=j;
		for(k=0;k<=j;k++)
		{
			Dame[0][k]=Dame[*i][k];
			Dame[1][k]=Dame[*i][k];
		}
		*i=1;
	}
	else
	{
		if(j==*max && !dame_vecteur_appartient(Dame,*i,*i-1,j))
		{
			*i=*i+1;
			for(k=0;k<=j;k++)
			{
				Dame[*i][k]=Dame[*i-1][k];
			}
		}
	}
}


void dame_ensemble_prise(partie_t* partie,coordonnees_t xy,dame_prise_t** Dame,int* i,int j,int* max)
{
	int _bool=0;
	dame_prise_t move;


/////////////////////////////////////////////////////////////////// N

	move=chercher_piece_cap_N(partie,xy);
	_bool=ajouter_ensemble(Dame,*i,j,move,xy);


	if(_bool==1)
	{
		do
		{
			dame_ensemble_prise(partie,move.position,Dame,i,j+1,max);

			move.position.x++;
			move.position.y++;

		}while(coordonnees_valid(move.position) && case_vide(partie->damier[move.position.x][move.position.y]));
	}
/////////////////////////////////////////////////////////////////// S

	move=chercher_piece_cap_S(partie,xy);
	_bool=ajouter_ensemble(Dame,*i,j,move,xy);


	if(_bool==1)
	{
		do
		{
			dame_ensemble_prise(partie,move.position,Dame,i,j+1,max);

			move.position.x--;
			move.position.y--;


		}while(coordonnees_valid(move.position) && case_vide(partie->damier[move.position.x][move.position.y]));
	}
/////////////////////////////////////////////////////////////////// E

	move=chercher_piece_cap_E(partie,xy);
	_bool=ajouter_ensemble(Dame,*i,j,move,xy);

	if(_bool==1)
	{
		do
		{

			dame_ensemble_prise(partie,move.position,Dame,i,j+1,max);

			move.position.x--;
			move.position.y++;

		}while(coordonnees_valid(move.position) && case_vide(partie->damier[move.position.x][move.position.y]));
	}
/////////////////////////////////////////////////////////////////// W

	move=chercher_piece_cap_W(partie,xy);
	_bool=ajouter_ensemble(Dame,*i,j,move,xy);

	if(_bool==1)
	{
		do
		{

			dame_ensemble_prise(partie,move.position,Dame,i,j+1,max);

			move.position.x++;
			move.position.y--;


		}while(coordonnees_valid(move.position) && case_vide(partie->damier[move.position.x][move.position.y]));
	}

	dame_prise_max(Dame,i,j,max);

}


dame_ensemble_t* initialiser_ensemble()
{

	int i;
	dame_ensemble_t* res=calloc(1,sizeof(dame_ensemble_t));
	res->Dame=calloc(10,sizeof(dame_prise_t*));

	for(i=0;i<10;i++)
	{
		res->Dame[i]=calloc(10,sizeof(dame_prise_t));
	}
	return res;
}

void detruire_ensemble(dame_ensemble_t * ens)
{
	int i;

	for(i=0;i<10;i++)
	{
		free(ens->Dame[i]);
	}

	free(ens->Dame);

	free(ens);

}

void dame_ensemble_position(dame_ensemble_t* ens)
{
	int i,j,a,b,c,d,det;

	for(i=0;i<ens->taille;i++)
	{
		for(j=1;j<ens->max;j++)
		{
			a=(ens->Dame[i][j].position.y-ens->Dame[i][j].capture.y)/(ens->Dame[i][j].position.x-ens->Dame[i][j].capture.x);
			b=ens->Dame[i][j].position.y-(a*ens->Dame[i][j].position.x);

			c=(ens->Dame[i][j+1].position.y-ens->Dame[i][j+1].capture.y)/(ens->Dame[i][j+1].position.x-ens->Dame[i][j+1].capture.x);
			d=ens->Dame[i][j+1].position.y-(c*ens->Dame[i][j+1].position.x);

			det=a-c;

			if(det!=0)
			{
				ens->Dame[i][j].position.y=((a*d)-(b*c))/det;
				ens->Dame[i][j].position.x=(d-b)/det;
			}
		}
	}

}

dame_ensemble_t* creer_ensemble_prise_dame(partie_t *partie)
{
	dame_ensemble_t* ens=initialiser_ensemble();
	int i=0,j=1,l,k,max=0;

	for(l=0;l<10;l=l+2)
	{
		for(k=0;k<10;k=k+2)
		{
			if(partie->damier[l][k].piece.joueur==partie->trait && partie->damier[l][k].piece.statut==promue)
			{
				ens->Dame[i][0].position.x=l;
				ens->Dame[i][0].position.y=k;
				dame_ensemble_prise(partie,ens->Dame[i][0].position,ens->Dame,&i,j,&max);
			}

			if(partie->damier[l+1][k+1].piece.joueur==partie->trait && partie->damier[l+1][k+1].piece.statut==promue)
			{
				ens->Dame[i][0].position.x=l+1;
				ens->Dame[i][0].position.y=k+1;
				dame_ensemble_prise(partie,ens->Dame[i][0].position,ens->Dame,&i,j,&max);
			}
		}
	}
		ens->max=max-1;
		ens->taille=i;

	dame_ensemble_position(ens);

	return ens;
}
























