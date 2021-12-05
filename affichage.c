#include "struct.h"

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
			return("");
			break;
		case 27:
		    return("\u2510");//┐
			break;
		case 28:
			return("\u250C");//┌
			break;
		case 29:
			return("\u2550");//═
			break;
		case 30:
			return("\u2502");//│
			break;
		case 31:
			return("\u2665");//♥
			break;
		case 32:
			return("\U0001F525");//🔥
			break;
		case 33://MISSILE
			return("\U00002B55");//⦷
			break;
		case 34://ETOILE
			return("\U00002606");//☆
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
	int j=0;
	int xLimit=4;
	int posInit=posy;
	int DecX = posx-xLimit;
	move(posx - 1, posy - 1);
	if(DecX<0)
	{
		for(i=0;i<length;i++)
		{
			if(i%larg==0&&i!=0)
			{
				posx++;
				j++;
				posy=posInit;
				move(posx - 1, posy - 1);
			}
			if(j>=-DecX)
			{
				printw("%s",skin[i]);
			}
		}
	}
	else
	{
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
//COLLISION ENTRE VAISSEAU ET MISSILE
int hitBox(VAISSEAU E, MISSILE M)
{
	int longueur=E.length/E.largeur;
	if((M.posx>=E.posx&&M.posx<=E.posx+longueur-2)&&(M.posy>=E.posy-1&&M.posy<=E.posy+E.largeur-3))
	{
		return 1;
	}
	return 0;
}

//COLLISION ENTRE 2 MISSILE
int collisionMissile(MISSILE M,MISSILE* tabM,int nbMissile)
{
	int i;
	for(i=0;i<nbMissile;i++)
	{
		if(M.posx==tabM[i].posx&&M.posy==tabM[i].posy&&tabM[i].etat=='V')
		{
			tabM[i].etat='I';
			return 1;
		}
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

void printList(Ptliste L)
{
	//COULEURS
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_BLUE,COLOR_BLACK);
	init_pair(3,COLOR_RED,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	
	//PARCOURS LISTE
	while(L->next!=NULL)
	{
		//AFFICHAGE PAR COULEUR
		if(L->contenu.points>45)
			attron(COLOR_PAIR(1));
		else if(L->contenu.points>30)
			attron(COLOR_PAIR(2));
		else if(L->contenu.points>10)
			attron(COLOR_PAIR(3));
		else
			attron(COLOR_PAIR(4));
		
		printSkinCurse(L->contenu.skin,L->contenu.length,L->contenu.posx,L->contenu.posy,L->contenu.largeur);
		L=L->next;
		attroff(COLOR_PAIR(1));
		attroff(COLOR_PAIR(2));
		attroff(COLOR_PAIR(3));
		attroff(COLOR_PAIR(4));
	}
}
char deplacementEnnemis(Ptliste init,char dir)
{
	Ptliste L=init;
	int yLimit1 =	2;
	int yLimit2 =	120;
	int x	= 0;
	int y	= 0;
	int xMin=L->contenu.posx;
	int xMax=L->contenu.posx;
	int yMin=L->contenu.posy;
	int yMax=L->contenu.posy;
	
	//PARCOURS DE LISTE POUR XMAX XMIN YMAX YMIN
	while(L->next!=NULL)
	{
		if(xMin>L->contenu.posx)
		{
			xMin=L->contenu.posx;
		}
		if(xMax<L->contenu.posx)
		{
			xMax=L->contenu.posx;
		}
		if(yMin>L->contenu.posy)
		{
			yMin=L->contenu.posy;
		}
		if(yMax<L->contenu.posy)
		{
			yMax=L->contenu.posy;
		}
		L=L->next;
	}
	//SI POSITION DES ENNEMIS EST PAS VISIBLE SUR L'ECRAN
	if(xMin<4)
	{
		x++;
	}
	//SI LES ENNEMIS VONT VERS LA DROITE
	if(dir=='E')
	{
		if(yMax<yLimit2)
		{
			y++;
		}
		else
		{
			x++;
			dir = 'O';
		}
	}
	//SI LES ENNEMIS VONT VERS LA GAUCHE
	if(dir=='O')
	{
		if(yMin<=yLimit1)
		{
			x++;
			dir = 'E';
		}
		else
		{
			y--;
		}
	}
	L=init;
	//MAJ DES POSITION ENNEMIS
	while(L->next!=NULL)
	{
		L->contenu.posy+=y;
		L->contenu.posx+=x;
		L=L->next;
	}
	
	
	return dir;
	
}


//SUPPRESSION ELEMENT DANS UNE LISTE 
Ptliste supprElt(Ptliste init,int n,Ptliste next)
{
	Ptliste L=init;
	
	while(L->next!=NULL)
	{
		if(n<0)
		{
			free(L);
			return init->next;
		}
		if(n==0)
		{
			free(L->next);
			L->next=next;
			return init;
		}
		n--;
		L=L->next;
	}
	return init;
}


void affichage_score(int choixMode,int score, int vie,int bestScore)
{
		//Ligne 0 Mode
		int i;
		char* mode;
		mvprintw(0,0,"%s",printChar(10));
		for(i = 0;i<18;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(5));
		for(i = 0;i<18;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(11));
		
		//Ligne 1 MODE
		if(choixMode==1)
			mode="Facile";
		else if(choixMode==2)
			mode="Difficile";
		else
			mode="Progressif";
		mvprintw(1,0,"%s",printChar(14));
		printw("MODE : %s",mode);
		mvprintw(1,19,"%s",printChar(14));
		printw("VIE : ");
		for(i=0;i<vie;i++)
		{
			printw("%s ",printChar(31));
		}
		mvprintw(1,38,"%s",printChar(14));
		
		//Ligne 2 MODE
		mvprintw(2,0,"%s",printChar(15));
		for(i = 0;i<18;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(6));
		for(i = 0;i<18;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(16));
		
		//Ligne 0 Score
		mvprintw(0,70,"%s",printChar(10));
		for(i = 0;i<25;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(5));
		for(i = 0;i<30;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(11));
		
		//Ligne 1 Score
		mvprintw(1,70,"%s",printChar(14));
		printw("Score : %d",score);
		mvprintw(1,96,"%s",printChar(14));
		printw("Meilleur Score : %d",bestScore);
		mvprintw(1,127,"%s",printChar(14));
		
		//Ligne 2 Score
		mvprintw(2,70,"%s",printChar(15));
		for(i = 0;i<25;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(6));
		for(i = 0;i<30;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(16));
	
}

void affich_GameOver(int bestScore,int score)
{
	int i;
	mvprintw(40,40,"%s",printChar(10));
	for(i = 0;i<40;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(11));
		
		//LIGNE 1
		mvprintw(41,40,"%s",printChar(14));
		printw("               Game Over                ");
		mvprintw(41,81,"%s",printChar(14));
		//LIGNE 2
		mvprintw(42,40,"%s",printChar(14));
		printw("                                        ");
		mvprintw(42,81,"%s",printChar(14));
		if(score>bestScore)
		{
			mvprintw(43,40,"%s",printChar(14));
			printw("        NOUVEAU MEILLEUR SCORE !!!       ");
			mvprintw(43,81,"%s",printChar(14));
			mvprintw(44,40,"%s",printChar(14));
			printw("                   %d                    ",score);
			mvprintw(44,81,"%s",printChar(14));
			
			mvprintw(45,40,"%s",printChar(14));
			printw("                                         ");
			mvprintw(45,81,"%s",printChar(14));
		
			mvprintw(46,40,"%s",printChar(14));
			printw("Appuyez sur 'n' pour relancer une partie");
			mvprintw(46,81,"%s",printChar(14));
			//LIGNE 4
			mvprintw(47,40,"%s",printChar(14));
			printw("                                        ");
			mvprintw(47,81,"%s",printChar(14));
			//LIGNE 5
			mvprintw(48,40,"%s",printChar(14));
			printw("Appuyez sur 'm' pour revenir au menu    ");
			mvprintw(48,81,"%s",printChar(14));
			//LIGNE 6
			mvprintw(49,40,"%s",printChar(15));
		}
		else
		{
			//LIGN3 3
			mvprintw(43,40,"%s",printChar(14));
			printw("Appuyez sur 'n' pour relancer une partie");
			mvprintw(43,81,"%s",printChar(14));
			//LIGNE 4
			mvprintw(44,40,"%s",printChar(14));
			printw("                                        ");
			mvprintw(44,81,"%s",printChar(14));
			//LIGNE 5
			mvprintw(45,40,"%s",printChar(14));
			printw("Appuyez sur 'm' pour revenir au menu    ");
			mvprintw(45,81,"%s",printChar(14));
			//LIGNE 6
			mvprintw(46,40,"%s",printChar(15));
		}
		for(i = 0;i<40;i++)
		{
			printw("%s",printChar(29));
		}
		printw("%s",printChar(16));
	
}