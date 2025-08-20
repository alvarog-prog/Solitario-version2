
#include "checkML.h"
#include "tablero.h"
#include "juego.h"
#include "movimiento.h"
using namespace std;



const string FG_BLACK = "\x1B[30m";
const string FG_BLUE = "\x1b[34m";
const string BG_BLACK = "\x1B[40m";
const string BG_BROWN = "\x1B[48;5;94m";
const string BG_ORANGE = "\x1B[48;2;204;102;0m";
const string Reset = "\x1b[0m";

const char Horizontal = char(196);
const char UpperLeft = char(218);
const char UpperCross = char(194);
const char UpperRight = char(191);
const char Vertical = char(179);
const char MidLeft = char(195);
const char MidCross = char(197);
const char MidRight = char(180);
const char LowerLeft = char(192);
const char LowerCross = char(193);
const char LowerRight = char(217);
const char Square = char(219);

//Funciones privadas de módulo tablero:

// dibuja la cabecera de la tabla (nº de las columnas)
void dibujaCabecera(const tTablero& tablero);
void dibujaBordeHorizontal(const tTablero& tablero, char left, char cross, char right);
// dibuja la banda exterior de las celdas de una fila del tablero
void dibujaBordeCelda(const tTablero& tablero, int fila);
// dibuja la banda central de las celdas de una fila del tablero
void dibujaCentroCelda(const tTablero& tablero, int fila);



void dibujaCentroCelda(const tTablero& tablero, int fila) {
	cout << "  " << setw(2) << fila + 1;  // pintamos el nº de fila
	for (int k = 0; k < tablero.cols; k++) { // para cada columna
		cout << Vertical; // pintamos barra vertical
		if (tablero.celdas[fila][k] == NULA) { // si es celda NULA: fondo negro y pintamos
			cout << BG_BLACK;
			cout << "      ";
		}
		else { // para celda útil
			if (tablero.filaMeta == fila && tablero.colMeta == k)  // si contiene la meta: fondo naranja
				cout << BG_ORANGE;
			else  // si no contiene la meta: fondo marrón
				cout << BG_BROWN;
			cout << "  "; // pintamos la primera parte de la banda
			if (tablero.celdas[fila][k] == VACIA)  // si está vacía: primer plano negro
				cout << FG_BLACK;
			else  // si tiene ficha: primer plano azul
				cout << FG_BLUE;
			cout << Square << Square;  // pintamos el cuadrado duplicado
			cout << Reset;
			if (tablero.filaMeta == fila && tablero.colMeta == k)
				cout << BG_ORANGE;
			else
				cout << BG_BROWN;
			cout << "  ";  // pintamos la tercera parte de la banda
		}
		cout << Reset;
	}
	cout << Vertical << endl;  // pintamos la barra vertical
}


// dibuja la cabecera de la tabla (nº de las columnas)
void dibujaCabecera(const tTablero& tablero) {
	cout << setw(2) << "    ";
	cout << setw(5) << 1;
	for (int i = 2; i <= tablero.cols; i++)
		cout << setw(7) << i;
	cout << endl;
}


void dibujaBordeHorizontal(const tTablero& tablero, char left, char cross, char right) {
	cout << "    ";
	cout << left;
	for (int i = 0; i < tablero.cols - 1; i++)
		cout << string(6, Horizontal) << cross;
	cout << string(6, Horizontal) << right << endl;
}


void dibujaBordeCelda(const tTablero& tablero, int fila) {
	cout << "    ";  // para llegar a la posición de la tabla
	for (int k = 0; k < tablero.cols; k++) { // para cada columna
		cout << Vertical; // pintamos barra vertical
		if (tablero.filaMeta == fila && tablero.colMeta == k) // si contiene meta: fondo naranja
			cout << BG_ORANGE;
		else if (tablero.celdas[fila][k] == NULA) // si es celda NULA: fondo negro
			cout << BG_BLACK;
		else // si es útil (con o sin ficha): fondo marrón
			cout << BG_BROWN;
		cout << "      "; // pintamos la banda
		cout << Reset;
	}
	cout << Vertical << endl; // pintamos barra vertical
}








