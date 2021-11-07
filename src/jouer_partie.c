#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "coordonnees.h"
#include "capture.h"
#include "damier.h"
#include "partie.h"
#include "mouvement.h"
#include "deplacement.h"
#include "forme_de_prise.h"
#include "jouer.h"
#include "sauvegarder.h"
#include "jouer_partie.h"


void menu(partie_t* partie)
{
	char acces[30];
	int choix;

	system("resize -s 20 110");
	do{
		system("clear");

		printf("\033[34m_________ _______                          ______   _______      ______   _______  _______  _______  _______ \n");
		printf("\\__    _/(  ____ \\|\\     /||\\     /|      (  __  \\ (  ____ \\    (  __  \\ (  ___  )(       )(  ____ \\(  ____ \\\n");
		printf("   )  (  | (    \\/| )   ( |( \\   / )      | (  \\  )| (    \\/    | (  \\  )| (   ) || () () || (    \\/| (    \\/\n");
		printf("\033[32m   |  |  | (__    | |   | | \\ (_) /       | |   ) || (__        | |   ) || (___) || || || || (__    | (_____ \n");
		printf("   |  |  |  __)   | |   | |  ) _ (        | |   | ||  __)       | |   | ||  ___  || |(_)| ||  __)   (_____  )\n");
		printf("   |  |  | (      | |   | | / ( ) \\       | |   ) || (          | |   ) || (   ) || |   | || (            ) |\n");
		printf("\033[33m|\\_)  )  | (____/\\| (___) |( /   \\ )      | (__/  )| (____/\\    | (__/  )| )   ( || )   ( || (____/\\/\\____) |\n");
		printf("(____/   (_______/(_______)|/     \\|      (______/ (_______/    (______/ |/     \\||/     \\|(_______/\\_______)\033[0m\n\n\n");

		printf("\t\t\t\t\t\t\033[34m1) Jouer\n\n");
		printf("\t\t\t\t\t\t\033[32m2) Quiter\n\n");
		printf("\t\t\t\t\t\t\033[33m3) Chager une partie\n\n\033[0m");
		printf("\t\t\t\t\t\t\033[33m4) le replay d'une partie\n\n\033[0m");
		scanf("%d",&choix);
	}while(choix!=1 && choix!=2 && choix!=3 && choix!=4);

	switch (choix)
	{
		case 1:
			break;
		case 2:
			exit(0);
			partie_detruire(partie);
			break;
		case 3:
			//le chargement il marche pas au menu principale mais dans la partie ca marche 
			printf("inserer un nom pour le fichier ou la partie était sauvegardée  ou un (A) pour annuler: ");
			scanf("%s",acces);
			acces[29]='\0';
			if((acces[0]=='A' || acces[0]=='a') && acces[1]=='\0')
			{	
				menu(partie);
				
			}
			else
			{
				if(partie_charger(acces)!=NULL)
				{
					partie_detruire(partie);
					partie=partie_charger(acces);
					printf("\t\t\t partie chargée \n");
				}
			}
			break;
		case 4: 	
			printf("\n\ninserer le nom du replay que vous voulez voir: ");
			scanf("%s",acces);
			replay_charger(acces);
			
		menu(partie);	
		break;		 	
	}

	system("resize -s 30 110");

}

void afficher_suite_mouvement(partie_t *partie)
{
	maillon_configuration* i=partie->liste_config->fin;

	int j;

	while(i!=NULL)
	{
		system("clear");
		afficher_damier(i->damier);
		i=i->prec;

		for(j=0;j<100000000;j++);
	}

}


void jouer_partie(partie_t* partie)
{
	int choix;

	do
	{
		affiche_plateau(partie);

		jouer(partie);

		do
		{
			printf("1- Valider votre mouvement\t");
			printf("2- Annuler votre mouvement\n");
			printf("___________________________>Votre choix : ");
			scanf("%d",&choix);
		}while(choix!=1 && choix!=2);

		if(choix==1)
		{
			supprimer_piece_capture(partie);
		}
		else
		{
			annuler_mouvement(partie);
		}

		changer_joueur(partie);

	}while(!test_fin_parite(partie));

}


void play()
{
	partie_t * partie;

	menu(partie);

	do
	{
		partie=partie_creer();
		jouer_partie(partie);
		partie_detruire(partie);
		menu(partie);

	}while(1);
}

