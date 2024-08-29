#include <stdio.h>
#include "Conjunto.h"
#include <stdlib.h>
#include <string.h>


typedef char elem[5];
int leeCad(elem cadena, int tam)
{
	int j=0,ret=0;
	char c= getchar();
	while(c != EOF && c!= '\n' && j< tam-1)
	{
		cadena[j]= c;
		j++;
		c= getchar();
		ret= 1;
	}
	cadena[j]= '\0';
	while(c!= EOF && c!= '\n')
		c= getchar();
	return ret;
}
tpn CreaNodo(elem x)
{
	tpn nodo= NULL;
	
	nodo= (t_nodo*) malloc (sizeof (t_nodo));
	strcpy(nodo->e, x);
	nodo-> sig= NULL;
	
	return nodo;
}


tpn ConjVacio()
{
	return NULL;
}


void InsertaElem(tpn *cab, tpn x)
{
	tpn aux;
	
	if (*cab== NULL)
		*cab= x;
	else
	{
		aux= *cab;
		while( aux->sig!= NULL)
			aux= aux->sig;
		
		aux->sig= x;
	}	
}

void CargaConj(tpn* cab, int *x)
{
	int i;
	elem y;
	tpn aux;
	
	printf("Cuantos elementos desea cargar?? ");
	scanf("%d",x);

	for (i=1; i<= *x; i++)
	{
		fflush(stdin);
		printf("Ingrese elem %d: ",i);
		leeCad(y,5);
		aux= CreaNodo(y);
		InsertaElem(cab,aux);
	}
}

int Compara(elem x, tpn A)
{
	tpn aux;
	aux= A;
	
	while (aux-> sig != NULL && strcmp(aux->e,x)!= 0)
		aux= aux-> sig;
	if (strcmp(aux->e,x)!= 0)
		return 0;
	else 
		return 1;
}

tpn Diferencia(tpn A, tpn B)
{
	tpn C,aux1, aux2,y;
	C= ConjVacio();
	if ( A != NULL && B!= NULL)
	{
		aux1= A;
		while (aux1 != NULL)
		{
			aux2= B;
			if (Compara(aux1->e,aux2)== 0)
			{
				y= CreaNodo(aux1->e);
				InsertaElem(&C,y);
			}
			aux1= aux1->sig;
		}
	}
	return C;
}

tpn Union(tpn A, tpn B)
{
	tpn C,aux,aux2;
	C= A;
	aux=A;
	
	while (aux->sig != NULL)
		aux= aux->sig;
	aux2= Diferencia(B,A);
	aux->sig= aux2;
	
	return C;
}

tpn Interseccion(tpn A, tpn B)
{
	tpn C,aux,aux2,y;
	
	C= ConjVacio();
	aux= A;
	
	while (aux != NULL)
	{
		aux2= B;
		if(Compara(aux->e,aux2) == 1)
		{
			y= CreaNodo(aux->e);
			InsertaElem(&C,y);
		}
		aux= aux->sig;
	}
	
	return C;
}

void MuestraConj(tpn cab)
{
	if (cab== NULL)
		printf("{}");
	else
	{
		printf("{ ");
		while(cab != NULL)
		{
			printf("%s, ",cab->e);
			cab= cab->sig;
		}
		printf("}");
	}
}