void cargar(tTablero& tablero, ifstream& file) {
	int num;
	file >> tablero.filas >> tablero.cols;
	for (int i = 0; i < tablero.filas; i++) {
		for (int j = 0; j < tablero.cols; j++) {
			file >> num;
			tablero.celdas[i][j] = tCelda(num);
		}
	}
	file >> tablero.filaMeta >> tablero.colMeta;
}

void mostrar(const tTablero& tablero) {
	//system("cls");//Para borrar consola
	dibujaCabecera(tablero);
	dibujaBordeHorizontal(tablero, UpperLeft, UpperCross, UpperRight);
	for (int fila = 0; fila < tablero.filas; fila++) {
		dibujaBordeCelda(tablero, fila);
		dibujaCentroCelda(tablero, fila);
		dibujaBordeCelda(tablero, fila);
		if (fila < tablero.filas - 1) {
			dibujaBordeHorizontal(tablero, MidLeft, MidCross, MidRight);
		}
		else {
			dibujaBordeHorizontal(tablero, LowerLeft, LowerCross, LowerRight);
		}
	}

}




bool valida(const tTablero& tablero, int fila, int col) {//Comprobar  que la posicion está dentro del tablero
	bool valido = false;
	if (fila >= 0 && fila <= tablero.filas) {
		if (col >= 0 && col <= tablero.cols) {
			valido = true;
		}
	}
	return valido;
}

bool eleccionValida(const tTablero& tablero, int fila, int col) {
	bool correcto = false;
	if (valida(tablero, fila, col) && tablero.celdas[fila][col] == FICHA) {
		correcto = true;//Si la posición está dentro del tablero y tiene una ficha, devuelve true 
	}
	return correcto;
}

void ponCelda(tTablero& tablero, int fila, int col, tCelda celda) {
	tablero.celdas[fila][col] = celda;
}

tCelda dameCelda(const tTablero& tablero, int fila, int col) {//Devuelvo el contenido de dicha posición(NULA,VACÍA o FICHA)
	tCelda contenido{};

	if (tablero.celdas[fila][col] == NULA) {
		contenido = NULA;
	}
	else if (tablero.celdas[fila][col] == VACIA) {
		contenido = VACIA;
	}
	else if (tablero.celdas[fila][col] == FICHA) {
		contenido = FICHA;
	}
	return contenido;
}

void reseteaTablero(tTablero& tablero, int f, int c) {//
	tablero.filas = f;//Inicializamos el tablero.
	tablero.cols = c;
	for (f = 0; f < tablero.filas; f++) {
		for (c = 0; c < tablero.cols; c++) {
			tablero.celdas[f][c] = NULA;//Convertimos todas sus celdas en nulas.
		}
	}
}

void fichaAleatoria(const tTablero& tablero, int& fila, int& col) {
	do {
		fila = rand() % tablero.filas;
		col = rand() % tablero.cols;
	} while (tablero.celdas[fila][col] != FICHA);//Elige aleatoriamente una posición del tablero que tenga ficha.
}


int numFilas(const tTablero& tablero) {
	return tablero.filas;//Devuelvo el número de filas que tiene el tablero.
}

int numColumnas(const tTablero& tablero) {
	return tablero.cols;//Devuelve el número de columnas que tiene el tablero.
}

void dameMeta(const tTablero& tablero, int& fila, int& col) {
	fila = tablero.filaMeta;//Devuelve la fila de la meta.
	col = tablero.colMeta;//Devuelve la columna de la meta.
}

void ponMeta(tTablero& tablero, int fila, int col) {
	tablero.filaMeta = fila;//Pone fila, como la fila de la meta.
	tablero.colMeta = col;//Pone col, como la columna de la meta.
}



void guardar(const tTablero& tablero, std::ofstream& file) {
	file << tablero.filas;
	file << " ";
	file << tablero.cols;
	file << " ";
	file << endl;
	for (int i = 0; i < tablero.filas; i++) {
		for (int j = 0; j < tablero.cols; j++) {
			file << tablero.celdas[i][j];
			file << " ";
		}
		file << endl;
	}
	file << tablero.filaMeta;
	file << " ";
	file << tablero.colMeta<<endl;

}
