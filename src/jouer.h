#ifndef __JOUER
#define __JOUER
#include "piece.h"
#include "coordonnees.h"
#include "damier.h"
#include "partie.h"
#include "forme_de_prise.h"
#include "prise_dame.h"


void afficher_prise_ob_p(partie_t *partie,tab_prise_possible_t **prise);

void afficher_prise_ob_d(partie_t *partie,dame_ensemble_t* ens);

int test_promue(partie_t* partie,coordonnees_t coord);

int prise_obligatoire_test(tab_prise_possible_t **prise,dame_ensemble_t* ens);

void select_ensemble_prise_dame(dame_ensemble_t* ens,int i,int j);

int test_appartenire_prise_obligatoire_dame(dame_ensemble_t* ens,coordonnees_t coord,int j);

int test_multi_prise_dame(dame_ensemble_t* ens,int i);

int test_appartenire_inter(dame_ensemble_t* ens,coordonnees_t xy,int i,int j);

void liste_prise_dame(partie_t * partie,dame_ensemble_t* ens);

void deplacement_prise_obligatoire_dame(partie_t * partie,dame_ensemble_t* ens);

tab_prise_possible_t* test_appartenire_prise_obligatoire_piece(partie_t *partie,tab_prise_possible_t **prise,coordonnees_t coord);

void move(partie_t* partie,prise_possible_t* prise,char c);

char choise(prise_possible_t* prise);

void deplacement_prise_obligatoire_piece(partie_t* partie,tab_prise_possible_t *prise);

coordonnees_t saisir_piece_a_depla(partie_t* partie);

void deplacement_normal_piece(partie_t* partie,coordonnees_t coord1);

void deplacement_normal(partie_t* partie);

void detruire_prise_obligatoire(tab_prise_possible_t **prise);

void liste_prise(partie_t *partie);

void supprimer_piece_capture(partie_t* partie);

int prise_obligatoire(partie_t* partie);

void jouer(partie_t* partie);






#endif
