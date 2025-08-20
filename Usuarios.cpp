//Álvaro Gil Arjona
//Víctor Verdú García
//Grupo: LAB 11 G12
#include "checkML.h"
#include "juego.h"
#include "movimiento.h"
#include "tablero.h"
#include "Usuarios.h"
using namespace std;



void cargar(tListaUsuarios& lista, string nombre, bool& carga){
	ifstream archivo;
	
	archivo.open(nombre);
	if (!archivo.is_open()) {
		cout << "El archivo no puede abrirse" << endl;//Si el archivo no puede abrirse
		carga = false;
	}
	else {
		carga = true;
		archivo >> lista.contador;//Leemos contador
		for (int i = 0; i < lista.contador; i++) {
			lista.usuarios[i] = new tUsuario;//Reservamos espacio para un usuario en c
			archivo >> lista.usuarios[i]->id;//Leemos 
			cargar(lista.usuarios[i]->lista, archivo);
		}
	}
}



void liberar(tListaUsuarios& lista) {
	for (int i = 0; i < lista.contador; i++) {
		liberar(lista.usuarios[i]->lista);
		delete lista.usuarios[i];
	}
	lista.contador = 0;
}



void mostrar(const tListaUsuarios& lista) {//Mostramos los usuarios
    for (int i = 0; i < lista.contador; i++) {
        cout << lista.usuarios[i]->id << endl;
		mostrar(lista.usuarios[i]->lista);//Para mostrar la lista
    }

}


int buscar(const tListaUsuarios& lista, string id) {
	int pos;
	bool ok = false;
	int i = 0;
	while(i < lista.contador && !ok){//Si el usuario no existe se devuelve -1
		if (lista.usuarios[i]->id != id) {
			pos = -1;
		}
		else {//Si el usuario escrito por pantalla coincide, se devuelve su posición.
			pos = i;
			ok = true;
		}
		i++;
	}
	return pos;//Devolvemos la posición
}





void actualizaJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego, const tJuego& juego) {
	actualizaPrivacidad(lista.usuarios[posUsuario]->lista, juego, posJuego);//Llama a la función con la intención de respetar privacidad
}



void eliminar(tListaUsuarios& lista, int pos) {
	liberar(lista.usuarios[pos]->lista);
	delete lista.usuarios[pos];
	lista.contador--;
	for (int i = pos; i < lista.contador; i++) {
		lista.usuarios[i] = lista.usuarios[i + 1];//Desplazamos
	}

	
}

void guardar(const tListaUsuarios& lista, string nombre) {
	ofstream archivo;
	tTablero tablero;
	tListaJuegos numJuegos;

	archivo.open(nombre);
	if (!archivo.is_open()) {
		cout << "El archivo no puede abrirse" << endl;//Si el archivo no se abre
	}
	else {
		archivo << lista.contador << endl;//Leemos el contador
		for (int i = 0; i < lista.contador; i++) {
			archivo << lista.usuarios[i]->id << endl;//Leemos el usuario
			guardar(lista.usuarios[i]->lista, archivo);
		}

		archivo.close();//Cerramos el archivo
		cout << endl;
	}
}

int nuevoUsuario(tListaUsuarios& lista, string id) {
	tUsuario user;
	int x = 0;
	if (lista.contador == MAXIMO) {//Si la lista de usuarios esta completa, no puede crearse un nuevo usuario(devuelve -1)
		cout << "La lista esta completa" << endl;
		x = -1;
	}
	else {//Creamos el nuevo usuario
		user.id = id;//Introducimos el usuario en el struct
		lista.usuarios[lista.contador] = new tUsuario(user);
		x = lista.contador;//Devolvemos el contador
		lista.contador++;//Y lo aumentamos ya que hay un usuario más.
	}
	return x;
}

void eliminarJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego) {
	eliminar(lista.usuarios[posUsuario]->lista, posJuego);//llama a eliminar de lista
}


int eligeJuegoUsuario(const tListaUsuarios& lista, int indUsuario) {
	return eligeJuego(lista.usuarios[indUsuario]->lista);//Llamamos a elige juego para respetar la privacidad
}


tJuego dameJuegoPrivacidad(const tListaUsuarios& lista, int posUsuario, int posJuego) {
	return dameJuego(lista.usuarios[posUsuario]->lista, posJuego);//Llamamos a dameJuego para respetar la privacidad
}
	