#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <string.h>
#include <stdio.h>
#define MAX_ELEM_SIZE 100

typedef char elem[MAX_ELEM_SIZE];

typedef struct nodo {
	elem e;
	struct nodo* sig;
} t_nodo;

typedef t_nodo* tpn;

int leeCad(elem cadena, int tam);
void InsertaElem(tpn *cab, tpn x);
void CargaConj(tpn* cab, int *x);
tpn Union(tpn A, tpn B);
tpn ConjVacio();
tpn Interseccion(tpn A, tpn B);
void MuestraConj(tpn A);
tpn CreaNodo(elem x);
int Compara(elem x, tpn A);
tpn Diferencia(tpn A, tpn B);

#endif
