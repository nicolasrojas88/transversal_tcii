#ifndef CONJUNTO_H
#define CONJUNTO_H
#include <string.h>
#include <stdio.h>

typedef char elem[5];
typedef struct nodo{
	elem e;
	struct nodo* sig;
} t_nodo;

typedef t_nodo* tpn;

int leeCad(elem cadena, int tam);
void InsertaElem(tpn *cab, tpn x);
void CargaConj(tpn* cab, int *x);
tpn Union(tpn A, tpn B);
tpn Interseccion(tpn A, tpn B);
void MuestraConj(tpn A);

#endif
