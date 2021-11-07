#ifndef _SAV
#define _SAV


void partie_sauvegarder(partie_t* part,char* acces);

partie_t * partie_charger(char* acces);

void plataut_sauvegarder(cases_t** damier,char* fich);

void replay_charger(char * acces);

#endif
