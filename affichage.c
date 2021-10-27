#include "main.h"

//fonction qui retourne un caractere ascii extended en fonction d'un entier
char* printChar(int c)
{
	switch(c)
	{
		case 0:
			return(" ");
			break;
		case 1:
			return("\u2560");//╠
			break;
		case 2:
			return("\u2563");//╣
			break;
		case 3:
			return("\u252C");//┬
			break;
		case 4:
			return("\u2534");//┴
			break;
		case 5:
			return("\u2566");//╦
			break;
		case 6:
			return("\u2569");//╩
			break;
		case 7:
			return("\u2563");//╣
			break;
		case 8:
			return("\u256C");//╬
			break;
		case 9:
			return("\u253C");//┼
			break;
		case 10:
			return("\u2554");//╔
			break;
		case 11:
			return("\u2557");//╗
			break;
		case 12:
			return("\u2524");//┤
			break;
		case 13:
			return("\u251C");//├
			break;
		case 14:
			return("\u2551");//║
			break;
		case 15:
			return("\u255A");//╚
			break;
		case 16:
			return("\u255D");//╝
			break;
		case 17:
			return("\u2514");//└
			break;
		case 18:
			return("\u2518");//┘
			break;
		case 19:
			return("¯");
			break;
		case 20:
			return("_");
			break;
		case 21:
			return("V");
			break;
		case 22:
			return("^");
			break;
		case 23:
			return("O");
			break;
		case 24:
			return("\u2584");//▄
			break;
		case 25:
			return("\u2500");//─
			break;
		case 26:
			return("\n");
			break;
		default:
			return("");
	}
}
//initialisation d'un tableau dynamique
int* init_tab(int longueur)
{
	int* tab=malloc(longueur*sizeof(int));
	return(tab);
}
//initialisation d'un tableau dynamique 2D
char** matrice(int ligne,int colonne)
{
	int i;
	char** tab=malloc(ligne*sizeof(char*));
	for (i = 0; i < ligne; i++)
	{
		tab[i]=malloc(colonne*sizeof(char));
	}
	return(tab);
}
//stock un tableau d'entier a 2 digits a partir de valeurs contenu dans un fichier 
int* chargement(char* nom_fic,int length)
{
	int* skin=init_tab(length);
	char str[2]={0,0};
	char c;
	int i=0;
	int j=0;
	
	FILE* fic=fopen(nom_fic,"r");
	while((c=fgetc(fic))!=EOF)
	{
		if(c!='\n')
		{
			if(c==' ')
			{
				skin[j]=atoi(str);
				i=0;
				j++;
				str[1]=0;
				str[0]=0;
			}
			else
			{
				str[i]=c;
				
				i++;
			}
		}
	}
	fclose(fic);
	return skin;
}

//transforme un tableau d'entier en tableau de caractere ascii extended
char** getSkin(int* skin, int length)
{
	char** affich=matrice(length,6);
	int i;
	for(i=0;i<length;i++)
	{
		affich[i]=printChar(skin[i]);
	}
	return affich;
	
}
//affiche le tableau d'ascii avec le decalage correspondant en fonction de la largeur du vaisseau
void printSkin(char** skin, int length,int decalage,int larg)
{
	int i,j;
	for(i=0;i<length;i++)
	{
		if(i%larg==0&&i!=0)
		{
			for(j=0;j<decalage;j++)
			{
				printf(" ");
			}
		}
		printf("%s",skin[i]);
	}
}
//affichage du vaisseau avec ncurse
void printSkinCurse(char** skin, int length,int posx,int posy,int larg)
{
	int i;
	int posInit=posy;
	move(posx - 1, posy - 1);
	for(i=0;i<length;i++)
	{
		if(i%larg==0&&i!=0)
		{
			posx++;
			posy=posInit;
			move(posx - 1, posy - 1);
		}
		printw("%s",skin[i]);
	}
	posx++;
}
//supression des caracteres apres deplacement 
void supprSkinCurse(int posx, int posy, char dir, int longueur,int largeur)
{
	int i=0;
	if(dir=='s')
	{
		move(posx - 1, posy - 1);
		while(i<largeur)
		{
			printw(" ");
			i++;
		}
	}
	else if(dir=='z')
	{
		move(posx+longueur-1 - 1, posy - 1);
		while(i<largeur)
		{
			printw(" ");
			i++;
		}
	}
	else if(dir=='q')
	{
		move(posx+i - 1, posy+largeur-2 - 1);
		while(i<longueur)
		{
			printw(" ");
			i++;
			move(posx+i - 1, posy+largeur-2 - 1);
		}
	}
	else if(dir=='d')
	{
		move(posx - 1, posy - 1);
		while(i<longueur)
		{
			printw(" ");
			i++;
			move(posx+i - 1, posy - 1);
		}
	}
	
}

int hitBox(ENNEMI E, MISSILE M)
{
	int longueur=E.length/E.largeur;
	if((M.posx>=E.posx&&M.posx<=E.posx+longueur-2)&&(M.posy>=E.posy-1&&M.posy<=E.posy+E.largeur-3))
	{
		return 1;
	}
	return 0;
}

void affichage_Etoile(ETOILE* E,int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		mvprintw(E[i].posx,E[i].posy,"*");
	}
}