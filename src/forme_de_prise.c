#include <stdlib.h>
#include <stdio.h>
#include "coordonnees.h"
#include "partie.h"
#include "forme_de_prise.h"
#include "deplacement.h"


/*ici se trouve les fonction principale de la capture du prion */

//cette fonction ell cree les diferente formes de prise en l'appelant avec un caractere 
tab_prise_possible_t* tab_prise_creer(char c)
{
	tab_prise_possible_t* res=malloc(sizeof(tab_prise_possible_t));


	if(c=='a' || c=='b')
	{
		res->tab=malloc(13*sizeof(prise_possible_t));
		res->taille=13;
		res->prise_max=0;
	}
	if(c=='c' || c=='d')
	{

		res->tab=malloc(12*sizeof(prise_possible_t));
		res->taille=12;
		res->prise_max=0;
	}

	return res;
}
//initialisation des element du tableux de la forme a pour pouvoir manipuler les diferentes case ou un pion peut passer
void tab_initialiser_xy_forme_a(prise_possible_t* tab)
{
	int i,j,k=0;

	for(i=1;i<10;i=i+2)
	{
		for(j=i;j<10;j=j+4)
		{
			tab[k].xy.x=i;
			tab[k].xy.y=j;
			tab[k].E=NULL;
			tab[k].W=NULL;
			tab[k].N=NULL;
			tab[k].S=NULL;
			tab[k].nb_prise=0;
			k++;
		}
	}
	j=k;
	for(i=0;i<j;i++)
	{
		if(tab[i].xy.y!=tab[i].xy.x)
		{
			tab[k].xy.x=tab[i].xy.y;
			tab[k].xy.y=tab[i].xy.x;
			tab[k].E=NULL;
			tab[k].W=NULL;
			tab[k].N=NULL;
			tab[k].S=NULL;
			tab[k].nb_prise=0;
			k++;
		}
	}

}

//initialisation des element du tableux de la forme b pour pouvoir manipuler les diferentes case ou un pion peut passer
void tab_initialiser_xy_forme_b(prise_possible_t* tab)
{
	int i,j,k=0;

	for(i=0;i<10;i=i+2)
	{
		for(j=i;j<10;j=j+4)
		{
			tab[k].xy.x=i;
			tab[k].xy.y=j;
			tab[k].E=NULL;
			tab[k].W=NULL;
			tab[k].N=NULL;
			tab[k].S=NULL;
			tab[k].nb_prise=0;
			k++;
		}
	}
	j=k;
	for(i=0;i<j;i++)
	{
		if(tab[i].xy.y!=tab[i].xy.x)
		{
			tab[k].xy.x=tab[i].xy.y;
			tab[k].xy.y=tab[i].xy.x;
			tab[k].E=NULL;
			tab[k].W=NULL;
			tab[k].N=NULL;
			tab[k].S=NULL;
			tab[k].nb_prise=0;
			k++;
		}
	}

}
//initialisation des element du tableux de la forme c pour pouvoir manipuler les diferentes case ou un pion peut passer  
void tab_initialiser_xy_forme_c(prise_possible_t* tab)
{
	int i,j,k=0;

	for(i=1;i<10;i=i+2)
	{
		for(j=i+2;j<10;j=j+4)
		{
			tab[k].xy.x=i;
			tab[k].xy.y=j;
			tab[k].E=NULL;
			tab[k].W=NULL;
			tab[k].N=NULL;
			tab[k].S=NULL;
			tab[k].nb_prise=0;
			k++;
		}
	}
	j=k;
	for(i=0;i<j;i++)
	{
		tab[k].xy.x=tab[i].xy.y;
		tab[k].xy.y=tab[i].xy.x;
		tab[k].E=NULL;
		tab[k].W=NULL;
		tab[k].N=NULL;
		tab[k].S=NULL;
		tab[k].nb_prise=0;
		k++;
	}

}
//initialisation des element du tableux de la forme d pour pouvoir manipuler les diferentes case ou un pion peut passer 
void tab_initialiser_xy_forme_d(prise_possible_t* tab)
{
	int i,j,k=0;

	for(i=0;i<10;i=i+2)
	{
		for(j=i+2;j<10;j=j+4)
		{
			tab[k].xy.x=i;
			tab[k].xy.y=j;
			tab[k].E=NULL;
			tab[k].W=NULL;
			tab[k].N=NULL;
			tab[k].S=NULL;
			tab[k].nb_prise=0;
			k++;
		}
	}
	j=k;
	for(i=0;i<j;i++)
	{
		tab[k].xy.x=tab[i].xy.y;
		tab[k].xy.y=tab[i].xy.x;
		tab[k].E=NULL;
		tab[k].W=NULL;
		tab[k].N=NULL;
		tab[k].S=NULL;
		tab[k].nb_prise=0;
		k++;
	}

}
//on l'a utiliser pour les testes l'affichage de difernets elesments du tableaux avex les pointeurs sur les queles il pointe 
void tab_forme_prise_afficher(prise_possible_t* tab,int taille)
{
	int i;

	for(i=0;i<taille;i++)
	{
		printf("( %d , %d )\n",tab[i].xy.x,tab[i].xy.y);
	}
	printf("\n");
}
//la detection de la coordonnees la plus petit du tableaux  par rapport dabord a i puis a j 
int tab_forme_prise_min(prise_possible_t* tab,int taille)
{
	int i,min=0;
	
	for(i=0;i<taille;i++)
	{
		if(cmp_coordonnees(tab[i].xy,tab[min].xy)==3)
		{
			min=i;
		}
	}
	return min;
}
//le changement entre deux elelments du tableau
void swap_prise_possible(prise_possible_t *p1,prise_possible_t *p2)
{
	prise_possible_t tempe;

	tempe=*p1;
	*p1=*p2;
	*p2=tempe;

}
// le trie du tableaux par ordre croissant des conndonnees  par rapport au  i  si c'est egal on voie le j 
void tab_forme_prise_trie(prise_possible_t* tab,int taille)
{
	int i,j;
	

	for(i=0;i<taille-1;i++)
	{
		j=tab_forme_prise_min(&tab[i],taille-i)+i;
		swap_prise_possible(&tab[i],&tab[j]);
	}

}

