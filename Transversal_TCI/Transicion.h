#ifndef TRANSICION_H
#define TRANSICION_H
#include "Conjunto.h"

typedef struct campos{
	tpn part;
	tpn lleg;
	elem simb;
} t_camp;
typedef t_camp* Cam;

typedef struct delta{
	Cam datos;
	struct delta* sig;
} t_delta;

typedef t_delta *trans;

trans CreaTrans();
trans IniciaLista();
void CargaTrans(trans *cab, trans nw);
void MuestraTrans(trans cab);

#endif
