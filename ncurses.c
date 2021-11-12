#include "init.c"

int main(void)
{
	setlocale(LC_ALL, "");
	initscr();cbreak();noecho(),nodelay(stdscr,TRUE);
	curs_set(0);
	char c;
	//int posxM=posx-1;
	//int posyM=(5/2)+posy;
	
	int timing=0;
	int vitesse=100000;
	int i=0;
	int nbMissile=25;
	int nbEtoile=55;
	JOUEUR j1= init_joueur();
	// ENNEMI e1= init_ennemi('S',"vaisseauB2.txt",10,10,18,6);
	// ENNEMI e2= init_ennemi('S',"vaisseauB.txt",10,15,18,6);
	// ENNEMI e3= init_ennemi('S',"vaisseauB2.txt",10,20,18,6);
	ENNEMI e3= init_ennemi('S',"vaisseauE.txt",1,20,21,7);
	// MISSILE m1=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'I');
	MISSILE* tabM =tabMissile(nbMissile,j1);
	ETOILE* tabEt =tabEtoile(nbEtoile);
	affichage_Etoile(tabEt,nbEtoile);
	printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
	// printSkinCurse(e1.skin,e1.length,e1.posx,e1.posy,e1.largeur);
	// printSkinCurse(e2.skin,e2.length,e2.posx,e2.posy,e2.largeur);
	printSkinCurse(e3.skin,e3.length,e3.posx,e3.posy,e3.largeur);
	move(LINES - 1, COLS - 1);
	
	
	while((c=getch())!=27)
	{
		
		if((c=='s'/*||c==KEY_DOWN*/)&&j1.posx<37)
		{
			j1.posx++;
			/*
			erase();
			
			printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
			if(e3.etat=='V')
				printSkinCurse(e3.skin,e3.length,e3.posx,e3.posy,e3.largeur);
			tabM[1].timing = (tabM[1].timing+1)%tabM[1].vitesse;
			*/
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
		if(c=='k')
		{
			e3.posx++;
		}
		if(c=='i')
		{
			e3.posx--;
		}
		
		
		
		
		timing=(timing+1)%vitesse;
		if(c=='p'/*&&timing>=20000*/&&tabM[i].etat!='V')
		{
			tabM[i].timing=0;
			timing=0;
			tabM[i]=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'V');
			if(i<=nbMissile-2)
				i++;
			else
				i=0;
			
			/*
			erase();
			
			printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
		
			if(e3.etat=='V')
				printSkinCurse(e3.skin,e3.length,e3.posx,e3.posy,e3.largeur);
			tabM[1].timing = (tabM[1].timing+1)%tabM[1].vitesse;
			*/
		}
		//AFFICHAGE//
		
		
		erase();
		// refresh();
		//AFFICHAGE ETOILE
		tabEt[1].timing = (tabEt[1].timing+1)%tabEt[1].vitesse;
		for(int j=0;j<nbEtoile;j++)
		{
			if(tabEt[1].timing==100)
			{
				mvprintw(tabEt[j].posx,tabEt[j].posy," ");
				tabEt[j].posx++;
			}
			mvprintw(tabEt[j].posx,tabEt[j].posy,"*");
			
			if(tabEt[j].posx>=60)
			{
				tabEt[j].posx = 1;
				tabEt[j].posy = 1+(rand()%59);
			}
		}
		
		//AFFICHAGE JOUEUR
		printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
		
		//AFFICHAGE RNNEMI
		if(e3.etat=='V')
			printSkinCurse(e3.skin,e3.length,e3.posx,e3.posy,e3.largeur);
		tabM[1].timing = (tabM[1].timing+1)%tabM[1].vitesse;
		
		//AFFICHAGE MISSILE
		for(int j=0;j<nbMissile;j++)
		{
			if(tabM[j].etat=='V')
			{
				if(tabM[1].timing==100)
				{
					mvprintw(tabM[j].posx,tabM[j].posy," ");
					tabM[j].posx--;
				}
				mvprintw(tabM[j].posx,tabM[j].posy,"%s",tabM[j].skin);
				
				
				if(hitBox(e3,tabM[j])&&e3.etat=='V')
				{
					if(e3.blindage!=0)
					{
						e3.blindage--;
						tabM[j].etat='I';
						mvprintw(tabM[j].posx,tabM[j].posy," ");
					}
					if(e3.blindage==0)
					{
						e3.etat='I';
						// erase();
					}
				}
				if(tabM[j].posx==0)
				{
					tabM[j].etat='I';
					mvprintw(tabM[j].posx,tabM[j].posy," ");
				}
			}
		}
		
		
		
		
		move(LINES - 1, COLS - 1);
		
	}
	
	getch();
	endwin();
	
	return 0;
}