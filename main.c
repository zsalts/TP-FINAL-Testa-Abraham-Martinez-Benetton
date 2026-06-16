#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "clientes.h"
#include "habitaciones.h"
#include "empleados.h"

int main()
{
    Pila pilaPedidos;
    inicpila(&pilaPedidos);
    int opcion;
    stHabitaciones ArregloHabitaciones[100];
    int validosHab = 0;

    do
    {
        system("cls");
        printf("\n========================================\n");
        printf("      SISTEMA DE GESTION DE HOTEL       \n");
        printf("========================================\n");
        printf("1. Gestion de Clientes\n");
        printf("2. Gestion de Habitaciones\n");
        printf("3. Gestion de Personal y Atencion\n");
        printf("0. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        system("cls");
        switch (opcion)
        {
        case 1:
            menuClientes();
            break;
        case 2:
            menuHabitaciones(ArregloHabitaciones, &validosHab, &pilaPedidos);
            break;
        case 3:
            menuEmpleados(&pilaPedidos);
            break;
            break;
        case 0:
            printf("\nSaliendo del sistema. Hasta luego!\n");
            break;
        default:
            printf("\nOpcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}
