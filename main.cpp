
#include <iostream>
#include <string>
#include <cstdlib>
#include "Usuarios.h"
#include "checkML.h"
using namespace std;



string solicitaNombreFichero();
string solicitaNombreFicheroGuardar();


string solicitaNombreUsuario();


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool cargado = false;
	string nombre, nombreGUardar, id;
	char respuesta;
	int posicion, user;
	int victorias = 0, derrotas = 0, juegoEleccion;
	tJuego juego;
	ifstream fichero;
	ofstream guarda;
	tListaUsuarios lista;
	tListaJuegos lJuegos;
	bool fin, carga, parado;
	int j, busqueda;
	srand(time(NULL)); //Genera los números aleatorios
	int pasos = 0;
	cout << "----------BIENVENIDO AL SOLITARIO----------" << endl;
	do {
		nombre = solicitaNombreFichero();//Solicitamos el nombre del fichero
		cargar(lista, nombre, carga);
	} while (!carga);//Se repita hasta que cargue
			do {
				cout << "---LISTA DE USUARIOS---" << endl;
				mostrar(lista);//Mostramos lista usuarios, con sus juegos.
				id = solicitaNombreUsuario();//Solicitamos el nombre de un Usuario
				if (id != "FIN") {//Cuando el usuario no sea FIN
					posicion = buscar(lista, id);//Buscar nos devuelve la posicion del usuario que buscamos(si no existe devuelve -1)

					if (posicion == -1) {//No existe
						cout << "El usuario seleccionado no existe" << endl;
						user = nuevoUsuario(lista, id);//Creamos el nuevo usuario, con el id introducido por pantalla
						if (user == -1) {//Si nuevo usuario devuelve -1, significa que la lista esta completa(MAXÍMO 5 USUARIOS)
							cout << "No pueden crearse mas usuarios" << endl;
							cout << "PULSE ENTER PARA VISUALIZAR LISTA USUARIOS" << endl;
							char boton;
							boton = getchar();
							boton = getchar();
						}
						else {//Hemos podido crear el nuevo usuario
							generar(juego, pasos);//Generamos un juego aleatorio para dicho usuario
							insertar(lista.usuarios[user]->lista, juego);//Lo insertamos en la lista
							jugar(juego, parado);//Jugamos
						}
					}
					else {//Si el usuario que introducimos existe
						do {
							cout << "Tus juegos sin finalizar..." << endl;
							for (int i = 0; i < lista.usuarios[buscar(lista, id)]->lista.contador; i++) {//Nos muestra los juegos que nos faltan por jugar
								cout << "Juego " << i + 1 << endl;
								mostrar(lista.usuarios[buscar(lista, id)]->lista.juegos[i]);
							}
							busqueda = buscar(lista, id);

							j = eligeJuegoUsuario(lista,busqueda);//Elegimos un juego de los que tenemos posibles
							juego = dameJuegoPrivacidad(lista, busqueda, j);
							jugar(juego,parado);//Jugamos
							if (parado) {//Si hemos parado el juego(fila 0, col 0)
								actualizaJuegoUsuario(lista, busqueda, j, juego);//Nos actualice el juego con los movimientos que hayamos hecho
							}
							else {//Si el estado es BLOQUEO o GANADOR eliminamos el juego del usuario
								eliminarJuegoUsuario(lista, busqueda, j);//eliminamos juego
							}
						} while (lista.usuarios[busqueda]->lista.contador != 0);
						cout << "Usuario " << id << " ya no tiene juegos" << endl;//Si al usuario no le quedan juegos, eliminamos dicho usuario.
						cout << "Eliminando Usuario..." << endl;
						eliminar(lista, busqueda);//Eliminamos usuario
					}	
				}
			} while (id != "FIN");
			nombreGUardar = solicitaNombreFicheroGuardar();//Si decidimos acabar el juego, guardamos nuestra lista en un archivo.
			guardar(lista, nombreGUardar);//Guardamos
			cout << "Guardado en " << nombreGUardar << endl;
			liberar(lista);//Liberamos la memoria dinámica
	return 0;
}



string solicitaNombreFichero() {
	string nombre;
	cout << "Nombre del fichero: ";
	cin >> nombre; // se introduce nombre, sin extensión
	nombre = nombre + ".txt";
	return nombre;
}
string solicitaNombreFicheroGuardar() {
	string nombre;
	cout << "Nombre del fichero donde quieres guardar: ";
	cin >> nombre; // se introduce nombre, sin extensión
	nombre = nombre + ".txt";
	return nombre;
}
string solicitaNombreUsuario() {
	string id;
	cout << "DAME UN ID DE USUARIO O FIN PARA TERMINAR" << endl;
	cin >> id;
	return id;
}

