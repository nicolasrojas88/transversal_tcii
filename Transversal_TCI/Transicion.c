#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Transicion.h"
#include "Conjunto.h"

Cam CreaCampo() {
	Cam ca = (Cam)malloc(sizeof(t_camp));
	if (ca == NULL) {
		printf("Error de memoria\n");
		exit(1);
	}
	
	int tp, tl;
	
	// Inicializar cadenas
	memset(ca->simb, '\0', sizeof(ca->simb));
	
	// Cargar el conjunto de partida
	printf("====Conjunto Partida====\n");
	CargaConj(&(ca->part), &tp);
	
	// Cargar el s�mbolo del alfabeto
	printf("\nIngrese S�mbolo del Alfabeto: ");
	if (!leeCad(ca->simb, sizeof(ca->simb))) {
		printf("Error al leer el s�mbolo del alfabeto.\n");
		exit(1);
	}
	
	// Cargar el conjunto de llegada
	printf("====Conjunto Llegada====\n");
	CargaConj(&(ca->lleg), &tl);
	
	return ca;
}

// Funci�n para crear una nueva transici�n
trans CreaTrans() {
	trans p = (trans)malloc(sizeof(t_delta));
	if (p == NULL) {
		printf("Error de memoria al crear transici�n.\n");
		exit(1);
	}
	p->datos = CreaCampo();
	p->sig = NULL;
	return p;
}

// Funci�n para inicializar una lista de transiciones
trans IniciaLista() {
	return NULL;
}

// Funci�n para cargar una nueva transici�n en la lista
void CargaTrans(trans *cab, trans nw) {
	if (nw == NULL) {
		printf("Error: Nueva transici�n es NULL.\n");
		return;
	}
	
	nw->sig = NULL;
	
	if (*cab == NULL) {
		*cab = nw;
		printf("Transici�n a�adida como cabeza.\n");
	} else {
		trans ult = *cab;
		while (ult->sig != NULL) {
			ult = ult->sig;
		}
		ult->sig = nw;
		printf("Transici�n a�adida al final.\n");
	}
	
	// Verificaci�n del estado actual de la lista
	MuestraTrans(*cab);
}

// Funci�n para mostrar todas las transiciones
void MuestraTrans(trans cab) {
	if (cab == NULL) {
		printf("No hay transiciones para mostrar.\n");
		return;
	}
	
	while (cab != NULL) {
		if (cab->datos == NULL) {
			printf("Error: Transici�n con datos NULL.\n");
			return;
		}
		
		printf("QP: ");
		MuestraConj(cab->datos->part);
		printf("\nQLL: ");
		MuestraConj(cab->datos->lleg);
		printf("\nSING={%s}\n", cab->datos->simb);
		
		cab = cab->sig;
	}
}
