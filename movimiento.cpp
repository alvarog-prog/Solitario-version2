//Álvaro Gil Arjona
//Víctor Verdú García
//Grupo: LAB 11 G12
#include "checkML.h"
#include "movimiento.h"
#include "tablero.h"
#include"juego.h"
using namespace std;







//Funciones privadas del módulo movimiento

bool movimientosPosibles(const tTablero& tablero, int fila, int col, tMovimientoLista& listaMov);  // privado
string enumToString(tDireccion dir);
tMovimiento moviendo(tDireccion dir, int fila, int col);
tMovimiento eligeMovimiento(const tMovimientoLista& listaMov);


tMovimiento eligeMovimiento(const tMovimientoLista& listaMov) {//Muestra en pantalla las diferentes opciones que tenemos para movernos.
	cout << " " << endl;
	cout << "Puedes realizar mas de un movimiento" << endl;
	int respuesta;
	cout << "PULSE ENTER PARA VER EL MENU DE MOVIMIENTOS" << endl;
	char boton;
	boton = getchar();
	boton = getchar();
	cout << "----<<<<----Bienvenido al menu de movimientos---->>>>----" << endl;
	cout << "Los movimientos disponibles que tienes para realizar son: " << endl;
	for (int i = 0; i < listaMov.contador; i++) {
		cout << i + 1 << "-" << " " << enumToString(listaMov.posibles[i].dir) << endl;
	}

	do {
		cout << "Elige el movimiento que quieres realizar:" << endl;
		cin >> respuesta;
		if (respuesta < 1 || respuesta > listaMov.contador) {
			cout << "Eleccion no valida" << endl;
			cout << "PULSE ENTER PARA ELEGIR OTRO MOVIMIENTO" << endl;
			char boton;
			boton = getchar();
			boton = getchar();

		}
	} while (respuesta < 1 || respuesta > listaMov.contador);

	return listaMov.posibles[respuesta - 1];

}

bool movimientosPosibles(const tTablero& tablero, int fila, int col, tMovimientoLista& listaMov) {//Devuelve una lista con los movimientos que se pueden realizar.
	tMovimiento celda;
	bool valido = false;
	listaMov.contador = 0;
	for (tDireccion dir = ARRIBA; dir <= IZQUIERDA; dir = tDireccion(dir + 1)) {
		celda = moviendo(dir, fila, col);//que recorra todas las direcciones y así compruebe hacia cuales podría desplazarse.
		if (valida(tablero, celda.filaSaltada, celda.colSaltada) && dameCelda(tablero, celda.filaSaltada, celda.colSaltada) == FICHA &&
			valida(tablero, celda.filaDestino, celda.colDestino) && dameCelda(tablero, celda.filaDestino, celda.colDestino) == VACIA) {
			listaMov.posibles[listaMov.contador] = celda;//Guardamos el movimiento en la lista.
			listaMov.contador++;
			valido = true;

		}
		if (listaMov.contador == 0) {//No hay ningún movimiento
			valido = false;
		}
	}
	return valido;
}



tMovimiento moviendo(tDireccion dir, int fila, int col) {//Todos los movimientos que se pueden realizar en el juego.
	tMovimiento mov;
	mov.dir = dir;

	if (dir == ARRIBA) {
		mov.filaDestino = fila - 2;
		mov.filaSaltada = fila - 1;
		mov.colDestino = col;//Las columnas se mantienen
		mov.colSaltada = col;
	}
	else if (dir == ABAJO) {
		mov.filaDestino = fila + 2;
		mov.filaSaltada = fila + 1;
		mov.colDestino = col;//Las columnas se mantienen
		mov.colSaltada = col;
	}
	else if (dir == DERECHA) {
		mov.colDestino = col + 2;
		mov.colSaltada = col + 1;
		mov.filaDestino = fila;//Las filas se mantienen.
		mov.filaSaltada = fila;
	}
	else { //IZQUIERDA
		mov.colDestino = col - 2;
		mov.colSaltada = col - 1;
		mov.filaDestino = fila;//Las filas se mantienen.
		mov.filaSaltada = fila;
	}
	return mov;
}


string enumToString(tDireccion dir) {
	switch (dir) {//En vez de aparecer números, ponga la dirección.
	case ARRIBA:
		return "ARRIBA";
	case ABAJO:
		return "ABAJO";

	case IZQUIERDA:
		return "IZQUIERDA";

	case DERECHA:
		return "DERECHA";
	}
}








