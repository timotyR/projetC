#include "affichage.c"

//fichier d'initialisation des differentes structures



VAISSEAU init_joueur()
{
	VAISSEAU J;
	
	J.length=40;
	J.posx = 65;
	J.posy = 55;
	J.vitesse = 5000;
	J.etat = 'V';
	J.timing=0;
	J.largeur=10;
	J.blindage=3;
	
	J.skin=getSkin(chargement("vaisseauA.txt",J.length),J.length);
	J.skin2=getSkin(chargement("vaisseauA2.txt",J.length),J.length);
	J.skin3=getSkin(chargement("vaisseauA3.txt",J.length),J.length);
	
	return J;
}

VAISSEAU init_ennemi(char D,char* nom_fic,char* nom_fic2,char* nom_fic3,int x, int y,int length,int largeur,int pts,int blind)
{
	VAISSEAU E;
	E.length=length;
	E.posx = x;
	E.posy = y;
	E.direction = D;
	E.vitesse = 5000;
	E.etat = 'V';
	E.timing=0;
	E.largeur=largeur;
	E.blindage=blind;
	E.points=pts;
	
	E.skin=getSkin(chargement(nom_fic,E.length),E.length);
	E.skin2=getSkin(chargement(nom_fic2,E.length),E.length);
	E.skin3=getSkin(chargement(nom_fic3,E.length),E.length);
	
	return E;
}
MISSILE init_missile(char D,int x, int y,char etat)
{
	MISSILE M;
	M.posx = x;
	M.posy = y;
	M.direction = D;
	M.vitesse = 20000;
	// M.skin=printChar(33);
	M.skin="¤";
	M.etat = etat;
	M.timing=0;
	return M;
}

ETOILE init_etoile()
{
	ETOILE E;
	E.posx = 1+(rand()%70);
	E.posy = 1+(rand()%120);
	E.vitesse = 1500;
	E.skin=printChar(34);
	E.etat = 'V';
	return E;
}

MISSILE* tabMissile(int length,VAISSEAU j1)
{
	MISSILE* M=malloc(length*sizeof(MISSILE));
	int i;
	for(i=0;i<length;i++)
	{
		M[i]=init_missile('N',j1.posx-1-1,(j1.largeur/2)+j1.posy-2,'I');
	}
	return M;
}

ETOILE* tabEtoile(int length)
{
	ETOILE* E=malloc(length*sizeof(ETOILE));
	int i;
	for(i=0;i<length;i++)
	{
		E[i]=init_etoile();
		if(i>=length-35)
		{
			E[i].posx = -(1+(rand()%83));
			E[i].posy = 1+(rand()%70);
		}
	}
	return E;
}

Ptliste initListe(VAISSEAU X)
{
	
	Ptliste P =(Liste*)malloc(sizeof(Liste));
	P->contenu=X;
	P->next=NULL;
	return P;
}

Ptliste insertentete(Ptliste L, VAISSEAU X)
{
	Ptliste P=initListe(X);
	if(L==NULL)
	{
		return P;
	}
	P->next=L;
	return P;
}

Ptliste initEnnemiList1()
{
	int x =-80;
	int y =1+(rand()%120);
	int i;
	Ptliste listEn = (Liste*)malloc(sizeof(Liste));
	
	for(i=0;i<4;i++)
	{
		listEn=insertentete(listEn, init_ennemi('S',"vaisseauC.txt","vaisseauC2.txt","vaisseauC3.txt",x,y+22+i*7,21,7,60,5));
		
	}
	for(i=0;i<6;i++)
	{
		listEn=insertentete(listEn, init_ennemi('S',"vaisseauE.txt","vaisseauE2.txt","vaisseauE3.txt",x+4,y+14+i*7,21,7,45,4));
	}
	for(i=0;i<8;i++)
	{
		listEn=insertentete(listEn, init_ennemi('S',"vaisseauD.txt","vaisseauD2.txt","vaisseauD3.txt",x+8,y+8+i*7,21,7,30,3));
	}
	for(i=0;i<10;i++)
	{
		listEn=insertentete(listEn, init_ennemi('S',"vaisseauB.txt","vaisseauB2.txt","vaisseauB3.txt",x+12,y+1+i*7,18,6,10,3));
	}
	return listEn;
}

void freeList(Ptliste list)
{
   Ptliste tmp;

   while (list != NULL)
    {
       tmp = list;
       list = list->next;
       free(tmp);
    }

}

MISSILE* missile_ennemi(Ptliste init,MISSILE* M,int nbMissile)
{
	Ptliste L=init;
	int listLen=0;
	int j,k;
	
	while(L->next!=NULL)
	{
		listLen++;
		L=L->next;
	}
	for(j=0;j<nbMissile;j++)
	{
		L=init;
		k=0;
		
		if(M[j].etat!='V')
		{
			if(L->next==NULL)
			{
				M[j]=init_missile('S',L->contenu.posx+(L->contenu.length/L->contenu.largeur)-1,(L->contenu.largeur/2)+L->contenu.posy-2,'V');
			}
			else
			{
				while(L->next!=NULL)
				{
					if(k==1+(rand()%listLen))
					{
						M[j]=init_missile('S',L->contenu.posx+(L->contenu.length/L->contenu.largeur)-1,(L->contenu.largeur/2)+L->contenu.posy-2,'V');
					}
					k++;
					L=L->next;
				}
			}
		}
	}
	return M;
}


Ptliste damage(Ptliste init,MISSILE* m1,int* score)
{
	Ptliste L=init;
	int i=0;

	if(L->next==NULL)
	{
		if(L->contenu.blindage>0&&hitBox(L->contenu,*m1))
		{
			L->contenu.blindage--;
			if(L->contenu.blindage==1)
			{
				L->contenu.skin=L->contenu.skin3;
			}
			else if(L->contenu.blindage==2)
			{
				L->contenu.skin=L->contenu.skin2;
			}
			m1->etat='I';
			return init;
		}
		if(L->contenu.blindage<=0)
		{
			*score=*score+L->contenu.points;
			free(L);
			return NULL;
		}
	}
	while(L->next!=NULL)
	{
		if(L->contenu.blindage>0&&hitBox(L->contenu,*m1))
		{
			L->contenu.blindage--;
			m1->etat='I';
			if(L->contenu.blindage==1)
			{
				L->contenu.skin=L->contenu.skin3;
			}
			else if(L->contenu.blindage==2)
			{
				L->contenu.skin=L->contenu.skin2;
			}
			return init;
		}
		if(L->contenu.blindage<=0)
		{
			*score=*score+L->contenu.points;
			return supprElt(init,i-1,L->next);
		}
		i++;
		L=L->next;
	}
	return init;
}

