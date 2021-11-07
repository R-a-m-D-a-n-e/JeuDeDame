#include <stdlib.h>
#include <stdio.h>
#include "piece.h"
#include "coordonnees.h"
#include "capture.h"
#include "mouvement.h"
#include "damier.h"
#include "partie.h"
#include "sauvegarder.h"
#include "jouer_partie.h"

void afficher_fin(joueur_t j)
{
	char c;

	system("resize -s 20 110");
	system("clear");

	printf("\n\n\n\n\n");


	if(j==joueur0)
	{
		printf("\t\t\t\t\033[33;1m     _                              ___  \n");
		printf("\t\t\t\t\033[33;1m    | | ___  _   _  ___ _   _ _ __ / _ \\ \n");
		printf("\t\t\t\t\033[33;1m _  | |/ _ \\| | | |/ _ \\ | | | \'__| | | |\n");
		printf("\t\t\t\t\033[33;1m| |_| | (_) | |_| |  __/ |_| | |  | |_| |\n");
		printf("\t\t\t\t\033[33;1m \\___/ \\___/ \\__,_|\\___|\\__,_|_|   \\___/ \n\033[33;0m");
	}
	else
	{
		printf("\t\t\t\t\033[34;1m     _                               _ \n");
		printf("\t\t\t\t\033[34;1m    | | ___  _   _  ___ _   _ _ __  / |\n");
		printf("\t\t\t\t\033[34;1m _  | |/ _ \\| | | |/ _ \\ | | | \'__| | |\n");
		printf("\t\t\t\t\033[34;1m| |_| | (_) | |_| |  __/ |_| | |    | |\n");
		printf("\t\t\t\t\033[34;1m \\___/ \\___/ \\__,_|\\___|\\__,_|_|    |_|\n\033[33;0m");

	}
	scanf("%c",&c);
	scanf("%c",&c);
}
void affiche_joueur(partie_t* partie)
{
	printf("\t\t\t\t\t\t");
	if(partie->trait==joueur0)
	{
		printf("\033[33;1mJOUEUR 0 \033[0m\n");
		printf ("\033[34;1\tminser un (S) pour sauvegarder (Q) pour quiter et (R) pour le replay (C) pour chager une partie \033[0m\n");
	}
	else
	{
		printf("\033[31;1mJOUEUR 1 \033[0m\n");
		printf ("\033[36;1m\tinser un (S) pour sauvegarder (Q) pour quiter et (R) pour le replay (C) pour charger une partie  \033[0m\n");
	}
	printf("\n\n\n");

}

int case_vide(cases_t c)
{
	if(c.piece.joueur==non_joueur)
	{
		return 1;
	}
	return 0;
}

void modifier_case(partie_t* partie,piece_t piece,coordonnees_t xy)
{
	partie->damier[xy.x][xy.y].piece=piece;

}

void changer_joueur(partie_t *partie)
{
	if(partie->trait==joueur0)
	{
		partie->trait=joueur1;
	}
	else
	{
		partie->trait=joueur0;
	}
}


void affiche_plateau(partie_t *partie)
{
	system("clear");

	afficher_damier(partie->damier);

	affiche_joueur(partie);

}


void annuler_mouvement(partie_t *partie)
{
	maillon_configuration* config;
	int i,j;

	mouvement_deteruire(liste_mouvement_extraire_debut(partie->liste_coups));

	config=liste_configuration_extraire_debut(partie->liste_config);

	maillon_configuration_detruire(config);


	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			partie->damier[i][j]=partie->liste_config->debut->damier[i][j];
		}

	}

	
	//changer joueur
	changer_joueur(partie);

}


