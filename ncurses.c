#include "init.c"

int main(void)
{
	//INIT NCURSES
	setlocale(LC_ALL, "");
	initscr();cbreak();noecho(),nodelay(stdscr,TRUE);
	curs_set(0);
	start_color();
	srand(time(NULL));
	
	//INITIALISATION COULEURS
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_BLUE,COLOR_BLACK);
	init_pair(3,COLOR_RED,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_CYAN,COLOR_BLACK);
	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
	
	//DEFINITION DES VARIABLES
	char c;
	int timing			= 0;
	int timingEnnemis	= 0;
	int timingMissiles	= 0;
	int i				= 0;
	char dirEnnemis		= 'E';
	int score			= 0;
	int choixMode		= 3;
	FILE* fic;
	char* ficScore	= "score.txt";
	int bestScore;
	fic=fopen(ficScore,"r");
	fscanf(fic,"%d",&bestScore);
	fclose(fic);
	
	int vitesse		= 35000;
	int nbMissile	= 25;
	int nbMissileE;
	int nbEtoile	= 55;
	if(choixMode==2)
	{
		nbMissileE=10;
		vitesse=vitesse*0.90;
	}
	else
		nbMissileE=5;
	
	
	
	
	VAISSEAU j1			= init_joueur();
	Ptliste ennemisList	= initEnnemiList1();
	Ptliste ennemisList2;
	MISSILE* tabM 		= tabMissile(nbMissile,j1);
	MISSILE* tabMEnnemi	= tabMissile(nbMissile,ennemisList->contenu);
	ETOILE* tabEt 		= tabEtoile(nbEtoile);
	
	affichage_Etoile(tabEt,nbEtoile);
	printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
	move(LINES - 1, COLS - 1);
	
	
	while((c=getch()))
	{
		//DIRECTION DROITE
		if((c=='q'||c==KEY_LEFT)&&j1.posy>1)
		{
			j1.posy--;
		}
		//DIRECTION GAUCHE
		if((c=='d'||c==KEY_RIGHT)&&j1.posy<120)
		{
			j1.posy++;
		}
		//RESTART
		if(c=='n'&&(j1.blindage<=0||ennemisList==NULL))
		{
			if(score>bestScore)
			{
				fic=fopen(ficScore,"w+");
				fprintf(fic,"%d",score);
				bestScore=score;
				fclose(fic);
			}
			score = 0;
			
			j1= init_joueur();
			ennemisList2=initEnnemiList1();
			ennemisList2=initEnnemiList1();
			ennemisList=ennemisList2;
			tabMEnnemi=tabMissile(nbMissile,ennemisList->contenu);
			
		}
		
		
		
		
		//TIR DE MISSILE
		if(c=='p'&&tabM[i].etat!='V'&&j1.blindage>0)
		{
			tabM[i]=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'V');
			if(i<=nbMissile-2)
				i++;
			else
				i=0;
		}
		
		
		
		//AFFICHAGE//
		
		timing=(timing+1)%vitesse;
		if(timing==100&&ennemisList!=NULL)
			
		{
			timingEnnemis=(timingEnnemis+1)%3;
			if(timingEnnemis==2 && ennemisList!=NULL)
			{
				dirEnnemis = deplacementEnnemis(ennemisList,dirEnnemis);
			}
			timingMissiles=(timingMissiles+1)%21;
			//TIR MISSILE ENNEMIS
			if(timingMissiles==20&&ennemisList->contenu.posx>7)
				tabMEnnemi=missile_ennemi(ennemisList,tabMEnnemi,nbMissileE);
			
			erase();
			
			
		
		
		//AFFICHAGE ETOILES
			for(int j=0;j<nbEtoile;j++)
			{
				tabEt[j].posx++;
				mvprintw(tabEt[j].posx,tabEt[j].posy,tabEt[j].skin);
			
				if(tabEt[j].posx>=80)
				{
					tabEt[j].posx = 1;
					tabEt[j].posy = 1+(rand()%120);
				}
			}
		
		//AFFICHAGE JOUEUR
			attron(COLOR_PAIR(5));
			if(j1.etat=='V')
				printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
			if(j1.etat=='E'&&j1.blindage>1)
				printSkinCurse(j1.skin2,j1.length,j1.posx,j1.posy,j1.largeur);
			else if(j1.etat=='E'&&j1.blindage==1)
				printSkinCurse(j1.skin3,j1.length,j1.posx,j1.posy,j1.largeur);
			attroff(COLOR_PAIR(5));
			
		//AFFICHAGE ENNEMIS
			if(ennemisList!=NULL)
				printList(ennemisList);
			
		//AFFICHAGE MISSILES
			for(int j=0;j<nbMissile;j++)
			{
				if(tabM[j].etat=='V')
				{
					tabM[j].posx--;
					attron(COLOR_PAIR(5));
					mvprintw(tabM[j].posx,tabM[j].posy,"%s",tabM[j].skin);
					attroff(COLOR_PAIR(5));
					
					if(ennemisList!=NULL)
					{
						ennemisList=damage(ennemisList,&tabM[j],&score);
						
					}
						
					if(tabM[j].posx==0)
					{
						tabM[j].etat='I';
						mvprintw(tabM[j].posx,tabM[j].posy," ");
					}
				}
			}
			//MISSILES ENNEMIS
			for(int j=0;j<nbMissileE;j++)
			{
				if(tabMEnnemi[j].etat=='V')
				{
					tabMEnnemi[j].posx++;
					attron(COLOR_PAIR(3));
					mvprintw(tabMEnnemi[j].posx,tabMEnnemi[j].posy,"%s",tabMEnnemi[j].skin);
					attroff(COLOR_PAIR(3));
					
					if(collisionMissile(tabMEnnemi[j],tabM,nbMissile)==1)
					{
						tabMEnnemi[j].etat='I';
						score+=5;
					}
					if(hitBox(j1,tabMEnnemi[j])==1&&j1.blindage>0)
					{
						j1.blindage--;
						j1.etat='E';
						tabMEnnemi[j].etat='I';
					}
					if(j1.blindage==0)
					{
						j1.etat='D';
					}
						
					if(tabMEnnemi[j].posx>=80)
					{
						tabMEnnemi[j].etat='I';
						mvprintw(tabMEnnemi[j].posx,tabMEnnemi[j].posy," ");
					}
				}
			}
			//AFFICHAGE ENTETE
			attron(COLOR_PAIR(1));
			affichage_score(choixMode,score,j1.blindage,bestScore);
			if(((j1.blindage<=0||ennemisList==NULL)&&(choixMode==1||choixMode==2))||(j1.blindage<=0&&choixMode==3))
				affich_GameOver(bestScore,score);
			attroff(COLOR_PAIR(1));
			
			move(LINES - 1, COLS - 1);
		}
		//SI MODE PROGRESSIF
		if(timing==100&&ennemisList==NULL&&choixMode==3)
		{
			ennemisList2=initEnnemiList1();
			ennemisList2=initEnnemiList1();
			ennemisList=ennemisList2;
			tabMEnnemi=tabMissile(nbMissile,ennemisList->contenu);
			vitesse=vitesse*0.95;
			nbMissileE+=4;
		}
		
	}
	
	getch();
	endwin();
	
	return 0;
}