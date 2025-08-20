//Álvaro Gil Arjona
//Víctor Verdú García
//Grupo: LAB 11 G12

#ifndef ListaJuegos_h
#define ListaJuegos_h
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "juego.h"




const int DELTA = 5;
struct tListaJuegos {
	tJuegoPtr juegos = nullptr;
	int contador = 0, capacidad = 0;
};

void cargar(tListaJuegos& lista, std::ifstream& fichero);
void guardar(const tListaJuegos& lista, std::ofstream& file);
void insertar(tListaJuegos& lista, tJuego& juego);
void eliminar(tListaJuegos& lista, int pos);
int eligeJuego(tListaJuegos& lista);
void mostrar(const tListaJuegos& lista);
void liberar(tListaJuegos& lista);

void disminuir(tListaJuegos& lista);

void actualizaPrivacidad(tListaJuegos& lista, const tJuego& juego, int posJuego);
tJuego dameJuego(const tListaJuegos& lista, int pos);

#endif