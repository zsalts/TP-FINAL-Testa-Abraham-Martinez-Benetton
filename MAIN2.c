#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#include <time.h>
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
void mostrarServicios(stHabitaciones habitaciones[], int validos);
void mostrarDesayuno(stHabitaciones habitaciones[], int validos);
void cambiarDisponibilidad(stHabitaciones habitaciones[], int validos);

int main()
{
    stHabitaciones habitaciones[100];
    int validos = 0;
    int opcion;

    do
    {
        printf("\n--- MENU HABITACIONES ---\n");
        printf("1. Cargar habitacion\n");
        printf("2. Mostrar habitaciones\n");
        printf("3. Modificar habitacion\n");
        printf("4. Mostrar disponibles\n");
        printf("5. Mostrar no disponibles\n");
        printf("6. Mostrar servicios de una habitacion\n");
        printf("7. Mostrar desayuno\n");
        printf("8. Cambiar disponibilidad\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            cargarHabitacion(habitaciones, &validos);
            break;

        case 2:
            mostrarHabitaciones(habitaciones, validos);
            break;

        case 3:
            modificarHabitacion(habitaciones, validos);
            break;

        case 4:
            mostrarDisponibles(habitaciones, validos);
            break;

        case 5:
            mostrarNoDisponibles(habitaciones, validos);
            break;

        case 6:
            mostrarServicios(habitaciones, validos);
            break;

        case 7:
            mostrarDesayuno(habitaciones, validos);
            break;

        case 8:
            cambiarDisponibilidad(habitaciones, validos);
            break;

        case 0:
            printf("\nSaliendo...\n");
            break;

        default:
            printf("\nOpcion invalida.\n");
        }

    } while(opcion != 0);

    return 0;
}

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

void mostrarServicios(stHabitaciones habitaciones[], int validos)
{
    int numero;
    int pos;

    printf("Ingrese el numero de habitacion: ");
    scanf("%d", &numero);

    pos = buscarHabitacion(habitaciones, validos, numero);

    if(pos != -1)
    {
        printf("\nServicios de la habitacion %d:\n", habitaciones[pos].numHab);
        printf("%s\n", habitaciones[pos].servicios);
    }
    else
    {
        printf("\nLa habitacion no existe.\n");
    }
}

void mostrarDesayuno(stHabitaciones habitaciones[], int validos)
{
    int numero;
    int pos;

    printf("Ingrese el numero de habitacion: ");
    scanf("%d", &numero);

    pos = buscarHabitacion(habitaciones, validos, numero);

    if(pos != -1)
    {
        printf("\nHabitacion %d\n", habitaciones[pos].numHab);

        if(habitaciones[pos].desayuno == 1)
        {
            printf("Incluye desayuno.\n");
        }
        else
        {
            printf("No incluye desayuno.\n");
        }
    }
    else
    {
        printf("\nLa habitacion no existe.\n");
    }
}

void cambiarDisponibilidad(stHabitaciones habitaciones[], int validos)
{
    int numero;
    int pos;

    printf("Ingrese el numero de habitacion: ");
    scanf("%d", &numero);

    pos = buscarHabitacion(habitaciones, validos, numero);

    if(pos != -1)
    {
        if(habitaciones[pos].disponibilidad == 1)
        {
            habitaciones[pos].disponibilidad = 0;
            printf("\nLa habitacion ahora esta ocupada.\n");
        }
        else
        {
            habitaciones[pos].disponibilidad = 1;
            printf("\nLa habitacion ahora esta disponible.\n");
        }
    }
    else
    {
        printf("\nLa habitacion no existe.\n");
    }
}
