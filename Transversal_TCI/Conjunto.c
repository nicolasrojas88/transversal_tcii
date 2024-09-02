#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Conjunto.h"


int leeCad(elem cadena, int tam) {
	if (tam <= 0) return 0;
	memset(cadena, '\0', tam);
	int j = 0;
	char c;
	while ((c = getchar()) != EOF && c != '\n' && j < tam - 1) {
		cadena[j++] = c;
	}
	cadena[j] = '\0';  // Asegura que la cadena est� terminada en NULL
	// Limpia el b�fer de entrada
	while (c != EOF && c != '\n') {
		c = getchar();
	}
	return j > 0;
}

tpn ConjVacio() {
	return NULL;
}
// Funci�n para crear un nuevo nodo
tpn CreaNodo(elem x) {
	tpn nodo = (t_nodo*) malloc(sizeof(t_nodo));
	if (nodo == NULL) {
		printf("Error de memoria al crear nodo.\n");
		exit(1);
	}
	// Inicializa toda la cadena a '\0'
	memset(nodo->e, '\0', sizeof(nodo->e));
	// Copia la cadena, dejando espacio para el NULL
	strncpy(nodo->e, x, sizeof(nodo->e) - 1);
	nodo->e[sizeof(nodo->e) - 1] = '\0';  // Asegura que la cadena est� terminada en NULL
	nodo->sig = NULL;  // Inicializa el puntero siguiente
	printf("Creando nodo con elemento: %s\n", nodo->e);
	return nodo;
}
// Funci�n para insertar un elemento en la lista
void InsertaElem(tpn *cab, tpn x) {
	if (*cab == NULL) {
		*cab = x;
	} else {
		tpn aux = *cab;
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = x;
	}
	printf("Elemento a�adido a la lista: %s\n", x->e);
}

// Funci�n para cargar un conjunto
void CargaConj(tpn* cab, int *x) {
	int i;
	elem y;
	tpn aux;
	
	printf("Cuantos elementos desea cargar? ");
	if (scanf("%d", x) != 1) {
		printf("Error al leer el n�mero de elementos.\n");
		exit(1);
	}
	
	// Limpia el b�fer de entrada despu�s de scanf
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	
	for (i = 1; i <= *x; i++) {
		printf("Ingrese elem %d: ", i);
		if (leeCad(y, sizeof(y)) == 0) {
			printf("Error al leer el elemento.\n");
			exit(1);
		}
		aux = CreaNodo(y);
		InsertaElem(cab, aux);
		printf("Elemento a�adido a la lista: %s\n", y);
	}
}
int Compara(elem x, tpn A) {
	tpn aux = A;
	while (aux != NULL) {
		if (strcmp(aux->e, x) == 0)
			return 1; // Encontr� una coincidencia
		aux = aux->sig;
	}
	return 0; // No encontr� coincidencias
}


tpn Diferencia(tpn A, tpn B) {
	tpn C = ConjVacio();
	if (A != NULL && B != NULL) {
		tpn aux1 = A;
		while (aux1 != NULL) {
			if (Compara(aux1->e, B) == 0) {
				tpn y = CreaNodo(aux1->e);
				InsertaElem(&C, y);
			}
			aux1 = aux1->sig;
		}
	}
	return C;
}

tpn Union(tpn A, tpn B) {
	tpn C, aux, aux2;
	if (A == NULL) return B; // Si A es NULL, la uni�n es solo B
	C = A;
	aux = A;
	
	while (aux->sig != NULL)
		aux = aux->sig;
	aux2 = Diferencia(B, A);
	aux->sig = aux2;
	
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

// Funci�n para mostrar un conjunto
void MuestraConj(tpn cab) {
	if (cab == NULL) {
		printf("{}");
	} else {
		printf("{ ");
		while (cab != NULL) {
			printf("'%s'", cab->e);  // Imprime la cadena entre comillas
			cab = cab->sig;
			if (cab != NULL) {
				printf(", ");
			}
		}
		printf(" }\n");
	}
}
