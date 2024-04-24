#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avion.h"

list_av* creer_list_av(){
    list_av* l =malloc(sizeof(list_av));
    if (l==NULL)return l;
    l->premier=l->dernier=NULL;
    l->nbr=0;
    return l;
}
unsigned id_valide(char * id ){
    for (char* c=id;c<=id+2 ;c++){
        if (!('a'<=*c && *c<='z')) return 0 ;
    }
    for (char* c=id+3;c<=id+5 ;c++){
        if (!('1'<=*c && *c<='9')) return 0 ;
    }
    return 1;

}
void ajouter_nouveau_avion(list_av * l,node* p , unsigned u){
    avion a ;
    char id[7] , heure_deco[4] , nom[10], acro[4] ;

    int car , conso;
    do {
        printf("idnetifiant (3caracteres + 3 chiffres) : ");
        scanf("%s",id);
    }while (!id_valide(id));
    strncpy(acro, id, 3);
    acro[3] = '\0';
    printf("consomation : ");
    scanf("%d",&conso) ;
    printf("carburant : ");
    scanf("%d",&car) ;
    printf("heure decollage : ");
    scanf("%s",heure_deco);
    printf("compagnie : ");
    scanf("%s",nom);
    printf("\n");
    compagnie *c=creer_compagnie(nom,acro);
    a=creer_avion(id,car,conso,heure_deco,c);
    if(p==NULL|| p==l->dernier){
            if (u==0)insere_queue(l,a);
            else insere_tete(l,a);}
    else insere_pos(l,a,p);
}
void afficher_avion(node* n , unsigned i ){

    printf("Avion Num%d : %6s | %3d | %3d | %3s | %9s | %3s \n",i,n->av.id,n->av.consomation,n->av.carburant,n->av.heure_decollage,n->av.comp->nom,n->av.comp->acronyme);
}


avion creer_avion(char id[],int car,int con,char h[],compagnie* comp){
    avion a;
    strcpy(a.id,id);
    a.carburant  = car ;
    a.consomation = con ;
    strcpy(a.heure_decollage,h)  ;
    a.comp=comp;
    return a ;
}
compagnie* creer_compagnie(char nom[],char acr[]) {
    compagnie* c;
    c= (compagnie *)malloc(sizeof(compagnie));
    strcpy(c->nom,nom);
    strcpy(c->acronyme,acr);
    return c ;
}
unsigned taille_list(list_av* l){
    return l->nbr;
}
void insere_tete(list_av* l,avion a){
    node* n=malloc(sizeof(node));
    n->av=a;
    n->next = l->premier ;
    l->premier=n;
    if (l->premier==NULL) {
        l->dernier=n;
    }
    l->nbr++;
}
void insere_queue(list_av* l,avion a){
    node* n=malloc(sizeof(node));
    n->av=a;
    n->next = NULL ;
    if (l->nbr==0){
        l->premier=n;
        l->dernier=n;
    }
    else{l->dernier->next=n;
    l->dernier=n;
    if (l->premier==NULL) {
        l->premier=n;
    }}
    l->nbr++;
}
void insere_pos(list_av *l,avion a,node *p){
    if (p==l->premier)insere_tete(l,a);
    else if (p==l->dernier)insere_queue(l,a);
    else {
    node* n=malloc(sizeof(node));
    n->av=a;
    n->next = p->next ;
    p->next=n;
    if (l->premier==NULL) {
        l->premier=n;
    }
    l->nbr++;}
}
void supprimer_tete(list_av* l){
    if (l->nbr==0)return;
    node *n=l->premier ;
    l->premier =l->premier->next ;
    if(l->nbr==1)l->dernier=NULL;
    free(n);
    l->nbr--;
}
void supprimer_queue(list_av* l){
    if (l->nbr==0)return;
    node * p=l->premier ,*v;
    while (p->next!=l->dernier)p=p->next ;
    v=p->next->next;
    free(p->next);
    p->next=v;
    l->dernier=p;
    l->nbr--;
}
void supprimer_pos(list_av* l,node* n){
    if (n==l->premier)
        supprimer_tete(l);
    else if (n==l->dernier)
        supprimer_queue(l);
    else {
    node * p=l->premier ,*v;
    while (p->next!=n)p=p->next ;
    v=p->next->next;
    free(p->next);
    p->next=v;
    l->nbr--;}
}
void trier(list_av*  l){
    int swapped;
    node* p;
    avion v;
    if (l->nbr<=1)
        return;
    do {
        swapped = 0;
        p = l->premier;
        while (p && p->next) {
            if (p->av.consomation > p->next->av.consomation) {
                v=p->next->av;
                p->next->av=p->av;
                p->av=v;
                swapped = 1;
            }
            p = p->next;
        }
    } while (swapped);
}
void free_list(list_av * l ){
    node* p=l->premier, *v=p;
    while (p){
        p=p->next;
        free(v);
        v=p;
    }
}
