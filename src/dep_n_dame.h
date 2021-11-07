#ifndef _DEP_N_DAME
#define _DEP_N_DAME




int mouvement_possible(partie_t *partie,coordonnees_t coor);

int aprartenir_diag(coordonnees_t depart,coordonnees_t arrivee,int* erreur );

void deplacement_simple_dame(partie_t*  partie ,coordonnees_t depart);





#endif
