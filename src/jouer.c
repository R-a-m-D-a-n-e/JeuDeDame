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
#include "prise_dame.h"
#include "dep_n_dame.h"
#include "jouer.h"


void afficher_prise_ob_p(partie_t *partie,tab_prise_possible_t **prise)
{
	int i,j;

	printf("Piece : \t");

	for(i=0;i<4;i++)
	{
		if(prise[i]!=NULL)
		{
			for(j=0;j<prise[i]->taille;j++)
			{
				if(partie->damier[prise[i]->tab[j].xy.x][prise[i]->tab[j].xy.y].piece.joueur==partie->trait)
				{
					if(prise[i]->tab[j].N!=NULL || prise[i]->tab[j].S!=NULL || prise[i]->tab[j].E!=NULL || prise[i]->tab[j].W!=NULL)
					{
						printf("( %d , %d )\t",prise[i]->tab[j].xy.x,prise[i]->tab[j].xy.y);
					}
				}
			}
		}
	}

	printf("\n\n");
}

void afficher_prise_ob_d(partie_t *partie,dame_ensemble_t* ens)
{
	int i;

	printf("Dame : \t");

	for(i=0;i<ens->taille;i++)
	{
		printf("( %d , %d )\t",ens->Dame[i][0].position.x,ens->Dame[i][0].position.y);
	}

	printf("\n\n");

}

int test_promue(partie_t* partie,coordonnees_t coord)
{
	if(partie->trait==joueur0)
	{
		if(coord.x==9 || partie->damier[coord.x][coord.y].piece.statut==promue )
			return promue;
		return non_promue;
	}
	else
	{
		if(coord.x==0 || partie->damier[coord.x][coord.y].piece.statut==promue )
			return promue;
		return non_promue;
	}

}


int prise_obligatoire_test(tab_prise_possible_t **prise,dame_ensemble_t* ens)
{
	int i;

	for(i=0;i<4;i++)
	{
		if(prise[i]!=NULL)
		{
			if(prise[i]->prise_max>ens->max)
				return 1;

			if(prise[i]->prise_max<ens->max)
				return 2;
			return 3;
		}
	}

	if(ens->max>0)
		return 2;

	return 0;
}

void select_ensemble_prise_dame(dame_ensemble_t* ens,int i,int j)
{
	int h=0,k=j,l=i;

	do
	{
		for(k=j;k<=ens->max;k++)
		{
			ens->Dame[h][k]=ens->Dame[l][k];
		}
			h++;
			l++;
	}while(cmp_coordonnees(ens->Dame[l][j].position,ens->Dame[i][j].position)==1);

	ens->taille=h;
	
}

int test_appartenire_prise_obligatoire_dame(dame_ensemble_t* ens,coordonnees_t coord,int j)
{
	int i;

	for(i=0;i<ens->taille;i++)
	{
		if(cmp_coordonnees(ens->Dame[i][j].position,coord)==1)
		{
			return i;
		}
	}

	return -1;
}
int test_multi_prise_dame(dame_ensemble_t* ens,int i)
{
	int l,j;

	if(ens->taille==1)
		return 0;

	for(l=0;l<ens->taille-1;l++)//ens->taille-1
	{
		for(j=l+1;j<ens->taille;j++)
		{
			if(cmp_coordonnees(ens->Dame[j][i].position,ens->Dame[l][i].position)!=1)
				return 1;
		}
	}

	return 0;
}

