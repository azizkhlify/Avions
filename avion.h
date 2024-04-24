#ifndef AVION_H_INCLUDED
#define AVION_H_INCLUDED

#ifndef AVION_H
#define AVION_H



typedef struct {
    char nom[10];
    char acronyme[4];
}compagnie;
typedef struct {
    char id[7] ;
    int carburant ;
    int consomation ;
    char heure_decollage[4];
    compagnie* comp;
}avion;

typedef struct node {
    avion av;
    struct node* next;
} node;
typedef struct {
    node* premier ;
    node* dernier ;
    unsigned nbr ;
}list_av;

list_av* creer_list_av();
avion creer_avion(char[],int,int,char[],compagnie*);
compagnie *creer_compagnie(char*,char[]);
unsigned taille_list(list_av*);
void insere_tete(list_av*,avion);
void insere_queue(list_av*,avion);
void insere_pos(list_av*,avion,node*);
void supprimer_tete(list_av*);
void supprimer_queue(list_av*);
void supprimer_pos(list_av*,node*);
void free_list(list_av*);
void ajouter_nouveau_avion(list_av*,node*,unsigned);
void afficher_avion(node *,unsigned);
unsigned id_valide(char*);
void trier(list_av *);


#endif
#endif // AVION_H_INCLUDED