// apres le trie on intilises les pointuers des formes (elements du tablaux) pour les deux formes A et B puique c'est la meme structure 
void tab_initialiser_pointeur_forme_ab(prise_possible_t* tab)
{
	int i;
	

	for(i=0;i<10;i++)
	{
		if(i!=2 && i!=7)
		{
			tab[i].N=&tab[i+3];
		}
	}

	for(i=12;i>2;i--)
	{
		if(i!=5 && i!=10)
		{
			tab[i].S=&tab[i-3];
		}
	}

	for(i=1;i<10;i++)
	{
		if(i!=5)
		{
			tab[i].E=&tab[i+2];
		}
	}

	for(i=12;i>2;i--)
	{
		if(i!=7)
		{
			tab[i].W=&tab[i-2];
		}
	}

}
// apres le trie on intilises les pointuers des formes (elements du tablaux) pour les deux formes C et Dss puique c'est la meme structure 
void tab_initialiser_pointeur_forme_cd(prise_possible_t* tab)
{
	int i;

	for(i=0;i<9;i++)
	{
		if(i!=4)
		{
			tab[i].N=&tab[i+3];
		}
	}

	for(i=11;i>2;i--)
	{
		if(i!=7)
		{
			tab[i].S=&tab[i-3];
		}
	}

	for(i=1;i<10;i++)
	{
		if(i!=2 && i!=7)
		{
			tab[i].E=&tab[i+2];
		}
	}

	for(i=11;i>2;i--)
	{
		if(i!=9 && i!=4)
		{
			tab[i].W=&tab[i-2];
		}
	}

}