int test_appartenire_inter(dame_ensemble_t* ens,coordonnees_t xy,int i,int j)
{
	int erreur=0;

	int diag=aprartenir_diag(ens->Dame[i][j].capture,ens->Dame[i][j].position,&erreur);


	if(erreur)
		return 0;


	switch (diag)
	{
		case 1 :
		{
			if((xy.x>ens->Dame[i][j].position.x && xy.x<ens->Dame[i][j+1].capture.x && xy.y>ens->Dame[i][j].position.y && xy.y<ens->Dame[i][j+1].capture.y) )
			
				return 1;

			break;
		}
		case 4 :
		{
			if((xy.x<ens->Dame[i][j].position.x && xy.x>ens->Dame[i][j+1].capture.x && xy.y<ens->Dame[i][j].position.y && xy.y>ens->Dame[i][j+1].capture.y) )
			
				return 1;

			break;
		}
		case 2 :
		{
			if((xy.x>ens->Dame[i][j].position.x && xy.x<ens->Dame[i][j+1].capture.x && xy.y<ens->Dame[i][j].position.y && xy.y>ens->Dame[i][j+1].capture.y) )
			
				return 1;

			break;
		}
		case 3 :
		{
			if((xy.x<ens->Dame[i][j].position.x && xy.x>ens->Dame[i][j+1].capture.x && xy.y>ens->Dame[i][j].position.y && xy.y<ens->Dame[i][j+1].capture.y) )
			
				return 1;

			break;
		}
	}

	return 0;
}

void liste_prise_dame(partie_t * partie,dame_ensemble_t* ens)
{
	int i;

	for(i=1;i<=ens->max;i++)
	{
		liste_piece_capture_ajouter(partie->liste_coups->debut->mouvement.capture,piece_capture_creer(ens->Dame[0][i].capture));

	}

}

void deplacement_prise_obligatoire_dame(partie_t * partie,dame_ensemble_t* ens)
{
	coordonnees_t xy,init=ens->Dame[0][0].position;

	piece_t p;

	int i,j,_bool;

	liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(ens->Dame[0][0].position));

	for(i=1;i<=ens->max-1;i++)
	{
		if(!test_multi_prise_dame(ens,i))
		{
			do
			{
				printf("deplace à : ");
				xy=saisie_case(partie);

			}while(!test_appartenire_inter(ens,xy,0,i) && test_appartenire_prise_obligatoire_dame(ens,xy,i) == -1);
		}
		else
		{
			do
			{
				printf("deplace à : ");
				xy=saisie_case(partie);

				_bool=0;

				j=test_appartenire_prise_obligatoire_dame(ens,xy,i);

				if(j!=-1 || test_appartenire_inter(ens,xy,0,i))
				{
					select_ensemble_prise_dame(ens,j,i);
					_bool=1;
				}
			}while(!_bool);
		}

		modifier_case(partie,partie->damier[init.x][init.y].piece,xy);
		modifier_case(partie,piece_creer(non_joueur,non_promue),init);
		liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(xy));

		affiche_plateau(partie);

		init=xy;
	}

	p=partie->damier[ens->Dame[0][ens->max].capture.x][ens->Dame[0][ens->max].capture.y].piece;

	modifier_case(partie,partie->damier[init.x][init.y].piece,ens->Dame[0][ens->max].capture);
	modifier_case(partie,piece_creer(non_joueur,non_promue),init);
	deplacement_simple_dame(partie,ens->Dame[0][ens->max].capture);
	modifier_case(partie,p,ens->Dame[0][ens->max].capture);

	affiche_plateau(partie);

	liste_prise_dame(partie,ens);
}

