#ifndef _DAME
#define _DAME


typedef struct dame_prise_s{

	coordonnees_t capture,position;

}dame_prise_t;


typedef struct dame_ensemble_s{
	
	dame_prise_t** Dame;
	int max;
	int taille;

}dame_ensemble_t;


///Declaration des fonctions

void afficher_ensemble(dame_ensemble_t *ens);

dame_prise_t chercher_piece_cap_N(partie_t* partie,coordonnees_t xy);

dame_prise_t chercher_piece_cap_S(partie_t* partie,coordonnees_t xy);

dame_prise_t chercher_piece_cap_E(partie_t* partie,coordonnees_t xy);

dame_prise_t chercher_piece_cap_W(partie_t* partie,coordonnees_t xy);

int dame_ensemble_appartient(dame_prise_t** Dame,coordonnees_t xy,int i,int j);

int dame_vecteur_appartient(dame_prise_t** Dame,int i,int ii,int j);

int ajouter_ensemble(dame_prise_t** Dame,int i,int j,dame_prise_t mov,coordonnees_t xy);

void dame_prise_max(dame_prise_t** Dame,int *i,int j,int *max);

void dame_ensemble_prise(partie_t* partie,coordonnees_t xy,dame_prise_t** Dame,int* i,int j,int* max);

dame_ensemble_t* initialiser_ensemble();

void detruire_ensemble(dame_ensemble_t * ens);

dame_ensemble_t* creer_ensemble_prise_dame(partie_t *partie);







#endif
