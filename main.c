#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
//#include <curses.h>

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
	char skin[TAILLE];
	char etat;
	int timing;
	
}ENNEMI;
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
void affichage_vaisseau(char* nom_fic, int posx, int posy)
{
	printf("\033[%d;%dH",posx,posy);
	affich(nom_fic,posy);
}
void deplacement(int* posx, int* posy, int longueur_vaisseau, int largeur_vaisseau,int* posxM, int* posyM,char* etat)
{
	// int i;
	char c=key_pressed();
	switch(c)
	{
		case 'z':
			/*
			for(i=0;i<largeur_vaisseau;i++)
			{
				printf("\033[%d;%dH ",*posx+longueur_vaisseau-2,*posy+i);
			}
			*/
			
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
			/*
			for(i=0;i<longueur_vaisseau;i++)
			{
				printf("\033[%d;%dH ",*posx+i,*posy);
			}
			*/
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
			/*
			for(i=0;i<largeur_vaisseau;i++)
			{
				printf("\033[%d;%dH ",*posx,*posy+i);
			}
			*/
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
			/*
			for(i=0;i<longueur_vaisseau;i++)
			{
				printf("\033[%d;%dH ",*posx+i,*posy+largeur_vaisseau-1);
			}
			*/
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
		
		int posxM=posx-1;
		int posyM=(5/2)+posy;
		char etat='I';
		
		affichage_vaisseau("vaisseau1.txt",posx,posy);
		
		while((key_pressed())!='x')
		{
			timing = (timing+1)%vitesse;
			
			deplacement(&posx,&posy,3,5,&posxM,&posyM,&etat);
			/*
			if(timing==1000)
			{
				//posy++;
				//posx++;
				
				//printf("\033[3m");
				
				
				if(posy>1)
				{
					printf("\033[%d;%dH ",posx,posy-1);
				}
				if(posx>1)
				{
					printf("\033[%d;%dH      ",posx-1,posy-1);
				}
				//printf("\033[00m");
			}
			*/
		}
		
		return 0;
}