tab_prise_possible_t* test_appartenire_prise_obligatoire_piece(partie_t *partie,tab_prise_possible_t **prise,coordonnees_t coord)
{
	int i=0,j,k;
	coordonnees_t *tab;

	if((coord.x-coord.y)%4==0)
	{
		if(coord.x%2==0)
		{
			i=1;//la forme b
		}
		else
		{
			i=0;//la forme a
		}
	}
	else
	{
		if(coord.x%2==0)
		{
			i=3;//la forme d
		}
		else
		{
			i=2;//la forme c
		}
	}


	if(prise[i]==NULL)
		return NULL;



	for(j=0;j<prise[i]->taille;j++)
	{
		if(cmp_coordonnees(prise[i]->tab[j].xy,coord)==1 && partie->damier[prise[i]->tab[j].xy.x][prise[i]->tab[j].xy.y].piece.joueur==partie->trait)//coord trouvee et case=trait
		{
			if(prise[i]->tab[j].N!=NULL || prise[i]->tab[j].S!=NULL || prise[i]->tab[j].E!=NULL || prise[i]->tab[j].W!=NULL)
			{
				tab=calloc(prise[i]->taille,sizeof(coordonnees_t));

			liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(prise[i]->tab[j].xy));//pour la coordonnees initialle
				supprimer_le_chemain_min(tab,0,prise[i]->prise_max,prise[i]->tab[j],prise[i]->tab[j]);

				free(tab);


			for(k=0;k<prise[i]->taille;k++)//supprimer d'auter prise possible
				{
					if(cmp_coordonnees(prise[i]->tab[k].xy,coord)!=1 && partie->damier[prise[i]->tab[k].xy.x][prise[i]->tab[k].xy.y].piece.joueur==partie->trait)
					{
						if(prise[i]->tab[k].N!=NULL )//ajouter une fonction pour c'a
						{
							prise[i]->tab[k].N->S=NULL;
						}
						if(prise[i]->tab[k].S!=NULL)
						{
							prise[i]->tab[k].S->N=NULL;
						}
						if(prise[i]->tab[k].E!=NULL )
						{
							prise[i]->tab[k].E->W=NULL;
						}
						if(prise[i]->tab[k].W!=NULL )
						{
							prise[i]->tab[k].W->E=NULL;
						}
						prise[i]->tab[k].N=NULL;
						prise[i]->tab[k].S=NULL;
						prise[i]->tab[k].E=NULL;
						prise[i]->tab[k].W=NULL;

					}
				}


				return prise[i];
			}
		}
	}

	return NULL;
}

void move(partie_t* partie,prise_possible_t* prise,char c)
{
	switch (c)
	{
		case 'N':
			if(prise->N!=NULL)
			{
				modifier_case(partie,partie->damier[prise->xy.x][prise->xy.y].piece,prise->N->xy);
				modifier_case(partie,piece_creer(non_joueur,non_promue),prise->xy);
				liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(prise->N->xy));//pour les coordonnees_ intermedier
				prise->N->S=NULL;
				prise->N->nb_prise--;
				prise->N=NULL;

			}
			break;
		case 'S':
			if(prise->S!=NULL)
			{
				modifier_case(partie,partie->damier[prise->xy.x][prise->xy.y].piece,prise->S->xy);
				modifier_case(partie,piece_creer(non_joueur,non_promue),prise->xy);
				liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(prise->S->xy));//pour les coordonnees_ intermedier
				prise->S->N=NULL;
				prise->S->nb_prise--;
				prise->S=NULL;
			}
			break;
		case 'E':
			if(prise->E!=NULL)
			{
				modifier_case(partie,partie->damier[prise->xy.x][prise->xy.y].piece,prise->E->xy);
				modifier_case(partie,piece_creer(non_joueur,non_promue),prise->xy);
				liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(prise->E->xy));//pour les coordonnees_ intermedier
				prise->E->W=NULL;
				prise->E->nb_prise--;
				prise->E=NULL;
			}
			break;
		case 'W':
			if(prise->W!=NULL)
			{
				modifier_case(partie,partie->damier[prise->xy.x][prise->xy.y].piece,prise->W->xy);
				modifier_case(partie,piece_creer(non_joueur,non_promue),prise->xy);
				liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(prise->W->xy));//pour les coordonnees_ intermedier
				prise->W->E=NULL;
				prise->W->nb_prise--;
				prise->W=NULL;
			}
			break;
		default :
			move(partie,prise,'N');
			move(partie,prise,'S');
			move(partie,prise,'E');
			move(partie,prise,'W');
			break;
	}
}

