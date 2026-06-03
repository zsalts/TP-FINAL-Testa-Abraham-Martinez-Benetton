#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#include <time.h>
#include "habitaciones.h"

void cargarHabitacion(stHabitaciones habitaciones[], int *validos)
{
    stHabitaciones aux;

    printf("Numero de habitacion: ");
    scanf("%d", &aux.numHab);

    printf("Capacidad: ");
    scanf("%d", &aux.capacidad);

    printf("Disponibilidad (1=Disponible, 0=Ocupada): ");
    scanf("%d", &aux.disponibilidad);

    printf("Desayuno (1=Si, 0=No): ");
    scanf("%d", &aux.desayuno);

    fflush(stdin);
    printf("Servicios: ");
    fgets(aux.servicios, 100, stdin);

    habitaciones[*validos] = aux;
    (*validos)++;
}

void mostrarUnaHabitacion(stHabitaciones habitacion)
{
    printf("\nNumero: %d", habitacion.numHab);
    printf("\nCapacidad: %d", habitacion.capacidad);
    printf("\nDisponibilidad: %d", habitacion.disponibilidad);
    printf("\nDesayuno: %d", habitacion.desayuno);
    printf("\nServicios: %s", habitacion.servicios);
    printf("\n------------------------\n");
}

void mostrarHabitaciones(stHabitaciones habitaciones[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        mostrarUnaHabitacion(habitaciones[i]);
    }
}

int buscarHabitacion(stHabitaciones habitaciones[], int validos, int numero)
{
    int i = 0;

    while(i < validos && habitaciones[i].numHab != numero)
    {
        i++;
    }

    if(i == validos)
    {
        i = -1;
    }

    return i;
}

void modificarHabitacion(stHabitaciones habitaciones[], int validos)
{
    int numero;
    int pos;

    printf("Ingrese el numero de habitacion a modificar: ");
    scanf("%d", &numero);

    pos = buscarHabitacion(habitaciones, validos, numero);

    if(pos != -1)
    {
        printf("Nueva capacidad: ");
        scanf("%d", &habitaciones[pos].capacidad);

        printf("Nueva disponibilidad (1=Disponible, 0=Ocupada): ");
        scanf("%d", &habitaciones[pos].disponibilidad);

        printf("Desayuno (1=Si, 0=No): ");
        scanf("%d", &habitaciones[pos].desayuno);

        fflush(stdin);
        printf("Servicios: ");
        fgets(habitaciones[pos].servicios, 100, stdin);

        printf("\nHabitacion modificada correctamente.\n");
    }
    else
    {
        printf("\nLa habitacion no existe.\n");
    }
}

void mostrarDisponibles(stHabitaciones habitaciones[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        if(habitaciones[i].disponibilidad == 1)
        {
            mostrarUnaHabitacion(habitaciones[i]);
        }
    }
}

void mostrarNoDisponibles(stHabitaciones habitaciones[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        if(habitaciones[i].disponibilidad == 0)
        {
            mostrarUnaHabitacion(habitaciones[i]);
        }
    }
}
