#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define TAILLE 190

typedef struct missile
{
	char direction;
	int posx;
	int posy;
	int vitesse;
	char skin[TAILLE];
	char etat;
	
}MISSILE;

typedef struct joueur
{
	int posx;
	int posy;
	int vitesse;
	int blindage;
	int touches;
	char skin[TAILLE];
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
	char skin[TAILLE];
	char etat;
	int timing;
	
}ENNEMI;

JOUEUR init_joueur(char* model)
{
	JOUEUR J;
	J.posx = 30;
	J.posy = 19;
	J.vitesse = 5000;
	strcpy(J.skin,model);
	J.etat = 'I';
	J.timing=0;
	return J;
}
ENNEMI init_ennemi(char D,char* model,int x, int y)
{
	ENNEMI E;
	E.posx = x;
	E.posy = y;
	E.direction = D;
	E.vitesse = 5000;
	strcpy(E.skin,model);
	E.etat = 'I';
	E.timing=0;
	return E;
}
MISSILE init_missile(char D,char* model,int x, int y)
{
	MISSILE M;
	M.posx = x;
	M.posy = y;
	M.direction = D;
	M.vitesse = 5000;
	strcpy(M.skin,model);
	M.etat = 'V';
	return M;
}

char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) 
	{
		ungetc(c, stdin); result = getchar();
	}
return result;
}

void affich(char* nom_fic,int decalage)
{
	char c;
	int i;
	FILE* fic=fopen(nom_fic,"r");
	while((c=fgetc(fic))!=EOF)
	{
		if(c=='\n')
		{
			printf("%c",c);
			for(i=0;i<decalage-1;i++)
			{
				printf(" ");
			}
		}
		else
		{
			printf("%c",c);
		}
	}
	printf("\n");
}

void chargement(char* nom_fic,int nb,int skin[nb])
{
	char str[2];
	char c;
	int i,j;
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
			}
			else
			{
				str[i]=c;
				i++;
			}
		}
	}
}
void affichage_vaisseau(char* nom_fic, int posx, int posy)
{
	printf("\033[%d;%dH",posx,posy);
	affich(nom_fic,posy);
}
void deplacement(char c,int* posx, int* posy, int longueur_vaisseau, int largeur_vaisseau,int* posxM, int* posyM,char* etat)
{
	switch(c)
	{
		case 'z':
			*posx=*posx-1;
			system("clear");
			if(*etat=='I')
			{
				*posxM=*posx-1;
				*posyM=(5/2)+*posy;
			}
			else
			{
				*posxM=*posxM-1;
				printf("\033[%d;%dH║",*posxM,*posyM);
				if(*posxM<=1)
				{
					*etat='I';
				}
			}
			
			affichage_vaisseau("vaisseau1.txt",*posx-1,*posy);
			break;
		case 'd':
			*posy=*posy+1;
			system("clear");
			if(*etat=='I')
			{
				*posxM=*posx-1;
				*posyM=(5/2)+*posy;
			}
			else
			{
				*posxM=*posxM-1;
				printf("\033[%d;%dH║",*posxM,*posyM);
				if(*posxM<=1)
				{
					*etat='I';
				}
					
			}
			
			affichage_vaisseau("vaisseau1.txt",*posx,*posy);
			break;
		case 's':
			*posx=*posx+1;
			system("clear");
			if(*etat=='I')
			{
				*posxM=*posx-1;
				*posyM=(5/2)+*posy;
			}
			else
			{
				*posxM=*posxM-1;
				printf("\033[%d;%dH║",*posxM,*posyM);
				if(*posxM<=1)
				{
					*etat='I';
				}
			}
			
			affichage_vaisseau("vaisseau1.txt",*posx,*posy);
			break;
		case 'q':
			*posy=*posy-1;
			system("clear");
			if(*etat=='I')
			{
				*posxM=*posx-1;
				*posyM=(5/2)+*posy;
			}
			else
			{
				*posxM=*posxM-1;
				printf("\033[%d;%dH║",*posxM,*posyM);
				if(*posxM<=1)
				{
					*etat='I';
				}
			}
			
			affichage_vaisseau("vaisseau1.txt",*posx,*posy);
			break;
		
		case 'p':
			if(*etat=='I')
			{	
				*etat='V';
				printf("\033[%d;%dH║",*posxM,*posyM);
			}
			break;
	}
}
int main()
{
		system("clear");
		//affich("vaisseau1.txt",0);
		printf("\n");
		int timing=0;
		int vitesse=150000;
		int posy=5;
		int posx=5;
		
		char c;
		int posxM=posx-1;
		int posyM=(5/2)+posy;
		char etat='I';
		
		affichage_vaisseau("vaisseau1.txt",posx,posy);
		
		while((c=key_pressed())!='x')
		{
			timing = (timing+1)%vitesse;
			
			deplacement(c,&posx,&posy,3,5,&posxM,&posyM,&etat);

		}
		
		return 0;
}
