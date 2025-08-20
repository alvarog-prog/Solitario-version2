
#ifndef tablero_h
#define tablero_h
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>


const int MAX = 6;

typedef enum tCelda { NULA, VACIA, FICHA };

typedef tCelda tCeldaArray[MAX][MAX];

struct tTablero {
	int filas, cols;
	int filaMeta, colMeta;
	tCeldaArray celdas;
};


// Subprogramas del enunciado
// IMPORTANTE: decide cuáles permanecen públicos y traslada los que creas que deben ser privados (si es el caso)

void cargar(tTablero& tablero, std::ifstream& file);
bool valida(const tTablero& tablero, int fila, int col);
bool eleccionValida(const tTablero& tablero, int fila, int col);
tCelda dameCelda(const tTablero& tablero, int fila, int col);
void ponCelda(tTablero& tablero, int fila, int col, tCelda celda);
int numFilas(const tTablero& tablero);
int numColumnas(const tTablero& tablero);
void dameMeta(const tTablero& tablero, int& fila, int& col);
void ponMeta(tTablero& tablero, int fila, int col);
void mostrar(const tTablero& tablero);
void fichaAleatoria(const tTablero& tablero, int& fila, int& col);
void reseteaTablero(tTablero& tablero, int f, int c);


void mostrar(const tTablero& tablero);

void guardar(const tTablero& tablero, std::ofstream& file);

#endif

