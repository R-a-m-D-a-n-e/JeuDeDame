#ifndef __FONCTION
#define __FONCTION

//Declaration des types et constantes

enum statut_e{non_promue,promue};
typedef enum statut_e statut_t;

enum joueur_e{joueur0,joueur1,non_joueur};
typedef enum joueur_e joueur_t;

struct piece_s
{
	joueur_t joueur;
	statut_t statut;
};
typedef struct piece_s piece_t;


//Declaration des fonctions utilisateru
piece_t piece_creer(joueur_t j,statut_t s);
joueur_t piece_joueur(piece_t p);
piece_t piece_identifier(char c);
char piece_caractere(piece_t p);
void piece_afficher(piece_t p);
int cmp_piece(piece_t p1,piece_t p2);



#endif
