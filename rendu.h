#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int Prix=0;

double V[3][3]={{0.2,0.73,0.07},{0.11,0.74,0.15},{0.04,0.61,0.35}};
float Prod[3]={0,0.4,0.65};





// LES STRUCTURES : 

typedef struct Eo
{ 
	int etat;
	int numero;
	int temps_de_reparation;
	struct Eo *suiv;
}Eolienne; 

typedef struct ListeEo
{
	Eolienne *teteeo;
}ListeEo;

typedef struct parc
{	int jour;
	int nombretot;
	int vitesse;
	ListeEo *listeEolienneCourante;
	struct parc *suiv;
} ParcEo; 

typedef struct ListeParc
{
	ParcEo *queue;
	ParcEo *tetep;
}ListeParc;



// LES PROTOTYPES DES FONCTIONS
void vitesse(int duree, ListeParc *listeparc);
void etat(int nombretot,ListeParc *listeparc);
void reparation (ListeParc *listeparc,ParcEo *parceo);	
void prod_duree_parc(ListeParc *listeparc);
float productionjournaliere(ParcEo *courant,ListeParc *listeparc);
int coutjournalier(ParcEo *courant,ListeParc *listeparc);


int main()
{
ListeParc listeparc;
listeparc.tetep=NULL;
listeparc.queue=NULL;
srand(time(NULL));
prod_duree_parc(&listeparc);
return 0;
}

