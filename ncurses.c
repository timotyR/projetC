#include "init.c"

int main(void)
{
	setlocale(LC_ALL, "");
	initscr();cbreak();noecho(),nodelay(stdscr,TRUE);
	char c;
	//int posxM=posx-1;
	//int posyM=(5/2)+posy;
	
	// int timing;
	int i=0;
	int nbMissile=30;
	JOUEUR j1= init_joueur();
	ENNEMI e1= init_ennemi('S',"vaisseauB2.txt",10,10,18,6);
	ENNEMI e2= init_ennemi('S',"vaisseauB.txt",10,15,18,6);
	ENNEMI e3= init_ennemi('S',"vaisseauB2.txt",10,20,18,6);
	// MISSILE m1=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'I');
	MISSILE* tabM =tabMissile(nbMissile,j1);
	printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
	printSkinCurse(e1.skin,e1.length,e1.posx,e1.posy,e1.largeur);
	printSkinCurse(e2.skin,e2.length,e2.posx,e2.posy,e2.largeur);
	printSkinCurse(e3.skin,e3.length,e3.posx,e3.posy,e3.largeur);
	move(LINES - 1, COLS - 1);
	while((c=getch())!=27)
	{
		
		if(c=='s'&&j1.posx<37)
		{
			supprSkinCurse(j1.posx, j1.posy,c,j1.length/j1.largeur,j1.largeur);
			j1.posx++;
		}
		if(c=='z'&&j1.posx>1)
		{
			supprSkinCurse(j1.posx, j1.posy,c,j1.length/j1.largeur,j1.largeur);
			j1.posx--;
		}
		if(c=='q'&&j1.posy>1)
		{
			supprSkinCurse(j1.posx, j1.posy,c,j1.length/j1.largeur,j1.largeur);
			j1.posy--;
		}
		if(c=='d'&&j1.posy<60)
		{
			supprSkinCurse(j1.posx, j1.posy,c,j1.length/j1.largeur,j1.largeur);
			j1.posy++;
		}
		printSkinCurse(j1.skin,j1.length,j1.posx,j1.posy,j1.largeur);
		
		
		for(int j=0;j<nbMissile;j++)
		{
			if(tabM[j].etat=='V')
			{
				tabM[j].timing = (tabM[j].timing+1)%tabM[j].vitesse;
				if(tabM[j].timing==100)
					tabM[j].posx--;
				mvprintw(tabM[j].posx,tabM[j].posy,"%s",tabM[j].skin);
				mvprintw(tabM[j].posx+1,tabM[j].posy," ");
				if(tabM[j].posx==0)
				{
					tabM[j].etat='I';
				}
				if(tabM[j].etat=='I')
				{
					mvprintw(tabM[j].posx,tabM[j].posy," ");
				}
			}
		}
		if(c=='p')
		{
			tabM[i].timing=0;
			tabM[i]=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'V');
			if(i<=nbMissile-2)
				i++;
			else
				i=0;
		}
			// }
		/*
		if(m1.etat=='V')
		{
			timing = (timing+1)%m1.vitesse;
			if(timing==100)
			{
				m1.posx--;
			}
			// timeout(500);
			//napms(500);
			mvprintw(m1.posx+1,m1.posy," ");
			mvprintw(m1.posx,m1.posy,"%s",m1.skin);
			if(m1.posx==0)
			{
				mvprintw(m1.posx,m1.posy," ");
				m1=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'I');
			}
		}
		else
		{
			timing=0;
			if(c=='p')
			{
				m1=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'V');
			}
		}
		*/
		//printw("%d %d",j1.posx,j1.posy);
		move(LINES - 1, COLS - 1);
		
	}
	
	getch();
	endwin();
	
	return 0;
}