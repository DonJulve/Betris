// Autores: Alejandro Benedi y Javier Julve
// NIP:     843826              840710
#include <iostream>
using namespace std;

// CONSTANTES Y TIPOS

// Máximo múmero de filas y columnas del tablero
const int MAXDIM = 100;

// Máximo número de piezas en la entrada
const int MAXENTRADA = 3000;

// Tamaño en número de cuadrados de cada pieza
const int TAMPIEZA = 4;

// Número de piezas definidas
const int PIEZASDEF = 5;

// Códigos numéricos de colores
const int NEGRO    = 40;
const int ROJO     = 41;
const int VERDE    = 42;
const int AMARILLO = 43;
const int AZUL     = 44;
const int MAGENTA  = 45;
const int CIAN     = 46;
const int BLANCO   = 47;

const int TRANSPARENTE = 8;

// Tipo tablero
struct tpTablero{
    int nfils; // Número de filas del tablero
    int ncols; // Número de columnas del tablero
    int matriz[MAXDIM][MAXDIM]; // El valor de cada celda indica el numero de
                                // la pieza de entrada que la ocupa.
                                // Si el valor es -1 entonces la casilla está vacía.
                                // Las coordenadas de la casilla de arriba a la izquierda son (0,0)
};


// Tipo pieza (color y forma)
struct tpPieza{
   int color;              // Código de color de la pieza
   int forma[TAMPIEZA][2]; // Coordenadas de los cuadrados de la pieza
                           // El primer valor es el número de fila, el segundo es el número de columna
                           // La coordenada de arriba a la izquierda es (0,0)              
     // Ejemplo de forma: [[0,0], [0,1], [1,0], [2,0] ] es la pieza  XX 
     //                                                              X 
     //                                                              X
};

// Definición de piezas existentes. El número de cada pieza es su posición en este vector
const tpPieza vPiezas[PIEZASDEF] = {
    {AZUL,     {{0,0}, {0,1}, {0,2}, {0,3}}}, // 0  XXXX
    {VERDE,    {{0,0}, {1,0}, {2,0}, {3,0}}}, // 1  X
                                              //    X
                                              //    X
                                              //    X
    {ROJO,     {{0,0}, {0,1}, {1,0}, {2,0}}}, // 2  XX
                                              //    X
                                              //    X
    {CIAN,     {{0,0}, {0,1}, {0,2}, {1,2}}}, // 3  XXX
                                              //      X
    {AMARILLO, {{0,0}, {0,1}, {1,0}, {1,1}}}  // 4  XX
                                              //    XX
};


// FUNCIONES

// Pre: true
// Post: Todas las componentes de tablero.matriz son -1 (casilla vacía)
void inicializarTablero(tpTablero &tablero); 

// Pre: vEntrada contiene los números de las piezas que entran y tablero contiene el estado actual 
//      del tablero, en el que pueden estar colocadas algunas de dichas piezas 
// Post: Se ha mostrado el tablero por pantalla (cada pieza se ha dibujado con su color)
void mostrarTablero(const tpTablero & tablero, const int vEntrada[MAXENTRADA]);

// Pre: En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: Si las piezas colocadas completan al menos objetivo filas sin huecos,
//       entonces
//           devuelve el número de piezas colocadas, en vSalida las columnas en las que se han colocado
//           las piezas y el tablero con las piezas colocadas
//       si no devuelve -1
int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo=0);

// Pre:  filSel es un parametro obtenido a partir de la funcion, celda de referencia, la cual indica la fila en la que podemos colocar una pieza.
// Post: La funcion nos dice si existe un hueco disponible en esa casilla para la pieza que estamos intentando colocar.
bool esColocable(const tpTablero tablero, const int vEntrada[MAXENTRADA], const int n, const int col, const int filSel);

// Pre:  col es un parametro que se modifica en la funcion recursiva "buscaSolucion" y que indica la columna en 
//       la que nos situamos actualmente
// Post: la funcion ha buscado entre todas las filas, yendo de arriba a abajo hasta que encuentra una ficha colocada y 
//       entonces elije la fila de arriba pues esa es la que esta vacia para poder colocar la pieza.A esta fila de hay 
//       que sumarle la altura de la pieza y asi devuelve la fila que se corresponde a la celda de referencia para crear la pieza 
//       (la colocada arriba a la izquierda)
int celdaReferencia(tpTablero tablero, const int vEntrada[MAXENTRADA], const int n, const int col);

