
#include "checkML.h"
#include "juego.h"
#include "Usuarios.h"
#include "ListaJuegos.h"
using namespace std;




void cargar(tListaJuegos& lista, ifstream& file) {
	file >> lista.contador;//Leemos contador(número de juegos)
	while (lista.contador < lista.capacidad) {//si el contador es menor que la capacidad, aumenta capacidad
		lista.capacidad += DELTA;
	}
	lista.juegos = new tJuego[MAX];//Reservamos memoria
	for (int i = 0; i < lista.contador; i++) {
		cargar(lista.juegos[i], file);
	}
	
}


void insertar(tListaJuegos& lista,  tJuego& juego) {//+
	if (lista.contador == lista.capacidad) {//Si la capacidad y el contador coinciden, aumentamos capacidad
		lista.capacidad = +DELTA;
		tJuego* aux = new tJuego[lista.capacidad];
		for (int i = 0; i < lista.contador; i++) {
			aux[i] = lista.juegos[i];
		}
		lista.juegos = aux;
	}
	tJuego* aux2 = new tJuego[lista.capacidad];
	aux2 = &juego;//Apuntamos a la dirección de juego
	lista.juegos[lista.contador] = juego;
	lista.contador++;

}



void guardar(const tListaJuegos& lista, ofstream& file) {
	tTablero tablero;
	int num;
	file << lista.contador << endl;
	for (int i = 0; i < lista.contador; i++) {
		guardar(lista.juegos[i], file);
	}

}


void liberar(tListaJuegos& lista) {
	delete[] lista.juegos;
	lista.juegos = NULL;//Apuntamos a nulo
	lista.capacidad = 0;//Capacidad es 0
	lista.contador = 0;//Contador es 0
}


void mostrar(const tListaJuegos& lista) {//Mostramos la lista de juegos de cada usuario.
	cout << "Numero de juegos: " << lista.contador << endl;//Número de juegos.
	for (int i = 0; i < lista.contador; i++) {
		cout << "Juego" << i + 1 << endl;
		mostrar(lista.juegos[i].tablero);
	}
}



tJuego dameJuego(const tListaJuegos& lista, int pos) {
	return lista.juegos[pos];//Devuelve un juego
}



void eliminar(tListaJuegos& lista, int pos) {//+
	if (pos != lista.contador) {
		lista.juegos[pos] = lista.juegos[lista.contador - 1];//Desplazamos 
		lista.contador--;//Restamos uno al contador

	}
	if (lista.contador < lista.capacidad - 2 * DELTA) {
		disminuir(lista);//Disminuimos la capacidad
	}
}

void disminuir(tListaJuegos& lista) {
	tJuegoPtr aux = lista.juegos;
	lista.capacidad -= DELTA;
	lista.juegos = new tJuego[lista.capacidad];
	for (int i = 0; i < lista.contador; i++)
		lista.juegos[i] = aux[i];
	delete[] aux;
}





int eligeJuego(tListaJuegos& lista) {
	tJuego juego;
	int pos, eleccion;
	string id;
	int pasos = 0;
	if (lista.contador != 0) {//Si no quedan juegos lo hacemos aleatorio

		do {
			cout << "Elige un juego para jugar [ 0 para jugar un nuevo juego]: " << endl;
			cin >> eleccion;
		}while (eleccion > lista.contador + 1 || eleccion < -1);
			if (eleccion == 0) {
				generar(juego, pasos);
				insertar(lista, juego);
			}
			else if (eleccion != 0 && eleccion != -1) {
				cout << "Has elegido jugar el juego " << eleccion << endl;
				eleccion--;
			}
	}
	else {
		generar(juego, pasos);
		insertar(lista, juego);//Lo insertamos en la lista
	}
	return eleccion;
}

void actualizaPrivacidad(tListaJuegos& lista, const tJuego& juego, int posJuego) {
	lista.juegos[posJuego] = juego;//Actualiza el juego

}
