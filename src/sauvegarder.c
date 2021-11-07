#include <stdlib.h>
#include <stdio.h>
#include "piece.h"
#include "coordonnees.h"
#include "capture.h"
#include "mouvement.h"
#include "damier.h"
#include "partie.h"
#include "sauvegarder.h"

void partie_sauvegarder(partie_t* part,char* acces)
{
	int d;
	maillon_mouvement_t * i;
	maillon_coordonnees_t* j;
	maillon_piece_capture_t* k;
	maillon_configuration* g; 
	FILE *f=fopen(acces,"w");
	if (f!=NULL)
	{
		fprintf(f,"%c",'P');
		fprintf(f,"%c",'L');
		fprintf(f,"%c",'\n');
	
	if (part!=NULL)	
	{	
		fwrite(&part->trait,sizeof(joueur_t),1,f);	
		if (part->liste_coups!=NULL)
		{	fwrite(&part->liste_coups->taille,sizeof(int),1,f);
			for (i=part->liste_coups->fin;i!=NULL;i=i->precedent)
			{
				fwrite(&i->mouvement.piece,sizeof(piece_t),1,f);
				if(i->mouvement.position!=NULL)
				{	
					fwrite((&i->mouvement.position->taille),sizeof(int),1,f);
					for (j=i->mouvement.position->fin;j!=NULL;j=j->precedent)
						fwrite(&j->xy,sizeof(coordonnees_t),1,f);	
				}
			
				if (i->mouvement.capture!=NULL)
						{
						fwrite(&i->mouvement.capture->taille,sizeof(int),1,f);
						for (k=i->mouvement.capture->fin;k!=NULL;k=k->precedent)
							fwrite(&k->piece_cap,sizeof(piece_capture_t),1,f);
						}
			}
		}	
		if (part->liste_config!=NULL)		
			{
			fwrite(&part->liste_config->taille,sizeof(int),1,f);
			for (g=part->liste_config->fin->prec;g!=NULL;g=g->prec)
				{
					for (d=0;d<10;d++)
						fwrite(g->damier[d],sizeof(cases_t),10,f);
				}
			}
		
	
	}
	}
	fclose(f);		
}
partie_t * partie_charger(char* acces)
{
	FILE *f=fopen(acces,"r") ;

	if (f != NULL)
	{
	char test[3];
	partie_t* part=partie_creer();
	coordonnees_t* coor=malloc(sizeof(coordonnees_t));
	maillon_mouvement_t* mvt=NULL;
	piece_capture_t*  cap=malloc(sizeof(piece_capture_t));
	int i=0,j=0,k=0;
	piece_t p;


		fscanf(f,"%c",test);
		fscanf(f,"%c",test+1);
		fscanf(f,"%c",test+2);
		if (test[0]=='P' && test[1]=='L')
	
		{
			
			fread(&part->trait,sizeof(joueur_t),1,f);
			if (part->liste_coups!=NULL)
			
				{
					fread(&i,sizeof(int),1,f);
					
				for (;i>0;i--)
				{
					mvt=mouvement_creer();
					fread(&mvt->mouvement.piece,sizeof(piece_t),1,f);
					
					if (mvt->mouvement.position!=NULL)				
					{	
						fread(&j,sizeof(int),1,f);
							
							for (;j>0;j--)
								{
									fread(coor,sizeof(coordonnees_t),1,f);
									liste_coordonnees_ajouter(mvt->mouvement.position,coordonnees_creer(*coor));
									}
					}
					if (mvt->mouvement.capture!=NULL)
					{
							fread(&k,sizeof(int),1,f);
							
							for (;k>0;k--)
							{	fread(cap,sizeof(piece_capture_t),1,f);
								liste_piece_capture_ajouter(mvt->mouvement.capture,piece_capture_creer(cap->xy));
							
							}
					}
		
			liste_mouvement_ajouter(part->liste_coups,mvt);
			}
			
		
		if (part->liste_config!=NULL)		
		{
				fread(&i,sizeof(int),1,f);
				
				i=i-1;
				for (;i>0;i--)
				{
					for (j=0;j<10;j++)
						fread((part->damier[j]),sizeof(cases_t),10,f);
					ajout_liste_configuration(part);
				}
			
		}
		}
		}
		else{printf("votre l'acces n'est pas valide\n");}
		fclose(f);
		free(coor);
		free(cap);
	return part;
	}
	printf("la partie %s n'a pas pu ete charger\n",acces);
	return NULL;
}




void plataut_sauvegarder(cases_t** damier,char* fich)
{
//on a fait les  .PL c'est la partie tout entiére avec les listes de confoguration et de mouvment  dans un fichier binaire et PART juste le plataut dans un fichier txt.  	
	int i,j;
	FILE* f;
		
		if (f==NULL)
		{
		f=fopen(fich,"w");
		fprintf(f,"PART\n");
		}
		else
		{
			f=fopen(fich,"a");
			
			for(i=9;i>=0;i--)
			{
				for(j=0;j<10;j++)
					{
					if(damier[i][j].couleur == fancee)
					fprintf(f,"%c",piece_caractere(damier[i][j].piece));
					else 
					fprintf(f," ");
					
					}
			fprintf(f,"\n");				
			}

		fprintf(f,"\n");

		}
			
fclose(f);

}







void replay_charger(char * acces)
{
    char c[10];
    int i,j;
	cases_t **d=creer_damier();
    FILE* f=fopen(acces,"r");

if (f!=NULL )
{
fscanf(f,"part\n",c);
if (strcmp(c,"part\n"))
{
   while(!feof(f))
    {
    	
        for(i=9;i>=0;i--)
        {
            for(j=0;j<10;j++)
            {
                            fscanf(f,"%c",c);
                            if(c[0]==' ')
                            {
                            	  d[i][j].couleur=claire;
                            	 d[i][j].piece=piece_creer(non_joueur,non_promue);
                            	 
                            }
                            else
                            {
                            d[i][j].couleur=fancee;
                            
                            d[i][j].piece=piece_identifier(c[0]);
            
           		}
           		printf("%c",c[0]);		
            }
           fscanf(f,"%c",c); 
           printf("\n");
        }
         printf("\n");
        afficher_damier(d);
        fscanf(f,"%c",c);
    	sleep(1);
    }
    
}
else 
	printf ("erreur de recuperation fichier incorecte");
}

}