// la suppression des pointeurs des cases ou on peut pas se deplacer comme soit meme ou l'adversaire et on laisse juste le vide ou on peut deplacer
 void supprimer_cases_non_valid(partie_t* partie,prise_possible_t* tab,int taille)
{
	int i;

	for(i=0;i<taille;i++)//supprimer les cases non vide adversaire
	{

		if((!case_vide(partie->damier[tab[i].xy.x][tab[i].xy.y]) && partie->damier[tab[i].xy.x][tab[i].xy.y].piece.joueur!=partie->trait) || ( partie->damier[tab[i].xy.x][tab[i].xy.y].piece.statut==promue && partie->damier[tab[i].xy.x][tab[i].xy.y].piece.joueur==partie->trait))//ajouter la condition pour la dame joueur!=promu
		{

			if(tab[i].N!=NULL)
			{
				tab[i].N->S=NULL;
			}
			if(tab[i].S!=NULL)
			{
				tab[i].S->N=NULL;
			}
			if(tab[i].E!=NULL)
			{
				tab[i].E->W=NULL;
			}
			if(tab[i].W!=NULL)
			{
				tab[i].W->E=NULL;
			}
			tab[i].N=NULL;
			tab[i].S=NULL;
			tab[i].E=NULL;
			tab[i].W=NULL;
		}
	}

	for(i=0;i<taille;i++)//supprimer les cases non vide 
	{

		if(!case_vide(partie->damier[tab[i].xy.x][tab[i].xy.y]) && partie->damier[tab[i].xy.x][tab[i].xy.y].piece.joueur==partie->trait)
		{

			if(tab[i].N!=NULL )
			{
				if(partie->damier[tab[i].N->xy.x][tab[i].N->xy.y].piece.joueur==partie->trait)
				{
					tab[i].N->S=NULL;
					tab[i].N=NULL;
				}
			}
			if(tab[i].S!=NULL)
			{
				if(partie->damier[tab[i].S->xy.x][tab[i].S->xy.y].piece.joueur==partie->trait)
				{
					tab[i].S->N=NULL;
					tab[i].S=NULL;
				}
			}

			if(tab[i].E!=NULL )
			{
				if(partie->damier[tab[i].E->xy.x][tab[i].E->xy.y].piece.joueur==partie->trait)
				{
					tab[i].E->W=NULL;
					tab[i].E=NULL;
				}
				

			}

			if(tab[i].W!=NULL )
			{
				if(partie->damier[tab[i].W->xy.x][tab[i].W->xy.y].piece.joueur==partie->trait)
				{
					tab[i].W->E=NULL;
					tab[i].W=NULL;
				}
				
			}

				if(!test_prise_N(partie,tab[i].xy))
				{
					if(tab[i].N!=NULL)
					{
						tab[i].N->S=NULL;
					}
					tab[i].N=NULL;
				}
				if(!test_prise_S(partie,tab[i].xy))
				{
					if(tab[i].S!=NULL)
					{
						tab[i].S->N=NULL;
					}
					tab[i].S=NULL;
				}
				if(!test_prise_E(partie,tab[i].xy))
				{
					if(tab[i].E!=NULL)
					{
						tab[i].E->W=NULL;
					}
					tab[i].E=NULL;
				}
				if(!test_prise_W(partie,tab[i].xy))
				{
					if(tab[i].W!=NULL)
					{
						tab[i].W->E=NULL;
					}
					tab[i].W=NULL;
				}
					
		}
	
}
	for(i=0;i<taille;i++)//supprimer pointeur type . -> .
	{

		if(case_vide(partie->damier[tab[i].xy.x][tab[i].xy.y]))
		{
			if(!test_prise_N(partie,tab[i].xy))
			{
				if(tab[i].N!=NULL)
				{
					tab[i].N->S=NULL;
				}
				tab[i].N=NULL;
			}
			if(!test_prise_S(partie,tab[i].xy))
			{
				if(tab[i].S!=NULL)
				{
					tab[i].S->N=NULL;
				}
				tab[i].S=NULL;
			}
			if(!test_prise_E(partie,tab[i].xy))
			{
				if(tab[i].E!=NULL)
				{
					tab[i].E->W=NULL;
				}
				tab[i].E=NULL;
			}
			if(!test_prise_W(partie,tab[i].xy))
			{
				if(tab[i].W!=NULL)
				{
					tab[i].W->E=NULL;
				}
				tab[i].W=NULL;
			}
		}
	}
}


//on voix le nombre de prises possibles pour un pion juste sr place (le choix)
void prise_possible_nb(prise_possible_t* tab,int taille)
{
	int i;

	for(i=0;i<taille;i++)
	{
		if(tab[i].N!=NULL)
		{
			tab[i].nb_prise++;
		}
		if(tab[i].S!=NULL)
		{
			tab[i].nb_prise++;
		}
		if(tab[i].E!=NULL)
		{
			tab[i].nb_prise++;
		}
		if(tab[i].W!=NULL)
		{
			tab[i].nb_prise++;
		}
	}

}

//maximum de 4 nombres 
int max_4nb(int A,int B,int C,int D)
{
	
	if(A>B)
	{
		B=A;
	}
	if(B>C)
	{
		C=B;
	}
	if(C>D)
	{
		return C;
	}
	return D;
	
}


