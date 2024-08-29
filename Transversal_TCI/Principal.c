#include<stdio.h>
#include "Conjunto.h"
#include "Transicion.h"

int main (int argc, char *argv[]) {
	tpn c,a,I;
	int tam,tam1;
	c=ConjVacio();
	a=ConjVacio();
	printf("Vamos a cargar un Conjunto\n");
	CargaConj(&c,&tam);
	printf("Vamos a cargar otro Conjunto\n");
	CargaConj(&a,&tam1);
	printf("Vamos a hacer la Interseccion ");
	//I= Interseccion(c,a);
	I=Union(a,c);
	MuestraConj(I);
	/*trans cab, nue;
	nue= CreaTrans();
	CargaTrans(&cab , nue );
	MuestraTrans(cab); */
	return 0;
}
