#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automata.h"

taf IniciaAF() {
	return NULL;
}

taf CreaAF() {
	taf nuevoAF = (taf)malloc(sizeof(t_pAF));
	if (nuevoAF == NULL) {
		printf("Error de memoria\n");
		exit(1);
	}
	nuevoAF->comp = NULL;
	nuevoAF->sig = NULL;
	return nuevoAF;
}

void CargaAF(taf* automata, int componente) {
	taf nuevoAF = CreaAF();
	int n;
	
	switch (componente) {
	case 1:
	case 2:
	case 5:
		nuevoAF->comp = (void*)malloc(sizeof(*nuevoAF->comp));
		if (nuevoAF->comp == NULL) {
			printf("Error al asignar memoria\n");
			exit(1);
		}
		nuevoAF->comp->conjunto = ConjVacio();
		CargaConj(&(nuevoAF->comp->conjunto), &n);
		break;
	case 3:
		nuevoAF->comp = (void*)malloc(sizeof(*nuevoAF->comp));
		if (nuevoAF->comp == NULL) {
			printf("Error al asignar memoria\n");
			exit(1);
		}
		nuevoAF->comp->transiciones = IniciaLista();
		printf("Ingrese la cantidad de transiciones: ");
		scanf("%d", &n);
		trans nuevaTrans;
		for (int i = 0; i < n; i++) {
			nuevaTrans = CreaTrans();
			CargaTrans(&(nuevoAF->comp->transiciones), nuevaTrans);
		}
		break;
	case 4:
		nuevoAF->comp = (void*)malloc(sizeof(*nuevoAF->comp));
		if (nuevoAF->comp == NULL) {
			printf("Error al asignar memoria\n");
			exit(1);
		}
		elem estado_inicial;
		leeCad(estado_inicial, 5);
		nuevoAF->comp->conjunto = CreaNodo(estado_inicial);
		break;
	default:
		printf("Componente desconocido\n");
		free(nuevoAF);
		return;
	}
	
	if (*automata == NULL) {
		*automata = nuevoAF;
	} else {
		taf aux = *automata;
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = nuevoAF;
	}
}

taf CargarAFND() {
	taf afnd = IniciaAF();
	
	printf("[DEBUG] Iniciando carga del AFND\n");
	
	// Cargar conjunto de estados (componente 1)
	printf("[DEBUG] Iniciando CargaAF para componente 1\n");
	CargaAF(&afnd, 1);
	
	// Cargar alfabeto (componente 2)
	printf("[DEBUG] Iniciando CargaAF para componente 2\n");
	CargaAF(&afnd, 2);
	
	// Cargar transiciones (componente 3)
	printf("[DEBUG] Iniciando CargaAF para componente 3\n");
	CargaAF(&afnd, 3);
	
	// Cargar estado inicial (componente 4)
	printf("[DEBUG] Iniciando CargaAF para componente 4\n");
	CargaAF(&afnd, 4);
	
	// Cargar conjunto de estados finales (componente 5)
	printf("[DEBUG] Iniciando CargaAF para componente 5\n");
	CargaAF(&afnd, 5);
	
	printf("[DEBUG] AFND cargado exitosamente\n");
	return afnd;
}
tpn CopiaConjunto(tpn original) {
	if (original == NULL) {
		return NULL;
	}
	
	tpn copia = NULL;
	tpn temp = original;
	
	while (temp != NULL) {
		InsertaElem(&copia, CreaNodo(temp->e));
		temp = temp->sig;
	}
	
	return copia;
}

