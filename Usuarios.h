

#ifndef Usuario_h
#define Usuario_h
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "ListaJuegos.h"



const int MAXIMO = 5;
struct tUsuario {
	std::string id;
	tListaJuegos lista;
};
typedef tUsuario* tUsuarioPtr;
typedef tUsuarioPtr tArray[MAXIMO];
struct tListaUsuarios { // ordenada crecientemente por id
	tArray usuarios;
	int contador = 0;
};


void cargar(tListaUsuarios& lista, std::string nombre, bool& carga);
void guardar(const tListaUsuarios& lista, std::string nombre);
int buscar(const tListaUsuarios& lista, std::string id);
int nuevoUsuario(tListaUsuarios& lista, std::string id);
void eliminar(tListaUsuarios& lista, int pos);
void mostrar(const tListaUsuarios& lista); // para depuración
void liberar(tListaUsuarios& lista);
void actualizaJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego, const tJuego& juego);
tJuego dameJuegoUsuario(const tListaUsuarios& lista, int posUsuario, int posJuego);
void eliminarJuegoUsuario(tListaUsuarios& lista, int posUsuario, int posJuego);




int eligeJuegoUsuario(const tListaUsuarios& lista, int indUsuario);
tJuego dameJuegoPrivacidad(const tListaUsuarios& lista, int posUsuario, int posJuego);


#endif
