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
    for (int i = 0; i < validos; i++)
    {
        mostrarUnaHabitacion(habitaciones[i]);
    }
}

int buscarHabitacion(stHabitaciones habitaciones[], int validos, int numero)
{
    int i = 0;

    while (i < validos && habitaciones[i].numHab != numero)
    {
        i++;
    }

    if (i == validos)
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

    if (pos != -1)
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
    for (int i = 0; i < validos; i++)
    {
        if (habitaciones[i].disponibilidad == 1)
        {
            mostrarUnaHabitacion(habitaciones[i]);
        }
    }
}

void mostrarNoDisponibles(stHabitaciones habitaciones[], int validos)
{
    for (int i = 0; i < validos; i++)
    {
        if (habitaciones[i].disponibilidad == 0)
        {
            mostrarUnaHabitacion(habitaciones[i]);
        }
    }
}

void menuHabitaciones(stHabitaciones Habitaciones[], int *validos, Pila *pedidos)
{
    int opcion;
    int numeroBuscado, pos;
    do
    {
        printf("\n========================================\n");
        printf("       GESTION DE HABITACIONES          \n");
        printf("========================================\n");
        printf("1. Cargar una nueva habitaicon\n");
        printf("2. Mostrar TODAS las habitaciones\n");
        printf("3. Mostrar habitaciones DISPONIBLES\n");
        printf("4. Mostrar habitaciones NO DISPONIBLES\n");
        printf("5. Modificar una habitacion\n");
        printf("6. Buscar y mostrar una habitacion\n");
        printf("----------------------------------------\n");
        printf("7. Solicitar Room Service (Apilar pedido)\n");
        printf("0. Salir\n");
        printf("========================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("\n--- ALTA DE HABITACION ---\n");
            cargarHabitacion(Habitaciones, validos);
            break;
        case 2:
            printf("\n--- TODAS LAS HABITACIONES ---\n");
            if (*validos > 0)
                mostrarHabitaciones(Habitaciones, *validos);
            else
                printf("\nNo hay habitaciones cargadas.\n");
            break;
        case 3:
            printf("\n--- HABITACIONES DISPONIBLES ---\n");
            if (*validos > 0)
                mostrarDisponibles(Habitaciones, *validos);
            else
                printf("\nNo hay habitaciones cargadas.\n");
            break;
        case 4:
            printf("\n--- HABITACIONES OCUPADAS ---\n");
            if (*validos > 0)
                mostrarNoDisponibles(Habitaciones, *validos);
            else
                printf("\nNo hay habitaciones cargadas.\n");
            break;
        case 5:
            printf("\n--- MODIFICAR HABITACION ---\n");
            if (*validos > 0)
                modificarHabitacion(Habitaciones, *validos);
            else
                printf("\nNo hay habitaciones cargadas.\n");
            break;
        case 6:
            printf("\n--- CONSULTAR HABITACION ---\n");
            if (*validos > 0)
            {
                printf("Ingrese el numero de habitacion a buscar: ");
                scanf("%d", &numeroBuscado);
                pos = buscarHabitacion(Habitaciones, *validos, numeroBuscado);
                if (pos != -1)
                    mostrarUnaHabitacion(Habitaciones[pos]);
                else
                    printf("\nLa habitacion %d no existe.\n", numeroBuscado);
            }
            else
            {
                printf("\nNo hay habitaciones cargadas.\n");
            }
            break;
        case 7:
            printf("\n--- NUEVO PEDIDO DE ROOM SERVICE ---\n");
            printf("Ingrese el numero de habitacion que solicita servicio: ");
            scanf("%d", &numeroBuscado);
            apilar(pedidos, numeroBuscado);
            printf("Pedido de la habitacion %d agregado a la fila de trabajo.\n", numeroBuscado);
            break;
        case 0:
            printf("\nSaliendo del menu de habitaciones...\n");
            break;
        default:
            printf("\nOpcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}
