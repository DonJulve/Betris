// Autores: Alejandro Benedi y Javier Julve
// NIP:     843826              840710
#include <iostream>
#include <unistd.h>
#include <time.h>
#include "betris.hpp"

using namespace std;

// Pre: true
// Post: Todas las componentes de tablero.matriz son -1 (casilla vacía)
void inicializarTablero(tpTablero &tablero){

    for (int i = 0; i < tablero.nfils; i++){
        for ( int j = 0;j < tablero.ncols; j++){
            tablero.matriz[i][j] = -1;
        }
    }
}

// Pre: Retardo es un parametro que indica los milisegundos de descanso que haga el programa por cada iteración de "mostrarTablero".
// Post: La función genera un "descanso" en la ejecucion de "mostrarTablero" por cada iteración realizada, resultado en un
//       retardo entre cada "mostrarTablero" que se ejecute.
void mostrarTableroDelay(const tpTablero& tablero, const int vEntrada[], const int retardo){

    if(retardo >= 0){

        mostrarTablero(tablero, vEntrada);
        usleep(retardo*1000);                      //funcion de retardo
    }
}

// Pre: vEntrada contiene los números de las piezas que entran y tablero contiene el estado actual 
//      del tablero, en el que pueden estar colocadas algunas de dichas piezas 
// Post: Se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero & tablero, const int vEntrada[MAXENTRADA]){
    
    cout << endl;

    for (int i = 0; i < tablero.nfils; i++){
        for ( int j = 0; j < tablero.ncols; j++){
            
            if(tablero.matriz[i][j] != -1){

                int indPieza = vEntrada[tablero.matriz[i][j]];
                cout << "\033[" << vPiezas[indPieza].color << "m \033[0m";
            }
            else{

                cout << "\033[" << TRANSPARENTE << "m \033[0m";
            }
        }
        cout << endl;
    }

}

// Pre:  filSel es un parametro obtenido a partir de la funcion, celda de referencia, la cual indica la fila en la que podemos colocar una pieza.
// Post: La funcion nos dice si existe un hueco disponible en esa casilla para la pieza que estamos intentando colocar.
bool esColocable(const tpTablero tablero, const int vEntrada[MAXENTRADA], const int n, const int col, const int celRef){

    int indPieza = vEntrada[n];

    int ind = 0;
    bool hueco = true;

    while(ind < TAMPIEZA && hueco){

        int fila = vPiezas[indPieza].forma[ind][0];           
        int columna = vPiezas[indPieza].forma[ind][1];

        if(tablero.matriz[celRef + fila][col + columna] != -1){
            hueco = false;
        }

        ind++;
    }

    return hueco;

}

// Pre:  col es un parametro que se modifica en la funcion recursiva "buscaSolucion" y que indica la columna en 
//       la que nos situamos actualmente
// Post: la funcion ha buscado entre todas las filas, yendo de arriba a abajo hasta que encuentra una ficha colocada y 
//       entonces elije la fila de arriba pues esa es la que esta vacia para poder colocar la pieza.A esta fila de hay 
//       que sumarle la altura de la pieza y asi devuelve la fila que se corresponde a la celda de referencia para crear la pieza 
//       (la colocada arriba a la izquierda)
int celdaReferencia(tpTablero tablero, const int vEntrada[MAXENTRADA], const int n, const int col){

    int hueco = 0;  

    while(tablero.matriz[hueco][col] == -1 && hueco < tablero.nfils){
        hueco++;                                // Esta variable hace referencia a la fila en la que no hay pieza en la columna <col>
    }
    hueco--;

    int indPieza = vEntrada[n];                 // Pilla el tipo de pieza que hay en <vEntrada>
    int filaReferencia;
    
    if(hueco != 0){

        if(indPieza != 3){
            filaReferencia = hueco - vPiezas[indPieza].forma[3][0];       // <hueco> tenia la fila en la que no hay pieza colocada y se le resta                                                                     // la fila mas alejada del punto de referencia para colocar o quitar la pieza
        }
        else{
            filaReferencia = hueco;
        }
    }
    else{
        filaReferencia = 0;
    }
    
    return filaReferencia;                    // Devolvemos el la fila por la cual podemos colocar o quitar la pieza
}

// Pre:  filSel contine la fila de referencia, que se corresponde a la celda de mas arriba a la izquierda de la pieza, 
//       y por la cual se va a crear la pieza. Tablero.matriz contiene las n primeras piezas y vEntrada[] tiene el tipo 
//       de las piezas.
// Post: La función ha colocado cuadro a cuadro la ficha almacenada en vEntrada empezando desde arriba a la izquierda y 
//       acabando en la posición de más abajo a la derecha.
void colocarPieza(tpTablero & tablero, const int vEntrada[MAXENTRADA], const int n, const int col, const int celRef){

    int indPieza = vEntrada[n];

    int ind = 0;

    while(ind < TAMPIEZA){

        int fila = vPiezas[indPieza].forma[ind][0];
        int columna = vPiezas[indPieza].forma[ind][1];

        tablero.matriz[celRef + fila][col + columna] = n;

        ind++;
    }

}

