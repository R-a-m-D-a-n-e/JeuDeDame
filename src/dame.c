#include <stdio.h>
#include <stdlib.h>

#include "dame.h"



int diag_id(coordonnees_t a, coordonnees_t b)
{
    if((((9-b.x)-(9-a.x))<0)&&((b.y-(a.y))>0))
        return 0; //diag haut droite
    if((((9-b.x)-(9-a.x))<0)&&((b.y-(a.y))<0))
        return 1; //diag haut gauche
    if((((9-b.x)-(9-a.x))>0)&&((b.y-(a.y))>0))
        return 2; //diag bas droite
    if((((9-b.x)-(9-a.x))>0)&&((b.y-(a.y))<0))
        return 3; //diag bas  droite
   return -1;
}
int deplacement_dame_case_vide(coordonnees_t a, coordonnees_t b,partie_t p) //vide entre la piece a capturer et la fin
{
    int i=diag_id(a,b);
    int vide=1;
    coordonnees_t c;
    switch(i)
    {
    case 0: //Haut droit
        {   c.x=(9-a.x)--;
            c.y=a.y++;
            while((vide)&&(c.x!=(9-b.x))&&(c.y!=b.y))
            {
                if(p.damier[c.x][c.y].couleur!=clair)
                    return 0;
                else
                {
                    c.x--;
                    c.y++;
                }
            }
            return 1;
        }break;

    case 1: //haut gauche

         {  c.x=(9-a.x)--;
            c.y=a.y--;
            while((vide)&&(c.x!=(9-b.x))&&(c.y!=b.y))
            {
                if(p.damier[c.x*10+c.y]!=' ')
                    return 0;
                else
                {
                    c.x--;
                    c.y--;
                }
            }
            return 1;
        }break;

    case 2: //bas droitebreak;
         {  c.x=(9-a.x)++;
            c.y=a.y++;
            while((vide)&&(c.x!=(9-b.x))&&(c.y!=b.y))
            {
                if(p.damier[c.x*10+c.y]!=' ')
                    return 0;
                else
                {
                    c.x++;
                    c.y++;
                }
            }
            return 1;
        }break;printf("\033[H\033[2J")
        break;
    case 3: //bas gauche
         {  c.x=(9-a.x)++;
            c.y=a.y--;
            while((vide)&&(c.x!=(9-b.x))&&(c.y!=b.y))
            {
                if(p.damier[c.x*10+c.y]!=' ')
                    return 0;
                else
                {
                    c.x++;
                    c.y--;
                }
            }
            return 1;
        }break;
    }
}

tab_coor tab_coor_piece(partie_t p,coordonnees_t a)
{
    tab_coor tc;
    int trouve=0;

    //Cas Existe haut droite
    int i=(9-a.x)--;
    int j=a.y++;
    while((i>0)&&(j<10)&&(!trouve))
    {
        if((p.damier[i*10+j].joueur==!(p.damier[a.x*10+a.y].joueur))&&(((i--)>=0)&&((j++)<10))&&((piece_caratere(p.damier[(i--)*10+(j++)]))==' '))
        {
            trouve=1;
            tc.t[0]=1;
            tc.cd[0].x=i;
            tc.cd[0].y=j;
        }
        else
        {
            i--;
            j++;
        }
    }
    if(trouve==0)
    {
        tc.t[0]=0;
        tc.cd[0].x=-1;
        tc.cd[0].y=-1;
    }

    // Cas Existe Haut Gauche

    trouve=0;
    i=(9-a.x)--;
    j=a.y--;
    while((i>0)&&(j>0)&&(!trouve))
    {
        if((p.damier[i*10+j].joueur==!(p.damier[a.x*10+a.y].joueur))&&(((i--)>=0)&&((j--)>=0))&&((piece_caratere(p.damier[(i--)*10+(j--)]))==' '))
        {
            trouve=1;
            tc.t[1]=1;
            tc.cd[1].x=i;
            tc.cd[1].y=j;
        }
        else
        {
            i--;
            j--;
        }
    }
    if(trouve==0)
    {
        tc.t[1]=0;
        tc.cd[1].x=-1;
        tc.cd[1].y=-1;
    }


    // Cas Existe Bas Droite

    trouve=0;
    i=(9-a.x)++;
    j=a.y++;
    while((i<10)&&(j<10)&&(!trouve))
    {
        if((p.damier[i*10+j].joueur==!(p.damier[a.x*10+a.y].joueur))&&(((i++)<10)&&((j++)<10))&&((piece_caratere(p.damier[(i++)*10+(j++)]))==' '))
        {
            trouve=1;
            tc.t[2]=1;
            tc.cd[2].x=i;
            tc.cd[2].y=j;
        }
        else
        {
            i++;
            j++;
        }
    }
    if(trouve==0)
    {
        tc.t[2]=0;
        tc.cd[2].x=-1;
        tc.cd[2].y=-1;
    }

        // Cas Existe Bas Gauche

    trouve=0;
    i=(9-a.x)++;
    j=a.y--;
    while((i<10)&&(j>0)&&(!trouve))
    {
        if((p.damier[i*10+j].joueur==!(p.damier[a.x*10+a.y].joueur))&&(((i++)<10)&&((j--)>=0))&&((piece_caratere(p.damier[(i++)*10+(j--)]))==' '))
        {
            trouve=1;
            tc.t[3]=1;
            tc.cd[3].x=i;
            tc.cd[3].y=j;
        }
        else
        {
            i++;
            j--;
        }
    }
    if(trouve==0)
    {
        tc.t[3]=0;
        tc.cd[3].x=-1;
        tc.cd[3].y=-1;
    }

return tc;

}


void deplacement_dame(partie_t* p, coordonnees_t a, coordonnees_t b )
{
    tab_coor tc;
    int i;
    int x=1; // variable booleenne
    while(x==1)
    {
    tc=tab_coor_piece(*p,a);
    i=diag_id(a,b);
    if((tc.t[i]==0)&&((tc.t[0]==1)||(tc.t[1]==1)||(tc.t[2]==1)||(tc.t[3]==0)))
    {
        do
            printf("resaisissez les coordonnees vous pouvez capturez");
            scanf("%d %d %d %d",&a.x,&a.y,&b.x,&b.y);
        while()
    if((deplacement_dame_case_vide(tc.cd[i],b,*p))
       {
       p->damier[tc.cd[i].x*10+tc.cd[i].y]=piece_caractere(-1,-1); // ' '
       p->damier[b.x*10+b.y]=p->damier[a.x*10+a.y];
       tc.t[i]=0;
       tc.cd[i].x=-1;
       tc.cd[i].y=-1;
       }
    else
    if((tc.t[0]==1)||(tc.t[1]==1)||(tc.t[2]==1)||(tc.t[3]==1))
        do

}