//la fonction recurssive qui nous detrmime la prise maximum
void piece_prise_max(coordonnees_t *tab,int n,prise_possible_t prise1,prise_possible_t prise2)
{

	int i;
	coordonnees_t coord;

	if(n!=0)
	{
		coord=piece_prise_coordonnees(prise2.xy,prise1.xy);
	}

	for(i=0;i<n;i++)
	{
		if(cmp_coordonnees(coord,tab[i])==1)
			return ;
	}

	if(i!=0)
	{
		tab[i]=coord;
	}


	if(prise1.N!=NULL)
	{
		piece_prise_max(tab,i+1,*prise1.N,prise1);
	}
	if(prise1.S!=NULL)
	{
		piece_prise_max(tab,i+1,*prise1.S,prise1);
	}
	if(prise1.E!=NULL)
	{
		piece_prise_max(tab,i+1,*prise1.E,prise1);
	}
	if(prise1.W!=NULL)
	{
		piece_prise_max(tab,i+1,*prise1.W,prise1);
	}

}
// on supprimes toutes les prise inferieures a la prise maximum detecte 
void supprimer_les_prise_min(coordonnees_t *tab,int n,int max,char *c,prise_possible_t prise1,prise_possible_t prise2)
{

	int i;
	coordonnees_t coord;

	if(n!=0)
	{
		coord=piece_prise_coordonnees(prise1.xy,prise2.xy);
	}

	for(i=0;i<n;i++)
	{
		if(cmp_coordonnees(coord,tab[i])==1)
			return ;
	}

	if(i!=0)
	{
		tab[i]=coord;
	}


	if(prise1.N!=NULL)
	{
		supprimer_les_prise_min(tab,i+1,max,c,*prise1.N,prise1);
	}
	if(prise1.S!=NULL)
	{
		supprimer_les_prise_min(tab,i+1,max,c,*prise1.S,prise1);
	}
	if(prise1.E!=NULL)
	{
		supprimer_les_prise_min(tab,i+1,max,c,*prise1.E,prise1);
	}
	if(prise1.W!=NULL)
	{
		supprimer_les_prise_min(tab,i+1,max,c,*prise1.W,prise1);
	}


	if(i==max)
		*c='M';

}
//on supprime le chemin de la prise minimumm entre deux  prises 
void supprimer_le_chemain_min(coordonnees_t *tab,int n,int max,prise_possible_t prise1,prise_possible_t prise2)
{

	int i;
	coordonnees_t coord;

	if(n!=0)
	{
		coord=piece_prise_coordonnees(prise1.xy,prise2.xy);
	}

	for(i=0;i<n;i++)
	{
		if(cmp_coordonnees(coord,tab[i])==1)
			return ;
	}

	if(i!=0)
	{
		tab[i]=coord;
	}


	if(prise1.N!=NULL)
	{
		supprimer_le_chemain_min(tab,i+1,max,*prise1.N,prise1);
	}
	if(prise1.S!=NULL)
	{
		supprimer_le_chemain_min(tab,i+1,max,*prise1.S,prise1);
	}
	if(prise1.E!=NULL)
	{
		supprimer_le_chemain_min(tab,i+1,max,*prise1.E,prise1);
	}
	if(prise1.W!=NULL)
	{
		supprimer_le_chemain_min(tab,i+1,max,*prise1.W,prise1);
	}


	if(prise1.nb_prise<1 && i<max && n!=0)
	{
		if(prise1.N!=NULL )//ajouter une fonction pour c'a
		{
			prise1.N->S=NULL;
		}
		if(prise1.S!=NULL)
		{
			prise1.S->N=NULL;
		}
		if(prise1.E!=NULL )
		{
			prise1.E->W=NULL;
		}
		if(prise1.W!=NULL )
		{
			prise1.W->E=NULL;
		}
		prise1.N=NULL;
		prise1.S=NULL;
		prise1.E=NULL;
		prise1.W=NULL;
		prise2.nb_prise--;
	}	

}
//on detecte la prise maximum on testant toutes les piece qui appartienne au joueur qui joue pour la rendre une prise obligatoire apres 
int prise_max(partie_t* partie,prise_possible_t* prise,int taille)
{
	int i,n=0,max=0;
	char c='n';
	coordonnees_t *tab=calloc(taille,sizeof(coordonnees_t));


	for(i=0;i<taille;i++)
	{
		if(partie->damier[prise[i].xy.x][prise[i].xy.y].piece.joueur==partie->trait)
		{
			piece_prise_max(tab,n,prise[i],prise[i]);
		}
	}
	for(i=0;i<taille;i++)
	{
		if(tab[i].x!=0 || tab[i].y!=0)
			max++;
	}

	free(tab);

	tab=calloc(taille,sizeof(coordonnees_t));

	for(i=0;i<taille;i++)
	{
		if(partie->damier[prise[i].xy.x][prise[i].xy.y].piece.joueur==partie->trait)
		{
			if(prise[i].N==NULL && prise[i].S==NULL && prise[i].E==NULL && prise[i].W==NULL)
			{
			}
			else
			{
				supprimer_les_prise_min(tab,n,max,&c,prise[i],prise[i]);
				if(c!='M')
				{
					if(prise[i].N!=NULL )
					{
						prise[i].N->S=NULL;
					}
					if(prise[i].S!=NULL)
					{
						prise[i].S->N=NULL;
					}
					if(prise[i].E!=NULL )
					{
						prise[i].E->W=NULL;
					}
					if(prise[i].W!=NULL )
					{
						prise[i].W->E=NULL;
					}
					prise[i].N=NULL;
					prise[i].S=NULL;
					prise[i].E=NULL;
					prise[i].W=NULL;
				}
			}
		}
	}


	return max;
}
//la creation du tableau des prises possible 
tab_prise_possible_t* creer_forme_prise_possible(partie_t *partie,char c)
{
	tab_prise_possible_t* res;
	res=tab_prise_creer(c);
	

	switch (c)
	{
		case 'a':
			tab_initialiser_xy_forme_a(res->tab);
			break;

		case 'b':
			tab_initialiser_xy_forme_b(res->tab);
			break;

		case 'c':
			tab_initialiser_xy_forme_c(res->tab);
			break;

		case 'd':
			tab_initialiser_xy_forme_d(res->tab);
			break;

	}
	if(c=='a' || c=='b')
	{
		tab_forme_prise_trie(res->tab,13);
		tab_initialiser_pointeur_forme_ab(res->tab);
	}
	else
	{
		tab_forme_prise_trie(res->tab,12);
		tab_initialiser_pointeur_forme_cd(res->tab);
	}


	supprimer_cases_non_valid(partie,res->tab,res->taille);
	
	prise_possible_nb(res->tab,res->taille);

	res->prise_max=prise_max(partie,res->tab,res->taille);

	return res;
}
// un affichage qui nous aides au testes pour voir si les pieces de chaque formes sonts bien pointees 
void afficher_pionteur2(tab_prise_possible_t *prise)
{
	int i;

	for(i=0;i<prise->taille;i++)
	{
		printf("( %d , %d ) %d :\n\t",prise->tab[i].xy.x,prise->tab[i].xy.y,prise->tab[i].nb_prise);
		if(prise->tab[i].N!=NULL)
		{
			printf("N : ( %d , %d )\t",prise->tab[i].N->xy.x,prise->tab[i].N->xy.y);
		}

		if(prise->tab[i].S!=NULL)
		{
			printf("S : ( %d , %d )\t",prise->tab[i].S->xy.x,prise->tab[i].S->xy.y);
		}

		if(prise->tab[i].E!=NULL)
		{
			printf("E : ( %d , %d )\t",prise->tab[i].E->xy.x,prise->tab[i].E->xy.y);
		}

		if(prise->tab[i].W!=NULL)
		{
			printf("W : ( %d , %d )\t",prise->tab[i].W->xy.x,prise->tab[i].W->xy.y);
		}

		printf("\n\n");
	}
	printf("\n");
}