// Pre:  filSel contine la fila de referencia, que se corresponde a la celda de mas arriba a la izquierda de la pieza, 
//       y por la cual se va a crear la pieza. Tablero.matriz contiene las n primeras piezas y vEntrada[] tiene el tipo 
//       de las piezas.
// Post: La función ha colocado cuadro a cuadro la ficha almacenada en vEntrada empezando desde arriba a la izquierda y 
//       acabando en la posición de más abajo a la derecha.
void colocarPieza(tpTablero & tablero, const int vEntrada[MAXENTRADA], const int n, const int col, const int filSel);

// Pre:  filSel contine la fila de referencia, que se corresponde a la celda de mas arriba a la izquierda de la pieza, 
//       y por la cual se va a crear la pieza. Tablero.matriz contiene las n primeras piezas y vEntrada[] tiene el tipo 
//       de las piezas.
// Post: La función ha eliminado cuadro a cuadro la ficha almacenada en vEntrada empezando desde arriba a la izquierda y 
//       acabando en la posición de más abajo a la derecha.
void quitarPieza(tpTablero & tablero, const int vEntrada[MAXENTRADA], const int n, const int col, const int filSel);

// Pre:  En la matriz tablero.matriz estam colocadas las n primeras piezas.Objetivo contien las filas que tiene que 
//       estar completas para que lo que hay en el tablero en ese sea una solucion valida.
// Post: Devuelve "true" si el numero de filas completas es igual o superior a objetivo y devulve "false" si el numero
//       de filas completas es menor estricto que objetivo.
bool esSol(tpTablero tablero, int objetivo);

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
void introducirDatos(tpTablero& tablero,int argc, char* argv[], int& objetivo, int& retardo, int vEntrada[]);

// Pre:  En los componente de vEntrada[] se encuentra todas la piezas que se quiere colocar
// Post: Escribe en pantalla el siguinte mensaje:
//                      "Entrada (número de piezas): " <Escribe todas la piezas, quitando el -1>
//                      "Numero de piezas colocadas " <Si se ha encontrado solución escribira el numero de piezas colocadas>
//                      "Salida(numero de columnas)" <Si se ha encontrado solucion se escribira la columna en la que 
//                                                      se han colocado las columnas. Si no hay solucion no escribira nada>
void escribirSolucion(const int vEntrada[], int numPiezas, const int salida[]);

// Pre: vEntrada contiene las piezas a colocar en el tablero, para la activación de esta función la primera 
//      componente del vector debe ser un número negativo.
// Post: La función ha generado aleatoriamente tantas piezas como la cantidad en valor absoluto de la componente negativa 
//       del vEntrada.
void piezasAleatorias(const int numPiezas, int vEntrada[]);

// Pre: Retardo es un parametro que indica los milisegundos de descanso que haga el programa por cada iteración de "mostrarTablero".
// Post: La función genera un "descanso" en la ejecucion de "mostrarTablero" por cada iteración realizada, resultado en un
//       retardo entre cada "mostrarTablero" que se ejecute.
void mostrarTableroDelay(const tpTablero& tablero, const int vEntrada[], const int retardo);

//////////////////////////////////////////////////////////////////////////////
// Salida con atributos
//
// La cadena "<ESC>[{attr1};...;{attrn}m" sirve para asignar atributos a la salida
//
// Por ejemplo: 
//    cout << "\033[34;42m" << "Hola" << "\033[0m";
// escribe en azul con fondo verde, y después resetea los atributos

// Lista de atributos estándar:
// 0 Resetea todos los atributos
// 1 brillante
// 2 tenue
// 4 subrayado
// 5 parpadeo
// 7 invertido
// 8 oculto

// Colores de primer plano
// 30 negro
// 31 rojo
// 32 verde
// 33 amarillo
// 34 azul
// 35 magenta
// 36 cian
// 37 blanco

// Colores de fondo
// 40 negro
// 41 rojo
// 42 verde
// 43 amarillo
// 44 azul
// 45 magenta
// 46 cian
// 47 blanco

