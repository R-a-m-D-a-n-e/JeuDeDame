#include <stdio.h>
#include "partie.h"
#include "deplacement.h"
#include "forme_de_prise.h"
#include "dep_n_dame.h"


int test_prise_valid(partie_t* partie,coordonnees_t xy)
{

	if(coordonnees_valid(xy) && partie->trait!=partie->damier[xy.x][xy.y].piece.joueur && !case_vide(partie->damier[xy.x][xy.y]))//pour la dame case vide supprimer
	{
		return 1;
	}
	
	return 0;
}

int test_prise_N(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x+1;
	coord.y=xy.y+1;
	
	return test_prise_valid(partie,coord);

}


int test_prise_S(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x-1;
	coord.y=xy.y-1;
	
	return test_prise_valid(partie,coord);

}

int test_prise_E(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x+1;
	coord.y=xy.y-1;

	return test_prise_valid(partie,coord);

}

int test_prise_W(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x-1;
	coord.y=xy.y+1;
	
	return test_prise_valid(partie,coord);

}

coordonnees_t piece_prise_coordonnees(coordonnees_t coord1,coordonnees_t coord2)
{
	coordonnees_t res={0,0};

	res.x=(coord2.x+coord1.x)/2;
	res.y=(coord2.y+coord1.y)/2;

	return res;
}

int test_deplac_N(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x+1;
	coord.y=xy.y+1;

	if (!coordonnees_valid(coord))
		return 0;

	return case_vide(partie->damier[coord.x][coord.y]);
}


int test_deplac_S(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x-1;
	coord.y=xy.y-1;
	
	if (!coordonnees_valid(coord))
		return 0;

	return case_vide(partie->damier[coord.x][coord.y]);

}

int test_deplac_E(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x+1;
	coord.y=xy.y-1;

	if (!coordonnees_valid(coord))
		return 0;

	return case_vide(partie->damier[coord.x][coord.y]);

}

int test_deplac_W(partie_t* partie,coordonnees_t xy)
{
	coordonnees_t coord;
	
	coord.x=xy.x-1;
	coord.y=xy.y+1;
	
	if (!coordonnees_valid(coord))
		return 0;

	return case_vide(partie->damier[coord.x][coord.y]);

}

int test_move(partie_t* partie,coordonnees_t xy)
{

	if(partie->damier[xy.x][xy.y].piece.statut!=promue)
	{
		if(partie->trait==joueur0)
		{
			if(test_deplac_N(partie,xy) || test_deplac_E(partie,xy) )
				return 1;
			return 0;
		}
		if(test_deplac_S(partie,xy)|| test_deplac_W(partie,xy) )
		{
			return 1;
		}
		return 0;
	}

	return mouvement_possible(partie,xy);

}