char choise(prise_possible_t* prise)
{
	char c;
	
	printf("Choisie une coordonnee (N/S/E/W) : \n");

	if(prise->N!=NULL)
	{
		printf("N : ( %d , %d )\t",prise->N->xy.x,prise->N->xy.y);
	}

	if(prise->S!=NULL)
	{
		printf("S : ( %d , %d )\t",prise->S->xy.x,prise->S->xy.y);
	}

	if(prise->E!=NULL)
	{
		printf("E : ( %d , %d )\t",prise->E->xy.x,prise->E->xy.y);
	}

	if(prise->W!=NULL)
	{
		printf("W : ( %d , %d )\t",prise->W->xy.x,prise->W->xy.y);
	}
	printf("\n");
	do
	{
		printf("___________________________Votre chois : ");
		
		scanf("%c",&c);
	}while(c!='N' && c!='S' && c!='E' && c!='W');

	return c;	
}


void deplacement_prise_obligatoire_piece(partie_t* partie,tab_prise_possible_t *prise)
{
	int i,fin=1;


	if(prise->prise_max==0)
	{
		return;
	}


	for(i=0;i<prise->taille;i++)
	{
		if(partie->damier[prise->tab[i].xy.x][prise->tab[i].xy.y].piece.joueur==partie->trait && (prise->tab[i].N!=NULL || prise->tab[i].S!=NULL || prise->tab[i].E!=NULL || prise->tab[i].W!=NULL))
		{
			fin=0;
			move(partie,&prise->tab[i],choise(&prise->tab[i]));
		}
	}
	
	if(fin)
		return;

	prise->prise_max--;

	affiche_plateau(partie);

	deplacement_prise_obligatoire_piece(partie,prise);

}

coordonnees_t saisir_piece_a_depla(partie_t* partie)
{

	coordonnees_t coord;

	do
	{
		printf("Saisir les coordonnees de la piece a deplace : ");
		coord=saisie_case(partie);
	}while(partie->damier[coord.x][coord.y].piece.joueur!=partie->trait || !test_move(partie,coord));



	return coord;
}

void deplacement_normal_piece(partie_t* partie,coordonnees_t coord1)
{

	coordonnees_t coord2;

	if(partie->trait==joueur0)
	{
		do
		{
			printf("deplace à : ");
			scanf("%d %d",&coord2.x,&coord2.y);
		}while(((coord1.x>=coord2.x || coord1.y>=coord2.y)&& (coord1.x>=coord2.x || coord1.y<=coord2.y)) || !case_vide(partie->damier[coord2.x][coord2.y]) || abs(coord1.x-coord2.x)!=1 || abs(coord1.y-coord2.y)!=1);

	}
	else
	{
		do
		{
			printf("deplace à : ");
			scanf("%d %d",&coord2.x,&coord2.y);
		}while(((coord1.x<=coord2.x || coord1.y<=coord2.y) && (coord1.x<=coord2.x || coord1.y>=coord2.y)) || !case_vide(partie->damier[coord2.x][coord2.y]) || abs(coord1.x-coord2.x)!=1 || abs(coord1.y-coord2.y)!=1);
	}

	liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(coord1));
	liste_coordonnees_ajouter(partie->liste_coups->debut->mouvement.position,coordonnees_creer(coord2));

	modifier_case(partie,partie->damier[coord1.x][coord1.y].piece,coord2);
	modifier_case(partie,piece_creer(non_joueur,non_promue),coord1);


}

void deplacement_normal(partie_t* partie)
{
	coordonnees_t coord1;

	coord1=saisir_piece_a_depla(partie);

	if(partie->damier[coord1.x][coord1.y].piece.statut!=promue)
	{
		deplacement_normal_piece(partie,coord1);
	}
	else
	{
		deplacement_simple_dame(partie,coord1);
	}
}

void detruire_prise_obligatoire(tab_prise_possible_t **prise)
{
	int i;

	for(i=0;i<4;i++)
	{
		if(prise[i]!=NULL)
		{
			forme_prise_detruire(prise[i]);
		}
	}
	
	free(prise);
}

void liste_prise_piece(partie_t *partie)
{
	maillon_coordonnees_t* i=partie->liste_coups->debut->mouvement.position->debut;

	while(i->suivant!=NULL)
	{
		liste_piece_capture_ajouter(partie->liste_coups->debut->mouvement.capture,piece_capture_creer(piece_prise_coordonnees(i->xy,i->suivant->xy)));

		i=i->suivant;
	}

}

