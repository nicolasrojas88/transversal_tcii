#include <stdio.h>
#include <stdlib.h>
#include "Transicion.h"
#include "Conjunto.h"

Cam CreaCampo(){
	Cam ca;
	int tp,tl;
	//Cargar El Estado de Partida, con el TAD Conjunto
	printf("====Conjunto Partida====\n");
	CargaConj(&(ca->part),&tp);
	fflush(stdin);
	
	//Carga El Simbolo
	printf("\nIngrese Simbolo del Alfabeto: ");
	leeCad(ca->simb,5);
	fflush(stdin);
	//Carga El Estado de LLegada, con el TAD Conjunto
	printf("====Conjunto LLegada====\n");
	CargaConj(&(ca->lleg),&tl);
	fflush(stdin);
	
	
	return ca;
}
	trans CreaTrans()
	{
		trans p;
		p= (t_delta*) malloc (sizeof (t_delta));
		p->datos=CreaCampo();
		p->sig= NULL;
		
		return p;
	}
	
	trans IniciaLista()
	{
		return NULL;
	}
	
	void CargaTrans(trans *cab, trans nw)
	{
		trans ult;
		
		if (*cab != NULL)
		{
			ult= *cab;
			while (ult-> sig != NULL)
				ult= ult->sig;
			ult->sig= nw;
		}
		else
			*cab= nw;
		
	}
	
	void MuestraTrans(trans cab)
	{
		if(cab!=NULL){
			printf("QP: ");
			while(cab->datos->part!=NULL ){
				MuestraConj(cab->datos->part);
				
			}
			printf("\n QLL: ");
			while(cab->datos->lleg!=NULL)
				MuestraConj(cab->datos->lleg);
			
			printf("\n SING={%s}",cab->datos->simb );
		}else
		   printf("ERROR :P");
		
	}
	
