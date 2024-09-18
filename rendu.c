#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rendu.h"


void initialiserListeEo(ParcEo *parc) 
{
    parc->listeEolienneCourante = (ListeEo *)malloc(sizeof(ListeEo));
    if (parc->listeEolienneCourante != NULL) {
        parc->listeEolienneCourante->teteeo = NULL;
    } else {
        printf("Erreur d'allocation mémoire pour listeEolienneCourante.\n");
        exit(EXIT_FAILURE);
    }
}


void vitesse(int duree, ListeParc *listeparc) 
{
    int a;
    int j;
    int i;
    int jo;
    int c;
    ParcEo *courant;
    int vitessecourante;
    ParcEo *parceo1 = (ParcEo *)malloc(sizeof(ParcEo)); 
    parceo1->jour = 0;
    parceo1->vitesse = 0;
    initialiserListeEo(parceo1);
    parceo1->suiv = NULL; 
    printf("la vitesse au jour %d est de niveau %d\n", parceo1->jour, parceo1->vitesse);
        
    listeparc->tetep = parceo1;
    listeparc->queue = parceo1;
    
    for(jo = 1; jo < duree; jo++) 
    {
        courant = listeparc->queue;
        vitessecourante = courant->vitesse;
        
        int b = 0;
        ParcEo *parceo = (ParcEo *)malloc(sizeof(ParcEo)); 
        parceo->jour = jo;
        initialiserListeEo(parceo);
        
        int liste[100]; //je cree une liste de 100 elements
        for (j = 0; j < 3; j++) // j represente les colonnes de ma matrice V
        {
            
            for (i = b; (i - b) < V[vitessecourante][j] * 100; i++) 
            {   
                liste[i] = j; // j'ajoute a la liste 100*proba de chaque possibilite pour la nouvelle vitesse
            }
            b += V[vitessecourante][j]*100;
        }
        a = rand() % 100; //je simule un aleatoire entre 0 et 99
        parceo->vitesse = liste[a]; // le nouvelle vitesse est definie ainsi
        
        printf("\nla vitesse au jour %d est de niveau %d\n", parceo->jour, parceo->vitesse);
        
        
        courant->suiv = parceo; 
        listeparc->queue = parceo;
        parceo->suiv=NULL; 
        
    }
}


void afficher(ListeParc *listeparc)
{	ParcEo *courant=listeparc->tetep;
	int jour;
	while(courant!=NULL)
		{
		jour=courant->jour;
		printf("%d\n",jour);
		courant=courant->suiv;
		}
}


void etat(int nombretot, ListeParc *listeparc)	
{
    int i;
    int j;
    int liste[100];
    int num;
    int jour;
    int aleatoire;
    int casse = 0;
    ParcEo *courant;
    ParcEo *stock;
    Eolienne *eolienne;
    Eolienne *courante;
    Eolienne *stockee;
    courant = listeparc->tetep;
    
    for (num = 0; num < nombretot; num++)
        {
            eolienne = (Eolienne *)malloc(sizeof(Eolienne));
            eolienne->suiv = courant->listeEolienneCourante->teteeo;
            courant->listeEolienneCourante->teteeo = eolienne;
            eolienne->numero = num;
            eolienne->etat = 1;
            eolienne->temps_de_reparation = 0;
        }
    courant=courant->suiv;
    
    while (courant != NULL)
    {
        jour = courant->jour;
        for (num = 0; num < nombretot; num++)
        {
            eolienne = (Eolienne *)malloc(sizeof(Eolienne));
            eolienne->suiv = courant->listeEolienneCourante->teteeo;
            courant->listeEolienneCourante->teteeo = eolienne;
            eolienne->numero = num;
            eolienne->etat = 1;
            eolienne->temps_de_reparation = 0;
        }
	reparation(listeparc,courant);
        if (courant->vitesse != 2)
        {
            printf("aucune eolienne ne tombera en panne au jour %d\n", jour);
        }
        else if (courant->vitesse == 2)
        {
            courante = courant->listeEolienneCourante->teteeo;

            while (courante != NULL)
            {
                if (courante->etat != 0)
                {
                    for (i = 0; i < 15; i++)
                    {
                        liste[i] = 0;
                    }
                    for (j = 15; j < 100; j++)
                    {
                        liste[j] = 1;
                    }
                    aleatoire = rand() % 100;

                    if (liste[aleatoire] == 0)
                    {
                        casse += 1;
                        Prix += 150000;
                        courante->temps_de_reparation = 3;
                        courante->etat = 0;
                        
                    }
                }
                courante = courante->suiv;
            }
            printf(" %d eolienne(s) tombe(nt) en panne au jour %d\n", casse, jour);
        }

        courant = courant->suiv;
        casse = 0;
    }
}

