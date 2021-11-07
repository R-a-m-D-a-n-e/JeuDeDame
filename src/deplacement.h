#ifndef __DEPLACEMENT
#define __DEPLACEMENT

//Declaration des types et constantes


//Declaration des fonctions

int test_prise_valid(partie_t* partie,coordonnees_t xy);
int test_prise_N(partie_t* partie,coordonnees_t xy);
int test_prise_S(partie_t* partie,coordonnees_t xy);
int test_prise_E(partie_t* partie,coordonnees_t xy);
int test_prise_W(partie_t* partie,coordonnees_t xy);
coordonnees_t piece_prise_coordonnees(coordonnees_t coord1,coordonnees_t coord2);
int test_deplac_N(partie_t* partie,coordonnees_t xy);
int test_deplac_S(partie_t* partie,coordonnees_t xy);
int test_deplac_E(partie_t* partie,coordonnees_t xy);
int test_deplac_W(partie_t* partie,coordonnees_t xy);
int test_move(partie_t* partie,coordonnees_t xy);

#endif
