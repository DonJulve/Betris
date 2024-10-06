# Autores: Alejandro Benedi y Javier Julve
# NIP:     843826              840710
# Definición de macros
CC = g++
CPPFLAGS = -std=c++11      #opciones de compilación
LDFLAGS =                      #opciones de linkado
RM = rm -f                     #comando para borrar ficheros

all: mainB
#-----------------------------------------------------------
# Compilacion
main.o: main.cpp
	${CC} main.cpp -c ${CPPFLAGS}
# Linkeado
mainB: betris.o main.o
	${CC} main.o betris.o -o mainB ${CPPFLAGS}
	
betris.o: betris.cpp betris.hpp
	${CC} betris.cpp -c ${CPPFLAGS}

#-----------------------------------------------------------	
# LIMPIEZA
clean:
	${RM} betris.o main.o
