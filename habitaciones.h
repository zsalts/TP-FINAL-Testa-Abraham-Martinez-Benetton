#ifndef HABITACIONES_H_INCLUDED
#define HABITACIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

typedef struct{
    int numHab;
    int capacidad;
    int disponibilidad;
    int desayuno;
    char servicios[100];
} stHabitaciones;

typedef struct{
    char empleado[30];
    char claveDeAcceso[30];
} stPersonal;

//Prototipado
void cargarHabitacion(stHabitaciones habitaciones[], int *validos);
void mostrarUnaHabitacion(stHabitaciones habitacion);
void mostrarHabitaciones(stHabitaciones habitaciones[], int validos);
int buscarHabitacion(stHabitaciones habitaciones[], int validos, int numero);
void modificarHabitacion(stHabitaciones habitaciones[], int validos);
void mostrarDisponibles(stHabitaciones habitaciones[], int validos);
void mostrarNoDisponibles(stHabitaciones habitaciones[], int validos);
void menuHabitaciones(stHabitaciones habitaciones[], int *validos, Pila *p);

#endif