// pour la destruction du tableau des formes de prises 
void forme_prise_detruire(tab_prise_possible_t *prise)
{
	free(prise->tab);
	free(prise);
}


//on cree les forme puis on voie toutes les prises si elle sont egales a la maximales si non on les suprime 
void prise_obligatoire_f(partie_t *partie,tab_prise_possible_t **prise)
{
	int max=0;

	prise[0]=creer_forme_prise_possible(partie,'a');
	prise[1]=creer_forme_prise_possible(partie,'b');
	prise[2]=creer_forme_prise_possible(partie,'c');
	prise[3]=creer_forme_prise_possible(partie,'d');


	max=max_4nb(prise[0]->prise_max,prise[1]->prise_max,prise[2]->prise_max,prise[3]->prise_max);

	if(prise[0]->prise_max!=max || prise[0]->prise_max==0)
	{
		forme_prise_detruire(prise[0]);
		prise[0]=NULL;
	}
	if(prise[1]->prise_max!=max || prise[1]->prise_max==0)
	{
		forme_prise_detruire(prise[1]);
		prise[1]=NULL;
	}
	if(prise[2]->prise_max!=max || prise[2]->prise_max==0)
	{
		forme_prise_detruire(prise[2]);
		prise[2]=NULL;
	}
	if(prise[3]->prise_max!=max || prise[3]->prise_max==0)
	{
		forme_prise_detruire(prise[3]);
		prise[3]=NULL;
	}

}