// Pre:  filSel contine la fila de referencia, que se corresponde a la celda de mas arriba a la izquierda de la pieza, 
//       y por la cual se va a crear la pieza. Tablero.matriz contiene las n primeras piezas y vEntrada[] tiene el tipo 
//       de las piezas.
// Post: La función ha eliminado cuadro a cuadro la ficha almacenada en vEntrada empezando desde arriba a la izquierda y 
//       acabando en la posición de más abajo a la derecha.
void quitarPieza(tpTablero & tablero, const int vEntrada[MAXENTRADA], const int n, const int col,const int celRef){
   
    int indPieza = vEntrada[n];
    
    int ind = 0;

    while(ind < TAMPIEZA){

        int fila =  vPiezas[indPieza].forma[ind][0];
        int columna =  vPiezas[indPieza].forma[ind][1];

        tablero.matriz[celRef + fila][col + columna] = -1;

        ind++;
    }
}

// Pre:  En la matriz tablero.matriz estam colocadas las n primeras piezas.Objetivo contien las filas que tiene que 
//       estar completas para que lo que hay en el tablero en ese sea una solucion valida.
// Post: Devuelve "true" si el numero de filas completas es igual o superior a objetivo y devulve "false" si el numero
//       de filas completas es menor estricto que objetivo.
bool esSol(tpTablero tablero, int objetivo){
    
    int FilRecorrida = 0;
    int ColRecorrida = 0;
    int contCol = 0;
    int contFila = 0;
    
    while(tablero.nfils > FilRecorrida){
        while(tablero.ncols > ColRecorrida){
            
            if(tablero.matriz[FilRecorrida][ColRecorrida] != -1){
                contCol++;
            }
            ColRecorrida++;
        }

        if(contCol==tablero.ncols){
            contFila++;
        }
        
        contCol = 0;
        ColRecorrida = 0;
        FilRecorrida++;
    }

    if(contFila >= objetivo){
        return true;
    }
    else{
        return false;
    }
}

// Pre:  En los componente de vEntrada[] se encuentra todas la piezas que se quiere colocar
// Post: Escribe en pantalla el siguinte mensaje:
//                      "Entrada (número de piezas): " <Escribe todas la piezas, quitando el -1>
//                      "Numero de piezas colocadas " <Si se ha encontrado solución escribira el numero de piezas colocadas>
//                      "Salida(numero de columnas)" <Si se ha encontrado solucion se escribira la columna en la que 
//                                                      se han colocado las columnas. Si no hay solucion no escribira nada>
void escribirSolucion(const int vEntrada[], int numPiezas, const int salida[]){

    int indice = 0;

    cout << "Entrada (número de piezas): ";
    while(vEntrada[indice] != -1){
        cout << vEntrada[indice] << " ";
        indice++;
    }
    cout << endl;

    cout << "Numero de piezas colocadas: " << numPiezas << endl;

    cout << "Salida (numero de columnas): ";
    for(int i = 0; i < numPiezas; i++){
        cout << salida[i] << " ";
    }
    cout << endl;
}

// Pre: En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces
//           devuelve el número de piezas colocadas, en vSalida las columnas en las que se han colocado
//           las piezas y el tablero con las piezas colocadas
//       si no devuelve -1
int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo){

    int col = 0;
    int retorno = -1;
    
    if(esSol(tablero, objetivo)){
        return n;
    }
    else if(vEntrada[n] == -1){
        return -1;
    }
    else{
        while( col < tablero.ncols && retorno == -1){

            int celRef = celdaReferencia(tablero, vEntrada, n, col);

            if(esColocable(tablero, vEntrada, n, col, celRef)){

                colocarPieza(tablero, vEntrada, n, col, celRef);
                vSalida[n] = col;

                mostrarTableroDelay(tablero, vEntrada, retardo);


                retorno = buscaSolucion(tablero, vEntrada, vSalida, objetivo, n+1, retardo);

                if(retorno == -1){
                    quitarPieza(tablero, vEntrada, n, col, celRef);
                    vSalida[n] = 0;
                }
                
            }

            col++;

        }
    
    
    return retorno;
    }
}

// Pre: vEntrada contiene las piezas a colocar en el tablero, para la activación de esta función la primera 
//      componente del vector debe ser un número negativo.
// Post: La función ha generado aleatoriamente tantas piezas como la cantidad en valor absoluto de la componente negativa 
//       del vEntrada.
void piezasAleatorias(const int numPiezas, int vEntrada[]){
    
    time_t seed = time(nullptr);
    srand(seed);

    for(int i = 0; i < numPiezas; i++){
        vEntrada[i] = 0 + rand() % (4 - 0 + 1);
    }

    vEntrada[numPiezas] = -1;
}


// Pre:  argc es el numero de palabras usadas para ejecutar el programa principal, argv es un vector que almacena todos 
//       los datos que se usarán en el programa. Todos los datos a excepción del vector vEntrada se pasan por referencia 
//       puesto que así no debemos solicitarlos en el propio main del programa. vEntrada además almacenará todos los índices 
//       de las piezas que serán usadas posteriormente.
// Post: La función ha transformado todos los datos intoducidos a variables del tipo entero para poder trabajar con ellas, siguiendo el órden:
//          1º: filas.
//          2º: columnas.
//          3º: objetivo.
//          4º: retardo.
//          5º hasta n-ésimo: indice de las piezas a colocar.
void introducirDatos(tpTablero& tablero,int argc, char* argv[], int& objetivo, int& retardo, int vEntrada[]){
    
    tablero.nfils = atoi(argv[1]);
    tablero.ncols = atoi(argv[2]);
    objetivo = atoi(argv[3]);
    retardo = atoi(argv[4]);

    int N1 = atoi(argv[5]);

    if(N1 < 0){
        piezasAleatorias(-N1, vEntrada);
    }
    else{
         
        int ind = 0;
        for(int i = 5; i < argc; i++){

            vEntrada[ind] = atoi(argv[i]);
            ind++;
        }
    } 
}


