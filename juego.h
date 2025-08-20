//Álvaro Gil Arjona
//Víctor Verdú García
//Grupo: LAB 11 G12

#ifndef juego_h
#define juego_h
#include <string>
#include "tablero.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

typedef enum tEstado { JUGANDO, GANADOR, BLOQUEO };

struct tJuego {
	tTablero tablero;
	tEstado estado;

};
typedef tJuego* tJuegoPtr;


// Subprogramas del enunciado
// IMPORTANTE: decide cuáles permanecen públicos y traslada los que creas que deben ser privados (si es el caso)

void cargar(tJuego& juego, std::ifstream& fichero);
void mostrar(const tJuego& juego);

void generar(tJuego& juego, int pasos);

void guardar(const tJuego& juego, std::ofstream& fichero);

void jugar(tJuego& juego, bool& parado);

void estadoBloq(tJuego& juego);//QUITAR

void estadoJug(tJuego& juego);//QUITAR

bool estado(tJuego& juego);

#endif
