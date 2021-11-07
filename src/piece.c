#include <stdlib.h>
#include <stdio.h>
#include "piece.h"

piece_t piece_creer(joueur_t j,statut_t s)
{
	piece_t res={j,s};
	
	return res;
}

joueur_t piece_joueur(piece_t p)
{
	return p.joueur;
}

piece_t piece_identifier(char c)
{
	switch (c)	
	{
	case 'P':
		return piece_creer(joueur1,non_promue);break;
	
	case 'D':
		return piece_creer(joueur1,promue);break;
	case 'p':
		return piece_creer(joueur0,non_promue);break;
	case 'd':
		return piece_creer(joueur0,promue);break;		
	case '.':
		return piece_creer(non_joueur,non_promue);break;
	
	}
	
	return piece_creer(non_joueur,non_promue);
	
	
}
char piece_caractere(piece_t p)
{
	if(p.joueur==joueur1)
	{
		if(p.statut)
		{
			return 'D';
		}
		return 'P';
	}
	if(p.joueur==joueur0)
	{
		if(p.statut)
			return 'd';
		return 'p';
	}
	return '.';
}

void piece_afficher(piece_t p)
{
	char c=piece_caractere(p);

	if(c=='p' || c=='d')
		printf("\033[33;1m%c\033[0m",c);
	if(c=='P' || c=='D')
		printf("\033[31;1m%c\033[0m",c);
	if(c=='.')
		printf("\033[0m%c",c);

}

int cmp_piece(piece_t p1,piece_t p2)
{
	if(p1.joueur==p2.joueur && p1.statut==p2.statut)
		return 1;

	return 0;
}













