
#ifndef movimiento_h
#define moviento_h
#include "tablero.h"
#include <iostream>




const int NUMDIR = 4;

enum tDireccion { ARRIBA, DERECHA, ABAJO, IZQUIERDA };

struct tMovimiento {
	tDireccion dir;
	int filaSaltada, colSaltada, filaDestino, colDestino;
};

typedef tMovimiento tMovimientoArray[NUMDIR];

struct tMovimientoLista {
	tMovimientoArray posibles;
	int contador;
};


// Subprogramas del enunciado
// IMPORTANTE: decide cuáles permanecen públicos y traslada los que creas que deben ser privados (si es el caso)

bool fichaBloqueada(const tTablero& tablero, int fila, int col);
tMovimiento leeMovimiento(const tTablero& tablero, int& fila, int& col, bool& fin);
void movimientoFicha(tTablero& tablero, int fila, int col, const tMovimiento& mov);
bool eligeMovimientoInverso(const tTablero& tablero, int fila, int col, tMovimiento& mov);
void realizaMovimientoInverso(tTablero& tablero, int fila, int col, const tMovimiento& mov);



#endif