tMovimiento leeMovimiento(const tTablero& tablero, int& fila, int& col, bool& fin) {
	bool ok = false;
	fin = false;
	tMovimientoLista mov;
	tMovimiento x;
	x.dir = ARRIBA;
	tJuego juego;
	while (!ok) {
		cout << "Selecciona una ficha para mover (Fila  Columna)[0  0 para detener el juego]: "; cin >> fila; cout << " "; cin >> col;//Solicitamos al usuario una fila y una columna.
		fila--;//Le restamos uno para que lea bien la posición en el array.
		col--;
		if (fila != -1 && col != -1) {//Si no hemos puesto 0  0 que continue el juego
			juego.estado = JUGANDO;// Cambiar porque me meto en modulos
			if (eleccionValida(tablero, fila, col)) {
				if (movimientosPosibles(tablero, fila, col, mov)) {
					if (mov.contador == 1) {
						x = mov.posibles[0];//Si solo hay un movimiento para realiza, lo realice directamente.

					}
					else {
						x = eligeMovimiento(mov);
					}
					ok = true;
				}
				else {
					cout << "La ficha en la posicion " << fila + 1 << " - " << col + 1 << " no puede moverse" << endl;
					cout << "No hay movimientos disponibles" << endl;
					cout << "PULSE ENTER PARA MOVER OTRA FICHA" << endl;
					char boton;
					boton = getchar();
					boton = getchar();
					ok = false;
				}
			}
			else {
				cout << "La posicion " << fila + 1 << " - " << col + 1 << " no tiene ficha o no es posicion valida" << endl;
				cout << "No puedes realizar ningun movimiento" << endl;
				cout << "PULSE ENTER PARA MOVER OTRA FICHA" << endl;
				char boton;
				boton = getchar();
				boton = getchar();
			}
		}
		else {//Hemos pedido que pare el juego(fila 0, col 0)
			cout << "El juego se ha parado" << endl;
			ok = true;
			fin = true;
		}
	}
	return x;
}



bool fichaBloqueada(const tTablero& tablero, int fila, int col) {//Comprueba si puedo o no realizar algún movimiento.
	tMovimiento mov;
	bool puede = true;
	tDireccion dir = ARRIBA;
	while (dir <= IZQUIERDA && puede) {//Recorra todas las direcciones mientras puede sea true.
		mov = moviendo(dir, fila, col);
		if (dameCelda(tablero, mov.filaSaltada, mov.colSaltada) == FICHA && dameCelda(tablero, mov.filaDestino, mov.colDestino) == VACIA) {
			puede = false;//Si la posición saltada tiene ficha y la destino está vacía, puedes mover.(Sales del bucle porque ya sabemos que podemos hacer al menos un movimiento)
		}
		else {
			puede = true;
		}
		dir = tDireccion(dir + 1);//Siguiente dirección.
	}
	return puede;
}




void movimientoFicha(tTablero& tablero, int fila, int col, const tMovimiento& mov) {//Realiza el movimiento.
	ponCelda(tablero, fila, col, tablero.celdas[fila][col]);
	ponCelda(tablero, fila, col, VACIA);//Ponga la posición en la que nos situábamos como vacía.
	ponCelda(tablero, mov.filaSaltada, mov.colSaltada, VACIA);//La posición que saltamos por encima como vacía.
	ponCelda(tablero, mov.filaDestino, mov.colDestino, FICHA);//La posición a la que nos desplazamos la complete con una ficha.
}

bool eligeMovimientoInverso(const tTablero& tablero, int fila, int col, tMovimiento& mov) {//Crea una lista con los movimientos posibles de realizar.
	bool existe = false;
	tMovimientoLista lista;
	lista.contador = 0;
	for (tDireccion dir = ARRIBA; dir <= IZQUIERDA; dir = tDireccion(dir + 1)) {//Recorremos todas las direcciones.
		mov = moviendo(dir, fila, col);//Que el movimiento compruebe cada dirección.
		if (mov.filaSaltada < numFilas(tablero) - 1 && mov.filaDestino < numFilas(tablero) - 1 && mov.colSaltada < numColumnas(tablero) - 1 && mov.colDestino < numColumnas(tablero) - 1 && mov.filaSaltada >= 0
			&& mov.filaDestino >= 0 && mov.colSaltada >= 0 && mov.colDestino >= 0) {//La fila y columna saltada y destino estén dentro del tablero.
			if (dameCelda(tablero, mov.filaSaltada, mov.colSaltada) != FICHA &&//La fila  y columna saltada y la destino no tengan ficha.
				dameCelda(tablero, mov.filaDestino, mov.colDestino) != FICHA) {
				lista.posibles[lista.contador] = mov;//Metemos el movimiento en la lista.
				lista.contador++;
				existe = true;
			}
		}
	}
	if (lista.contador == 0) {//No hay movimientos inversos.
		existe = false;
	}
	else {//En el caso que haya, que eliga aleatoriamente cual realizar.
		int contNuevo = rand() % lista.contador;
		mov = lista.posibles[contNuevo];//Lo meta de nuevo, en la posición del nuevo contador.
		existe = true;
	}
	return existe;
}

void realizaMovimientoInverso(tTablero& tablero, int fila, int col, const tMovimiento& mov) {//Realiza el movimiento inverso.
	ponCelda(tablero, fila, col, VACIA);//La posición en la que estábamos la ponga vacía.
	ponCelda(tablero, mov.filaSaltada, mov.colSaltada, FICHA);//La posición a la que saltamos por encima la rellene con ficha.
	ponCelda(tablero, mov.filaDestino, mov.colDestino, FICHA);//La posición a la que nos desplazamos la rellene con ficha.
}