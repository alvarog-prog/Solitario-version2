//Álvaro Gil Arjona
//Víctor Verdú García
//Grupo: LAB 11 G12
#include "checkML.h"
#include "movimiento.h"
#include "juego.h"
using namespace std;


//Funciones privadas del módulo juego
void actualizaEstado(tJuego& juego);
bool ganador(const tJuego& juego);
bool hayMovimientos(const tJuego& juego);
bool movimientoInverso(tJuego& juego);
void ejecutarMovimiento(tJuego& juego, bool& fin);




bool movimientoInverso(tJuego& juego) {//Devuelve si se ha podido realizar el movimiento o no.
	int fila, col;
	tMovimiento mov;
	bool realizado = false;
	fichaAleatoria(juego.tablero, fila, col);
	if (eligeMovimientoInverso(juego.tablero, fila, col, mov)) {
		realizaMovimientoInverso(juego.tablero, fila, col, mov);
		realizado = true;
	}
	else {
		realizado = false;//No ha podido realizarse, esto no quiere decir que no haya.
	}

	return realizado;
}


void ejecutarMovimiento(tJuego& juego, bool& fin) {//Hace un movimiento
	tMovimiento mov;
	int fila, col;

	mov = leeMovimiento(juego.tablero, fila, col, fin);
	if (!fin) {
		movimientoFicha(juego.tablero, fila, col, mov);
		mostrar(juego);
		actualizaEstado(juego);
	}

}


void actualizaEstado(tJuego& juego) {
	if (ganador(juego)) {//Si devuelve true, hemos ganado
		juego.estado = GANADOR;//actualizamos a ganador
		cout << "HAS GANADO" << endl;

	}
	else {
		if (!hayMovimientos(juego)) {//Si devuelve false, no hay movimientos
			juego.estado = BLOQUEO;//actualizamos a bloqueado
			cout << "ESTAS BLOQUEADO" << endl;
		}
		else {
			juego.estado = JUGANDO;//Continuamos jugando,hay movimientos
			cout << "SIGUE JUGANDO" << endl;
		}
	}
}


bool ganador(const tJuego& juego) {//Revisamos todo el tablero, para contar el numero de fichas
	bool ganas = false;;
	int contFichas = 0;
	for (int i = 0; i < numFilas(juego.tablero); i++) {
		for (int j = 0; j < numColumnas(juego.tablero); j++) {
			if (dameCelda(juego.tablero, i, j) == FICHA) {
				contFichas++;//Aumenta por cada ficha
			}
		}
	}
	int fila, col;
	dameMeta(juego.tablero, fila, col);
	if (contFichas == 1 && eleccionValida(juego.tablero, fila, col)) {
		ganas = true;//Si solo hay una ficha y se encuentra en el tablero(has ganado) devuelve true
	}
	return ganas;
}


bool hayMovimientos(const tJuego& juego) {//Comprobamos si hay alguna ficha que no este bloqueada, es decir, que nos podamos mover
	bool bloqueado = false;
	int fila = 0;
	while (fila < numFilas(juego.tablero) && !bloqueado) {//Recorremos filas
		int col = 0;
		while (!bloqueado && col < numColumnas(juego.tablero)) {//Recorremos columnas
			if (eleccionValida(juego.tablero, fila, col)) {
				if (fichaBloqueada(juego.tablero, fila, col)) {
					bloqueado = false;//Estas bloqueado
				}
				else {
					bloqueado = true;
				}
			}
			col++;
		}
		fila++;
	}
	return bloqueado;
}







void cargar(tJuego& juego,ifstream& fichero) {
	cargar(juego.tablero, fichero);//Carga tablero
}

void mostrar(const tJuego& juego) {
	mostrar(juego.tablero);//Mostrar tablero
}





void generar(tJuego& juego, int pasos) {//Crea el tablero aleatorio, poniendo todas sus celdas como nulas
	int fila, col, filMeta, colMeta;
	srand(time(NULL));

	fila = 4 + rand() % (MAX - 3);//Generación aleatoria del tamaño de las filas.
	col = 4 + rand() % (MAX - 3);//Generación aleatoria del tamaño de las columnas.
	reseteaTablero(juego.tablero, fila, col);//Que todas las posiciones sean nulas.
	filMeta = rand() % fila;//Generación aleatoria de la fila en la que estará la meta.
	colMeta = rand() % col;//Generación aleatoria de la columna en la que estará la meta.

	ponMeta(juego.tablero, filMeta, colMeta);//Colocamos la meta en dicha posición creada aleatoriamente.
	ponCelda(juego.tablero, filMeta, colMeta, FICHA);//La rellenamos con una ficha.

	cout << "Cuantos pasos quieres realizar:" << endl;
	cin >> pasos;//Se solicita por pantalla el número de pasos que se quiere dar(no tiene porque dar todos).
	int i = 0;
	while (i < pasos) {
		mostrar(juego);
		bool ultimoMov = movimientoInverso(juego);
		if (!ultimoMov) {
			i = pasos;//Para salir del bucle.
		}
		else {
			i++;//Aumentamos para pasar al siguiente paso.
			cout << "ENTER PARA VER EL PASO " << i << endl;
			char boton;
			boton = getchar();
		}
	}
	mostrar(juego);
	juego.estado = JUGANDO;//Inicializamos el estado a jugando.
}



void guardar(const tJuego& juego, std::ofstream& fichero) {
	guardar(juego.tablero, fichero);
}


void jugar(tJuego& juego,bool& parado) {
	
	bool fin = false;
	ejecutarMovimiento(juego, fin);
	while (juego.estado == JUGANDO && !fin) {
		ejecutarMovimiento(juego, fin);
		
	}
	if (juego.estado == BLOQUEO) {//Estamos bloqueados, hemos perdido
		cout << "HAS PERDIDO LA PARTIDA" << endl;
		cout << "-------------------------" << endl;
		parado = false;
		
		
	}
	else if(juego.estado == GANADOR) {//Si hemos ganado
		cout << "ENHORABUENA!!" << endl;
		cout << "-------------------" << endl;
		parado = false;
		
	}
	else {//Si hemos parado el juego(fila 0, col 0)
		parado = true;
	}
	
}


bool estado(tJuego& juego) {
	return juego.estado;//Devuelve el estado(Para respetar la privacidad)
}