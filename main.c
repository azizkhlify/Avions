#include <stdio.h>
#include "avion.h"
#include <stdlib.h>
#include <string.h>


list_av *l;

void menu_general(){
    //system("cls");
    printf("---MENU GENERAL---\n");
    printf("1-Creation du repertoire Avion\n");
    printf("2-Mise a jour des Avions\n");
    printf("3-Recherche , affiche et Tri\n");
    printf("4-Enregistrement et chargement dans un fichier\n");
    printf("5-Quitter\n");
    choix_general();
}
void creer_repertoire() {
    //system("cls");
    unsigned u ;
    char *ch;
    l=creer_list_av();
    printf("--- CREATION ---\n");
    do {
        printf("Avion Num%d :\n",l->nbr+1);
        ajouter_nouveau_avion(l,NULL,0);
        printf("continue ?(oui=1 | non= 0) :");
        scanf("%u",&u);
    }while(u%2);
    menu_general();
}

void choix_general(){
    unsigned u ;
    scanf("%u",&u);
    if (u==1)creer_repertoire();
    else if (u==2)menu_maj(l->premier,1);
    else if (u==3)menu_rat();
    else if (u==4)menu_enrg();
    else if (u==5)EXIT_SUCCESS;
    else menu_general();
}

void menu_maj(node * p,unsigned pos){
    //system("cls");
    int i = 0 , j= 0 ;
    if(p){
    if (p==l->premier)i=1;
    if (p->next && pos<l->nbr)j=1;
    printf("---MENU MAJ---\n");
    printf("               id   |conso|carbu|heure| compagnie | acr \n");
    afficher_avion(p,pos);
    if (j)printf("%d-Passer a l'avion  suivant\n",j);
    if (i)printf("%d-Ajouter un nouvel avion avant cette avion\n",i+j);
    printf("%d-Ajouter un nouvel avion apres cette avion\n",i+1+j);
    printf("%d-Supprimer cette avion\n",i+2+j);
    printf("%d-Modifier les donnees de cette avion\n",i+3+j);
    printf("%d-Retour Menu general\n",i+4+j);
    choix_maj(p,pos,i,j);}
    else menu_general();
}
void choix_maj(node * p,unsigned pos,unsigned i , unsigned j){
    unsigned u ;
    scanf("%u",&u);
    if (u==1 && j==1)menu_maj(p->next,1+pos);
    else if(u==1 && i==1 || ( (i==1 && j==1) && u==2)) {ajouter_nouveau_avion(l,NULL,1); //premier
    menu_general();
    }
    else if (u==1 || u==i+j+1 ){ajouter_nouveau_avion(l,p,0);
    menu_general();}
    else if (u==i+j+2){
        supprimer_pos(l,p);
        menu_general();
    }
    else if (u==i+j+3)menu_modif(p);
    else if (u==i+j+4)menu_general();
    else menu_maj(p,pos);
}
void menu_modif(node * p){
    printf("---MODIFIER---\n");
    printf("1-Identifiant\n");
    printf("2-Compagnie\n");
    printf("3-Rien\n");
    choix_modif(p);
}
void choix_modif(node*p){
    unsigned u ;
    scanf("%u",&u);
    if (u==1){
        char id[7],acro[4];
        do {
        printf("idnetifiant (3caracteres + 3 chiffres) : ");
        scanf("%s",id);
        }while (!id_valide(id));
        strncpy(acro, id, 3);
        acro[3] = '\0';
        strcpy(p->av.id,id);
        strcpy(p->av.comp->acronyme,acro);
        menu_general();
    }
    else if (u==2){
        char nom[10];
        printf("compagnie : ");
        scanf("%s",nom);
        strcpy(p->av.comp->nom,nom);
        menu_general();
    }
    else if (u==3)menu_general();
    else menu_modif(p);
}
void menu_rat(){
 //   system("cls");
    printf("---Recherche,affiche et trie---\n");
    printf("1-Contenu de la liste des avions\n");
    printf("2-Recherche par identifiant avion\n");
    printf("3-Recherche par compagnie\n");
    printf("4-Trie\n");
    printf("5-Retour au menu general\n");
    choix_rat();
}
void choix_rat(){
    unsigned u ;
    scanf("%u",&u);
    if (u==1){
        node * p = l->premier ;
        char id[7];
        unsigned i=1;
        printf("               id   |conso|carbu|heure| compagnie | acr \n");
        while (p){
            afficher_avion(p,i++);
            p=p->next;
        }
        scanf("%s",id);
        menu_general();
    }
    else if (u==2){
        char id[7];
        printf("identifiant (3caracteres + 3 chiffres) : ");
        scanf("%s",id);
        node * p= l->premier ;
        unsigned i =1;
        while (p){
            if (strcmp(p->av.id,id)==0)break;
            p=p->next;
            i++;
        }
        if (p){
            printf("           :   id   |conso|carbu|heure| compagnie | acr \n");
            afficher_avion(p,i);
        }
        else {
            printf("identifiant introuvable");
        }
        scanf("%s",id);
        menu_general();
    }
    else if (u==3){
        char nom[10];
        printf("compagnie : ");
        scanf("%s",nom);
        node * p= l->premier ;
        unsigned i =1;
        while (p){
            if (strcmp(p->av.comp->nom,nom)==0)break;
            p=p->next;
            i++;
        }
        if (p){
            printf("               id   |conso|carbu|heure| compagnie | acr \n");
            afficher_avion(p,i);
        }
        else {
            printf("compagnie introuvable");
        }
        scanf("%s",nom);
        menu_general();
    }
    else if (u==4){
        trier(l);
        menu_general();
    }
    else if (u==5)menu_general();
    else menu_rat();
}
void menu_enrg(){
    //system("cls");
    printf("---MENU ENREGISTREMENT ET CHERGEMENT---\n");
    printf("1-Enregistrement\n");
    printf("2-Chargement\n");
    printf("3-Retour au general\n");
    choix_enrg();
}
void choix_enrg() {
    unsigned u ;
    scanf("%u",&u);
    if (u==1){
    enregistrement();
    menu_general();
    }
    else if (u==2){
    chargement();
    menu_general();
    }
    else if (u==3)menu_general();
    else menu_enrg();
}
void enregistrement(){
    FILE* f;
    f = fopen("save.txt", "w");
    if (f){
        node * p = l->premier ;
        while (p){
            fprintf(f,"%s\n",p->av.id);
            fprintf(f,"%d\n",p->av.consomation);
            fprintf(f,"%d\n",p->av.carburant);
            fprintf(f,"%s\n",p->av.heure_decollage);
            fprintf(f,"%s\n",p->av.comp->nom);
            p=p->next;
        }}
    else {
        printf("ereur.");
    }
    fclose(f);

}

void chargement(){
    FILE* f =fopen("save.txt","r") ;
    free_list(l);
    l=creer_list_av();
    avion a ;
    char id[7] , heure_deco[4] , nom[10], acro[4] ;
    int car , conso;
    while (fscanf(f, "%s", id) == 1){
        fscanf(f,"%d",&conso) ;
        fscanf(f,"%d",&car) ;
        fscanf(f,"%s",heure_deco) ;
        fscanf(f,"%s",nom) ;
        strncpy(acro, id, 3);
        acro[3] = '\0';
        a=creer_avion(id,car,conso,heure_deco,creer_compagnie(nom,acro));
        insere_queue(l,a);
    }
    fclose(f);
}




int main(){
    l=creer_list_av();
    menu_general();
    return 0;
}
