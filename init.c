#include "affichage.c"

//fichier d'initialisation des differentes structures



JOUEUR init_joueur()
{
	JOUEUR J;
	
	J.length=40;
	J.posx = 30;
	J.posy = 19;
	J.vitesse = 5000;
	J.etat = 'I';
	J.timing=0;
	J.largeur=10;
	
	int* vaisseauA=chargement("vaisseauA.txt",J.length);
	J.skin=getSkin(vaisseauA,J.length);
	
	free(vaisseauA);
	return J;
}

ENNEMI init_ennemi(char D,char* nom_fic,int x, int y,int length,int largeur)
{
	ENNEMI E;
	E.length=length;
	E.posx = x;
	E.posy = y;
	E.direction = D;
	E.vitesse = 5000;
	E.etat = 'I';
	E.timing=0;
	E.largeur=largeur;
	
	int* vaisseau=chargement(nom_fic,E.length);
	E.skin=getSkin(vaisseau,E.length);
	
	free(vaisseau);
	return E;
}
MISSILE init_missile(char D,int x, int y,char etat)
{
	MISSILE M;
	M.posx = x;
	M.posy = y;
	M.direction = D;
	M.vitesse = 10000;
	M.skin="¤";
	M.etat = etat;
	M.timing=0;
	return M;
}

MISSILE* tabMissile(int length,JOUEUR j1)
{
	MISSILE* M=malloc(length*sizeof(MISSILE));
	int i=0;
	for(i=0;i<length;i++)
	{
		M[i]=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'I');
	}
	return M;
}

Ptliste initListe(ENNEMI X)
{
	
	Ptliste P =(Liste*)malloc(sizeof(Liste));
	P->contenu=X;
	P->next=NULL;
	return P;
}