void supprimer_piece_capture(partie_t* partie)
{
	maillon_piece_capture_t* i=partie->liste_coups->debut->mouvement.capture->debut;

	while(i!=NULL)
	{
	
		partie->damier[i->piece_cap.xy.x][i->piece_cap.xy.y].piece.joueur=non_joueur;
		i=i->suivant;
	}

}

int prise_obligatoire(partie_t* partie)
{
	coordonnees_t xy;
	tab_prise_possible_t **prise=malloc(4*sizeof(tab_prise_possible_t*));
	tab_prise_possible_t *prise_ob=NULL;
	int prise_ob_d,test;
	dame_ensemble_t* dame_ens=creer_ensemble_prise_dame(partie);

	prise_obligatoire_f(partie,prise);

	test=prise_obligatoire_test(prise,dame_ens);

	if(test==1)
	{
		do
		{
			afficher_prise_ob_p(partie,prise);
			printf("Saisir les coordonnees de la piece a deplace : ");
			prise_ob=test_appartenire_prise_obligatoire_piece(partie,prise,saisie_case(partie));
			printf("%p\n",prise_ob);

		}while(prise_ob==NULL);
		deplacement_prise_obligatoire_piece(partie,prise_ob);
	
		liste_prise_piece(partie);

		printf("%d\n",prise_ob->prise_max);
		return 1;
	}
	else
	{
		if(test==2)
		{
			do
			{
				afficher_prise_ob_d(partie,dame_ens);
				printf("Saisir les coordonnees de la piece a deplace : ");
				prise_ob_d=test_appartenire_prise_obligatoire_dame(dame_ens,saisie_case(partie),0);

			}while(prise_ob_d==-1);
			select_ensemble_prise_dame(dame_ens,prise_ob_d,0);
			deplacement_prise_obligatoire_dame(partie,dame_ens);

			return 1;
		}
		else
		{
			if(test==3)
			{
				do
				{
					afficher_prise_ob_p(partie,prise);
					afficher_prise_ob_d(partie,dame_ens);
					printf("Saisir les coordonnees de la piece a deplace : ");
					xy=saisie_case(partie);
					prise_ob=test_appartenire_prise_obligatoire_piece(partie,prise,xy);
					prise_ob_d=test_appartenire_prise_obligatoire_dame(dame_ens,xy,0);
					printf("%p\n",prise_ob);

				}while(prise_ob==NULL && prise_ob_d==-1);

				if(prise_ob!=NULL)
				{
					deplacement_prise_obligatoire_piece(partie,prise_ob);
	
					liste_prise_piece(partie);

					printf("%d\n",prise_ob->prise_max);
				}
				else
				{
					select_ensemble_prise_dame(dame_ens,prise_ob_d,0);
					deplacement_prise_obligatoire_dame(partie,dame_ens);
				}
				return 1;
			}
		}
	}

	detruire_prise_obligatoire(prise);
	detruire_ensemble(dame_ens);

	return 0;
}

void jouer(partie_t* partie)
{


//////////////////////////// liste mouvement //////////////////////////

	liste_mouvement_ajouter(partie->liste_coups,mouvement_creer());


/////////////////////////////////////////////////////


	if(!prise_obligatoire(partie))
	{
		deplacement_normal(partie);
	}

	ajout_liste_configuration(partie);


	partie->liste_coups->debut->mouvement.piece=partie->damier[partie->liste_coups->debut->mouvement.position->debut->xy.x][partie->liste_coups->debut->mouvement.position->debut->xy.y].piece;

	partie->damier[partie->liste_coups->debut->mouvement.position->debut->xy.x][partie->liste_coups->debut->mouvement.position->debut->xy.y].piece.statut=test_promue(partie,partie->liste_coups->debut->mouvement.position->debut->xy);//test promut

	//la piece en mouvement



}