coordonnees_t saisie_case(partie_t* partie)
{
	char x[2],y[2],acces[30];
	coordonnees_t res;
	int valid=0;
	do{
		if(valid==0)
		{
			valid++;
		}
		else
		{
			printf("coordonnees non valid veuillez ressaisir  :");
		}
		
		scanf("%s %s",x,y);
		if(x[0]=='s' || y[0]=='s' || x[0]=='S'|| y[0]=='S')
		{
			printf("inserer un nom pour le fichier ou vous allrez sauvegarder : ");
				scanf("%s",acces);
				acces[29]='\0';
				partie_sauvegarder(partie,acces);
				printf("\t\t\t partie sauvegardée \n");
				valid=0;
				affiche_plateau(partie);
			
		}
		if(x[0]=='c' || y[0]=='c' || x[0]=='C'|| y[0]=='C')
		{
	
				printf("inserer un nom pour le fichier ou la partie était sauvegardée  ou un (A) pour annuler: ");
				scanf("%s",acces);
				acces[29]='\0';
				if((acces[0]=='A' || acces[0]=='a') && acces[1]=='\0')
				{
					
				}
				else
				{
					if(partie_charger(acces)!=NULL)
					{
						partie_detruire(partie);
						partie=partie_charger(acces);
						printf("\t\t\t partie chargée \n");
					}
					valid=0;
				}
				affiche_plateau(partie);				
				printf("inserer les coordonnees de la piece a deplacer : ");		
		}
		else 
		if(x[0]=='r' || y[0]=='r' || x[0]=='R'|| y[0]=='R')
		{
			valid=0;
			char fich[30];
			int ch;
			do
			{
			printf("\n inserer 1 pour enregistrer une nouvelle ou 0 pour voir existante : ");
			scanf("%d",&ch);
			}while(ch!=1 && ch !=0);
			
			if (ch==1)
			{
					printf("\n\ninserer un ficher ou un acces ou vous voulez sauvegarder le replay : ");
					scanf("%s",fich);
				 	maillon_configuration* d=partie->liste_config->fin;	
					do
					{
					plataut_sauvegarder(d->damier,fich);
					d=d->prec;
					}while(d!=NULL);
					affiche_plateau(partie);
				
					
			}
			else
			{
			printf("\n\ninserer le nom du replay : ");
			scanf("%s",fich);
			replay_charger(fich);
			affiche_plateau(partie);				
			}	
		printf("inserer les coordonnees de la piece a deplacer : ");		
		}
		else 
		if(x[0]=='q' || y[0]=='q' || x[0]=='Q'|| y[0]=='Q')
		{
			do 
			{
			printf("voulez vous sauvegarder inserer (O ou o\\N ou n) :  ");
			scanf("%s",x);
			}while(x[0]!='O' && x[0]!='o' && x[0]!='n' && x[0]!='N');
			if (x[0]=='O' || x[0]=='o')
				{
				printf("inserer un nom pour le fichier ou vous allez sauvegarder : ");
				scanf("%s",acces);
				partie_sauvegarder(partie,acces);
					printf("\t\t\t partie sauvegardée \n");
						
				}
			printf("\t\t\ta bien tot \n");	
			exit(0);
				
		}		
		else 
			
		res.x=atoi(x);
		res.y=atoi(y);
		
	}while(!coordonnees_valid(res));

	return res;
}



partie_t* partie_creer()
{
	partie_t *res=malloc(sizeof(partie_t));

	res->damier=creer_damier();
	initialier_damier(res->damier);

	res->liste_coups=liste_mouvement_initialiser();

	creer_liste_configuration(res);

	res->trait=joueur0;

	return res;
}

void partie_detruire(partie_t *partie)
{
	liste_mouvement_detruire(partie->liste_coups);
	detruire_damier(partie->damier);
	liste_configuration_detruire(partie->liste_config);
	free(partie);
}

int test_fin_parite(partie_t* partie)
{
	int i,j;
	int pieceP0=0,pieceP1=0,piece0=0,piece1=0;

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(partie->damier[i][j].piece.joueur==joueur0)
			{
				if(partie->damier[i][j].piece.statut==promue)
				{
					piece0++;
				}
				else
				{
					pieceP0++;
				}
			}
			if(partie->damier[i][j].piece.joueur==joueur1)
			{
				if(partie->damier[i][j].piece.statut==promue)
				{
					piece1++;
				}
				else
				{
					pieceP1++;
				}
			}
		}
	
	}


	if((piece0+pieceP0)==0)
	{
		afficher_fin(joueur1);
		return 1;
	}
	if((piece1+pieceP1)==0)
	{
		afficher_fin(joueur0);
		return 1;
	}

	return 0;
}


















