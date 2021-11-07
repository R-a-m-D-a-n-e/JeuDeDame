#include <stdlib.h>
#include <stdio.h>
#include "piece.h"
#include "damier.h"

cases_t creer_cases(piece_t p,couleur_t c)
{
	cases_t res={p,c};
	
	return res;
}

cases_t** creer_damier()
{
	int i;
	cases_t **damier=malloc(10*sizeof(cases_t*));
	
	for(i=0;i<10;i++)
	{
		damier[i]=malloc(10*sizeof(cases_t));
	}

	return damier;
}

void initialier_damier(cases_t **d)
{
	int i,j;

	for(i=9;i>=0;i--)
	{
		for(j=0;j<10;j++)
		{
			if((i%2!=0 && j%2!=0) || (i%2==0 && j%2==0))
			{
				if(i<4)
				{
					d[i][j]=creer_cases(piece_creer(joueur0,non_promue),fancee);
				}
				else
				{
					if(i>5)
					{
						d[i][j]=creer_cases(piece_creer(joueur1,non_promue),fancee);
					}
					else
					{
						d[i][j]=creer_cases(piece_creer(non_joueur,non_promue),fancee);
					}
				}
			}
			else
			{
				d[i][j]=creer_cases(piece_creer(non_joueur,non_promue),claire);
			}
		}
	}

}


void afficher_damier(cases_t **d)
{
	int i,j;

	

	printf("\t\t          \t     ");

	for(i=0;i<10;i++)
	{
		printf("%d  ",i);
	}

	printf("\n");	
	printf("\t\t          	  \033[37;7m                                  \033[0m\n");

	for(i=9;i>=0;i--)
	{
		if(i<4)
		{
			printf("\t\tjoueur0 ->\t");
		}
		else
		{
			if(i>5)
			{
				printf("\t\tjoueur1 ->\t");
			}
			else
			{
				printf("\t\t          \t");
			}
		}
		printf("%d \033[37;7m  \033[0m",i);
		for(j=0;j<10;j++)
		{
			if(d[i][j].couleur==fancee)
			{
				printf(" ");
				piece_afficher(d[i][j].piece);
				printf(" ");
			}
			else
			{
				printf("\033[0;7m   \033[0m");
			}
		}
		printf("\033[37;7m  \033[0m\n");
	}
	printf("\t\t        	  \033[37;7m                                  \033[0m\n");
	printf("\n\n");
}


void detruire_damier(cases_t **d)
{
	int i;
	
	for(i=0;i<10;i++)
	{
		free(d[i]);
	}
	
	free(d);
}











