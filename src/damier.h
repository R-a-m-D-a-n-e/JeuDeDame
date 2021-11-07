#ifndef __DAMIER
#define __DAMIER
#include "piece.h"

//Declaration des types constantes
typedef enum couleur_e{claire,fancee}couleur_t;

typedef struct cases_s
{
	piece_t piece;
	couleur_t couleur;
}cases_t;


//Declaration des fonctions
cases_t creer_cases(piece_t p,couleur_t c);
cases_t** creer_damier();
void initialier_damier(cases_t **d);
void afficher_damier(cases_t **d);
void detruire_damier(cases_t **d);


#endif
