#include<stdlib.h>
#include<stdio.h>
#include"partie.h"
#include"coordonnees.h"
#include<time.h>
#include<math.h>
#include "dep_n_dame.h"



int mouvement_possible(partie_t* partie,coordonnees_t coor)
{
	if (case_vide(partie->damier[coor.x+1][coor.y+1]) || case_vide(partie->damier[coor.x-1][coor.y-1]) || case_vide(partie->damier[coor.x-1][coor.y+1])|| case_vide(partie->damier[coor.x+1][coor.y-1]))
			return 1;
	else 
		return 0;
}

int aprartenir_diag(coordonnees_t depart,coordonnees_t arrivee,int* erreur )
{
	if(abs(arrivee.x-depart.x)==abs(arrivee.y-depart.y))
	{
		if (arrivee.x>depart.x)
			if (arrivee.y>depart.y)
				return 1;
			else
				return 2;			
		else 
			if (arrivee.y>depart.y)
				return 3;
			else
				return 4;			
	
	} 

		printf("deplacement non valide \n");
		*erreur=1;
		return 0;
}
//en cas il ya pas de prise obligatoire on appelle cette fonction pour ce qui concerne la dame 
void deplacement_simple_dame(partie_t*  partie ,coordonnees_t depart)
{
	coordonnees_t ab;
	int diag;
	coordonnees_t arrivee;
	int erreur;


	do{
		erreur=0;
		printf("inserer les coordonees d'arivee :");
		arrivee=saisie_case(partie);
		diag=aprartenir_diag(depart,arrivee,&erreur);	
		ab.x=depart.x;
		ab.y=depart.y;

		switch ( diag )
			{	
			case 1 :
				{

					while(coordonnees_valid(ab) && !erreur )
						{
							ab.x++;ab.y++;
							if(!case_vide(partie->damier[ab.x][ab.y]))
							{
								printf("deplacement non valide\n");
								erreur=1;
								break;
							}
	
							if(arrivee.x==ab.x && arrivee.y==ab.y)
							{
								modifier_case(partie,partie->damier[depart.x][depart.y].piece,arrivee);
								modifier_case(partie,piece_creer(non_joueur,non_promue),depart);
								liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(arrivee));
								return;
							}
						
						
						}
						break;
		
				}		
			case 2 :
				{	
					while(coordonnees_valid(ab) && !erreur )
						{
							ab.x++;ab.y--;

							if(!case_vide(partie->damier[ab.x][ab.y]))
							{
								printf("deplacement non valide\n");
								erreur=1;
								break;
							}
							if(arrivee.x==ab.x && arrivee.y==ab.y)
							{
								modifier_case(partie,partie->damier[depart.x][depart.y].piece,arrivee);
								modifier_case(partie,piece_creer(non_joueur,non_promue),depart);
								liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(arrivee));
								return;
							}			

						}
						break;
		
				}		
			case 3 :
				{
		
					while(coordonnees_valid(ab) && !erreur )
						{
							ab.x--;ab.y++;	
							if(!case_vide(partie->damier[ab.x][ab.y]))
							{
								printf("deplacement non valide\n");
								erreur=1;
								break;
							}
							
							if(arrivee.x==ab.x && arrivee.y==ab.y)
							{
								modifier_case(partie,partie->damier[depart.x][depart.y].piece,arrivee);
								modifier_case(partie,piece_creer(non_joueur,non_promue),depart);
					
								liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(arrivee));
								return;
							}
				

						}
					break;
		
				}		
			case 4 :
				{
					while(coordonnees_valid(ab) && !erreur )
						{
							ab.x--;ab.y--;
							if(!case_vide(partie->damier[ab.x][ab.y]))
							{
								printf("deplacement non valide\n");
								erreur=1;
								break;
							}
							if(arrivee.x==ab.x && arrivee.y==ab.y)
							{
								modifier_case(partie,partie->damier[depart.x][depart.y].piece,arrivee);
								modifier_case(partie,piece_creer(non_joueur,non_promue),depart);
								liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(arrivee));
								return;
							}
				

						}
						break;
			
				}	
		}
	}while(erreur);				
			

}		

