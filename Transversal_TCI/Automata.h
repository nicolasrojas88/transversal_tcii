#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "Conjunto.h"
#include "Transicion.h"

typedef struct AF {
	union {
		tpn conjunto;    // Para estados, alfabeto, y estado inicial/final
		trans transiciones; // Para las transiciones
	} *comp;
	struct AF *sig;
} t_pAF, *taf;

taf IniciaAF();
taf CreaAF();
void CargaAF(taf* automata, int componente);
taf CargarAFND();
taf ConvertirAFNDaAFD(taf afnd);
tpn CopiaConjunto(tpn original);  // Nueva función
void MuestraAF(taf automata);

tpn ObtenerEstados(taf automata);
tpn ObtenerAlfabeto(taf automata);
trans ObtenerTransiciones(taf automata);
tpn ObtenerEstadoInicial(taf automata);
tpn ObtenerEstadosFinales(taf automata);

#endif
