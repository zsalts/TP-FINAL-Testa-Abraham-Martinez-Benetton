#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "clientes.h"
#include "habitaciones.h"

int main()
{
    int opcion;
    stHabitaciones ArregloHabitaciones[100];
    int validosHab = 0;

    Pila pedidosServicio;
    inicpila(&pedidosServicio);

    char menuComidas[4][20] = {"Continental", "Buffet", "Americano", "Ingles"};

    do
    {
        system("cls");
        printf("\n========================================\n");
        printf("      SISTEMA DE GESTION DE HOTEL       \n");
        printf("========================================\n");
        printf("1. Gestion de Clientes\n");
        printf("2. Gestion de Habitaciones\n");
        printf("3. Gestion de Personal y Atencion\n");
        printf("4. Ver Menu de Comidas (Arreglo Estatico)\n");
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
            menuHabitaciones(ArregloHabitaciones, &validosHab,  pedidosServicio);
            break;
        // case 3: menuEmpleados(&pedidosServicio); break;
        case 4:
            printf("\n--- MENU DE COMIDAS DISPONIBLES ---\n");
            for (int i = 0; i < 4; i++)
            {
                printf("%d. %s\n", i + 1, menuComidas[i]);
            }
            break;
        case 0:
            printf("\nSaliendo del sistema. Hasta luego!\n");
            break;
        default:
            printf("\nOpcion invalida.\n");
        }
    }
    while (opcion != 0);

    return 0;
}
