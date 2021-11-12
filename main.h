#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include <ncurses.h>

typedef struct missile
{
	char direction;
	int posx;
	int posy;
	int vitesse;
	char* skin;
	char etat;
	int timing;
	
}MISSILE;

typedef struct etoile
{
	int posx;
	int posy;
	int vitesse;
	char* skin;
	char etat;
	int timing;
	
}ETOILE;

typedef struct joueur
{
	int posx;
	int posy;
	int vitesse;
	int blindage;
	int touches;
	int largeur;
	int length;
	char** skin;
	char etat;
	int timing;
	
}JOUEUR;

typedef struct ennemi
{
	char direction;
	int posx;
	int posy;
	int vitesse;
	int blindage;
	int touches;
	int largeur;
	int length;
	char** skin;
	char etat;
	int timing;
	
}ENNEMI;

typedef struct Liste
{
	ENNEMI contenu;
	struct Liste *next;
	
}Liste,*Ptliste;

struct printedList {
	void *data;
	struct printedList *prev;
	struct printedList *next;
	
};

//fonction qui retourne un caractere ascii extended en fonction d'un entier
char* printChar(int c);

//initialisation d'un tableau dynamique
int* init_tab(int longueur);

//initialisation d'un tableau dynamique 2D
char** matrice(int ligne,int colonne);

//stock un tableau d'entier a 2 digits a partir de valeurs contenu dans un fichier 
int* chargement(char* nom_fic,int length);

//transforme un tableau d'entier en tableau de caractere ascii extended
char** getSkin(int* skin, int length);

//affiche le tableau d'ascii avec le decalage correspondant en fonction de la largeur du vaisseau
void printSkin(char** skin, int length,int decalage,int larg);

//affichage du vaisseau avec ncurse
void printSkinCurse(char** skin, int length,int posx,int posy,int larg);

//supression des caracteres apres deplacement 
void supprSkinCurse(int posx, int posy, char dir, int longueur,int largeur);

int hitBox(ENNEMI E, MISSILE M);