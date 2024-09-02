#include<stdio.h>
#include "Conjunto.h"
#include "Transicion.h"
#include "Automata.h"

int main (int argc, char *argv[]) {
	/*trans cab = IniciaLista(); // Inicializar correctamente la lista
	trans nue = CreaTrans();
	
	CargaTrans(&cab, nue);
	MuestraTrans(cab);*/
	taf automataAFND, automataAFD;
	
	// Cargar el autómata AFND
	automataAFND = CargarAFND();
	
	printf("AFND cargado:\n");
	MuestraAF(automataAFND);
	
	// Convertir el AFND a AFD
	automataAFD = ConvertirAFNDaAFD(automataAFND);
	
	// Mostrar el AFD convertido
	printf("AFD convertido:\n");
	MuestraAF(automataAFD);
	
	return 0;
}
