// Autores: Alejandro Benedi y Javier Julve
// NIP:     843826              840710
#include <iostream>
#include <unistd.h>
#include "betris.hpp"

using namespace std;

int main(int argc, char* argv[]){

    tpTablero tablero;
    
    int objetivo;
    int vEntrada[MAXENTRADA];
    int vSalida[MAXENTRADA];
    int retardo = 0;

    introducirDatos(tablero, argc, argv, objetivo, retardo, vEntrada);

    inicializarTablero(tablero);

    int numPiezasColocadas = buscaSolucion(tablero, vEntrada, vSalida, objetivo, 0, retardo);

    mostrarTablero(tablero, vEntrada);
    escribirSolucion(vEntrada, numPiezasColocadas, vSalida);

    return 0;
}