taf ConvertirAFNDaAFD(taf afnd) {
	taf afd = CreaAF();
	if (afd == NULL) {
		printf("Error al crear el AFD\n");
		exit(1);
	}
	
	// Copiar el conjunto de estados
	afd->comp = (void*)malloc(sizeof(*afd->comp));
	if (afd->comp == NULL) {
		printf("Error al asignar memoria para el componente del AFD.\n");
		exit(1);
	}
	afd->comp->conjunto = CopiaConjunto(ObtenerEstados(afnd));
	
	// Copiar el alfabeto
	afd->sig = CreaAF();
	afd->sig->comp = (void*)malloc(sizeof(*afd->sig->comp));
	if (afd->sig->comp == NULL) {
		printf("Error al asignar memoria para el componente del alfabeto del AFD.\n");
		exit(1);
	}
	afd->sig->comp->conjunto = CopiaConjunto(ObtenerAlfabeto(afnd));
	
	// Copiar el estado inicial
	afd->sig->sig = CreaAF();
	afd->sig->sig->comp = (void*)malloc(sizeof(*afd->sig->sig->comp));
	if (afd->sig->sig->comp == NULL) {
		printf("Error al asignar memoria para el componente del estado inicial del AFD.\n");
		exit(1);
	}
	afd->sig->sig->comp->conjunto = CreaNodo(ObtenerEstadoInicial(afnd)->e);
	
	// Copiar las transiciones
	afd->sig->sig->sig = CreaAF();
	afd->sig->sig->sig->comp = (void*)malloc(sizeof(*afd->sig->sig->sig->comp));
	if (afd->sig->sig->sig->comp == NULL) {
		printf("Error al asignar memoria para el componente de transiciones del AFD.\n");
		exit(1);
	}
	afd->sig->sig->sig->comp->transiciones = NULL;
	
	trans transicionesAFND = ObtenerTransiciones(afnd);
	trans transicionActual = transicionesAFND;
	while (transicionActual != NULL) {
		trans nuevaTrans = CreaTrans();
		nuevaTrans->datos->part = CopiaConjunto(transicionActual->datos->part);
		strcpy(nuevaTrans->datos->simb, transicionActual->datos->simb);
		nuevaTrans->datos->lleg = CopiaConjunto(transicionActual->datos->lleg);
		CargaTrans(&(afd->sig->sig->sig->comp->transiciones), nuevaTrans);
		transicionActual = transicionActual->sig;
	}
	
	// Copiar los estados finales
	afd->sig->sig->sig->sig = CreaAF();
	afd->sig->sig->sig->sig->comp = (void*)malloc(sizeof(*afd->sig->sig->sig->sig->comp));
	if (afd->sig->sig->sig->sig->comp == NULL) {
		printf("Error al asignar memoria para el componente de estados finales del AFD.\n");
		exit(1);
	}
	afd->sig->sig->sig->sig->comp->conjunto = CopiaConjunto(ObtenerEstadosFinales(afnd));
	
	return afd;
}

void MuestraAF(taf automata) {
	int componente = 1;
	while (automata != NULL) {
		switch (componente) {
		case 1:
			printf("Conjunto de estados (Q): ");
			MuestraConj(automata->comp->conjunto);
			break;
		case 2:
			printf("\nAlfabeto (S): ");
			MuestraConj(automata->comp->conjunto);
			break;
		case 3:
			printf("\nTransiciones (d):\n");
			MuestraTrans(automata->comp->transiciones);
			break;
		case 4:
			printf("\nEstado inicial (q0): %s", automata->comp->conjunto->e);
			break;
		case 5:
			printf("\nConjunto de estados finales (F): ");
			MuestraConj(automata->comp->conjunto);
			break;
		}
		automata = automata->sig;
		componente++;
	}
}

tpn ObtenerEstados(taf automata) {
	return automata->comp->conjunto;
}

tpn ObtenerAlfabeto(taf automata) {
	if (automata != NULL && automata->sig != NULL) {
		return automata->sig->comp->conjunto;
	}
	return NULL;
}

trans ObtenerTransiciones(taf automata) {
	if (automata != NULL && automata->sig != NULL && automata->sig->sig != NULL) {
		return automata->sig->sig->comp->transiciones;
	}
	return NULL;
}

tpn ObtenerEstadoInicial(taf automata) {
	if (automata != NULL && automata->sig != NULL && automata->sig->sig != NULL && automata->sig->sig->sig != NULL) {
		return automata->sig->sig->sig->comp->conjunto;
	}
	return NULL;
}

tpn ObtenerEstadosFinales(taf automata) {
	if (automata != NULL && automata->sig != NULL && automata->sig->sig != NULL && automata->sig->sig->sig != NULL && automata->sig->sig->sig->sig != NULL) {
		return automata->sig->sig->sig->sig->comp->conjunto;
	}
	return NULL;
}
