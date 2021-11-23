#include "init.c"

int main(void)
{
	setlocale(LC_ALL, "");
	initscr();cbreak();noecho(),nodelay(stdscr,TRUE);
	curs_set(0);
	char c;
	
	int timing		= 0;
	int timing2		= 0;
	int vitesse		= 5000;
	int i			= 0;
	int nbMissile	= 25;
	int nbEtoile	= 55;
	char dirEnnemis	= 'E';
	JOUEUR j1= init_joueur();
	// ENNEMI e1= init_ennemi('S',"vaisseauB2.txt",10,10,18,6);
	// ENNEMI e2= init_ennemi('S',"vaisseauB.txt",10,15,18,6);
	// ENNEMI e3= init_ennemi('S',"vaisseauB2.txt",10,20,18,6);
	// ENNEMI e3= init_ennemi('S',"vaisseauE.txt",1,2,21,7);
	Ptliste ennemisList=initEnnemiList1();
	MISSILE* tabM =tabMissile(nbMissile,j1);
	ETOILE* tabEt =tabEtoile(nbEtoile);
	affichage_Etoile(tabEt,nbEtoile);
	printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
	// printSkinCurse(e3.skin,e3.length,e3.posx,e3.posy,e3.largeur);
	move(LINES - 1, COLS - 1);
	
	
	while((c=getch())!=27)
	{
		
		if((c=='s'/*||c==KEY_DOWN*/)&&j1.posx<37)
		{
			j1.posx++;
		}
		if((c=='z'/*||c==KEY_UP*/)&&j1.posx>1)
		{
			j1.posx--;
		}
		if((c=='q'/*||c==KEY_LEFT*/)&&j1.posy>1)
		{
			j1.posy--;
		}
		if((c=='d'/*||c==KEY_RIGHT*/)&&j1.posy<60)
		{
			j1.posy++;
		}
		
		
		
		
		
		//TIR DE MISSILE
		if(c=='p'&&tabM[i].etat!='V')
		{
			tabM[i]=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'V');
			if(i<=nbMissile-2)
				i++;
			else
				i=0;
		}
		
		timing=(timing+1)%vitesse;
		
		//AFFICHAGE//
		if(timing==100)
		{
			timing2=(timing2+1)%3;
		if(timing2==2)
			{
				dirEnnemis = deplacementEnnemis(ennemisList,dirEnnemis);
			}
			
			
			erase();
			// mvprintw(LINES - 3, COLS - 10, "%d",timing2);
		//AFFICHAGE ETOILE
		
			for(int j=0;j<nbEtoile;j++)
			{
				tabEt[j].posx++;
				mvprintw(tabEt[j].posx,tabEt[j].posy,"*");
			
				if(tabEt[j].posx>=60)
				{
					tabEt[j].posx = 1;
					tabEt[j].posy = 1+(rand()%59);
				}
			}
		
		//AFFICHAGE JOUEUR
			printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
		//AFFICHAGE ENNEMIS
			printList(ennemisList);
			
		//AFFICHAGE MISSILES
		
			for(int j=0;j<nbMissile;j++)
			{
				if(tabM[j].etat=='V')
				{
					tabM[j].posx--;
					mvprintw(tabM[j].posx,tabM[j].posy,"%s",tabM[j].skin);
				
					ennemisList=damage(ennemisList,&tabM[j]);
					
					if(tabM[j].posx==0)
					{
						tabM[j].etat='I';
						mvprintw(tabM[j].posx,tabM[j].posy," ");
					}
				}
			}
			move(LINES - 1, COLS - 1);
		}
		
		
		
		
	}
	
	getch();
	endwin();
	
	return 0;
}