void reparation (ListeParc *listeparc,ParcEo *courant) 
{	 
	ParcEo *prec = listeparc->tetep;
	int jour=courant->jour;
	while(prec->jour!=jour-1)
		prec=prec->suiv;
	Eolienne *courante = courant->listeEolienneCourante->teteeo;
	Eolienne *precedente = prec->listeEolienneCourante->teteeo;
	

	    	while(courante!=NULL)
	    	{	if(courant->vitesse!=2)
		    		{
		    		if( (precedente->etat==0) && (precedente->temps_de_reparation==3) )
				    {courante->etat=0;
				    courante->temps_de_reparation=2;
				    }
				if((precedente->etat==0) && (precedente->temps_de_reparation==2))
				{	courante->etat=0;
				    	courante->temps_de_reparation=1;
				}
				if((precedente->etat==0) && (precedente->temps_de_reparation==1))
				{	courante->etat=1;
				    	courante->temps_de_reparation=0;
				}
	    	 		}
	    		else if(courant->vitesse==2)
			    { if((precedente->etat==0)&&(precedente->temps_de_reparation==3))
			    	{	courante->etat=0;
			    		courante->temps_de_reparation=3;
			    	}
			    if((precedente->etat==0)&&(precedente->temps_de_reparation==2))
			    	{	courante->etat=0;
			    		courante->temps_de_reparation=2;
			    	}
			    if((precedente->etat==0)&&(precedente->temps_de_reparation==1))
			    	{	courante->etat=0;
			    		courante->temps_de_reparation=1;
			   	}
	    		    }
		courante=courante->suiv;
		precedente=precedente->suiv; 
		}
	
}
void prod_duree_parc(ListeParc *listeparc)
{	int duree;	
	int nb_eoliennes;
	printf("Un parc de combien d'eoliennes souhaitez vous simuler?\n");
 	scanf("%d",&nb_eoliennes);
 	printf("Combien de jours voulez vous que dure cette simulation?\n");
 	scanf("%d",&duree);
	int cout=0;
 	float production=0;
 	vitesse(duree,listeparc); 
 	etat(nb_eoliennes,listeparc);
	ParcEo *courant=listeparc->tetep;
	ParcEo *courant2=listeparc->tetep->suiv;
	float production_min=productionjournaliere(courant2,listeparc);
	float production_max=productionjournaliere(courant,listeparc);
	while(courant2!=NULL)	
	{	cout+=coutjournalier(courant2,listeparc);
		courant2=courant2->suiv;
	}
	
	while(courant!=NULL)			
	{
		
		production+=productionjournaliere(courant,listeparc);
		if (productionjournaliere(courant,listeparc)<production_min)
			production_min=productionjournaliere(courant,listeparc);
		if (productionjournaliere(courant,listeparc)>production_max)
			production_max=productionjournaliere(courant,listeparc);
		courant=courant->suiv;
	}
	
	
	printf("la production du parc eolien de %d eoliennes sur %d jours est de %f MW\n.Le cout total engendre par les reparations s'eleve a %d euros \n",nb_eoliennes,duree,production,cout);
	printf("la production journaliere minimale est de %f MW\n",production_min);
	printf("la production journaliere maximale est de %f MW\n",production_max);
}



float productionjournaliere(ParcEo *courant,ListeParc *listeparc) 
{	Eolienne *courante=courant->listeEolienneCourante->teteeo;
	float prod=0;
	int i;
	for(i=0;i<3;i++)
	{
		if (courant->vitesse==i)
		{	
			while(courante!=NULL)
			{
				if (courante->etat!=0)
				{	
					prod+=Prod[i];
				}
				
			courante=courante->suiv;
			}
		}
	}
	return prod;
}

int coutjournalier(ParcEo *courant,ListeParc *listeparc)
{	
		ParcEo *prec = listeparc->tetep;
		int jour=courant->jour;
		while(prec->jour!=jour-1)
			{
			prec=prec->suiv;
			}
		Eolienne *courante=courant->listeEolienneCourante->teteeo;
		Eolienne *precedente = prec->listeEolienneCourante->teteeo;
		int cout=0;
		while(courante!=NULL)
		{	
			if ((courante->temps_de_reparation==3) &&(precedente->temps_de_reparation!=3))
				cout+=125000;
			courante=courante->suiv;
			precedente=precedente->suiv;	
		}
		return cout;
}




