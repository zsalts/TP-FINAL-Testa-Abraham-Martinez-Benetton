#include "empleados.h"
#include "comidas.h"

const char empleados[] = "empleado.dat";

void cargarEmpleados()
{
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "ab");
    if (buffer != NULL)
    {
        printf("Ingrese numero de legajo: ");
        scanf("%i", &aux.legajo);

        fflush(stdin);
        printf("Ingrese el nombre del empleado: ");
        fgets(aux.nombre, 50, stdin);
        aux.nombre[strcspn(aux.nombre, "\n")] = 0;
        printf("Ingrese el puesto: ");
        fgets(aux.puesto, 50, stdin);
        aux.puesto[strcspn(aux.puesto, "\n")] = 0;

        aux.estado = 1;
        fwrite(&aux, sizeof(stEmpleados), 1, buffer);
        fclose(buffer);
        printf("\nEmpleado cargado correctamente. \n");
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

void mostrarEmpleados()
{
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "rb");
    int cont = 0;
    if (buffer != NULL)
    {
        while (fread(&aux, sizeof(stEmpleados), 1, buffer) > 0)
        {
            if (aux.estado == 1)
            {
                printf("Legajo: %-4d | Nombre: %-20s | Puesto: %s\n", aux.legajo, aux.nombre, aux.puesto);
                cont++;
            }
        }
        fclose(buffer);
        if (cont == 0) printf("No hay empleados activos en el sistema.\n");
    }
    else
    {
        printf("No hay registros de empleados creados aun.\n");
    }
}

void bajaEmpleado()
{
    int legajoBuscado, flag = 0;
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "r+b");
    if (buffer != NULL)
    {
        printf("\nIngrese el legajo del empleado que quiera dar de baja: ");
        scanf("%i", &legajoBuscado);

        while (fread(&aux, sizeof(stEmpleados), 1, buffer) > 0 && flag == 0)
        {
            if (aux.legajo == legajoBuscado && aux.estado == 1)
            {
                aux.estado = 0;
                fseek(buffer, (long)sizeof(stEmpleados) * -1, SEEK_CUR);
                fwrite(&aux, sizeof(stEmpleados), 1, buffer);
                flag = 1;
                printf("El empleado fue dado de baja exitosamente.\n");
            }
        }
        fclose(buffer);
        if (flag == 0) printf("No se encontro un empleado activo con ese legajo.\n");
    }
    else
    {
        printf("\nEl archivo no existe.\n");
    }
}

void modificarEmpleado()
{
    int legajoBuscado, flag = 0;
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "r+b");
    if (buffer != NULL)
    {
        printf("\nIngrese el legajo del empleado que quiera modificar: ");
        scanf("%i", &legajoBuscado);
        while (fread(&aux, sizeof(stEmpleados), 1, buffer) > 0 && flag == 0)
        {
            if (aux.legajo == legajoBuscado && aux.estado == 1) // CORREGIDO: validamos legajo y estado activo
            {
                fflush(stdin);
                printf("Ingrese el nuevo puesto: ");
                fgets(aux.puesto, 50, stdin);
                aux.puesto[strcspn(aux.puesto, "\n")] = 0;

                fseek(buffer, (long)sizeof(stEmpleados) * -1, SEEK_CUR);
                fwrite(&aux, sizeof(stEmpleados), 1, buffer);
                flag = 1;
                printf("El puesto fue modificado correctamente.\n");
            }
        }
        fclose(buffer);
        if (flag == 0) printf("No se encontro el empleado o esta inactivo.\n");
    }
    else
    {
        printf("El archivo no se pudo abrir.\n");
    }
}

void consultarEmpleado()
{
    int legajoBuscado, flag = 0;
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "rb");
    if (buffer != NULL)
    {
        printf("Ingrese el legajo del empleado a consultar: ");
        scanf("%d", &legajoBuscado);
        while (fread(&aux, sizeof(stEmpleados), 1, buffer) > 0 && flag == 0)
        {
            if (aux.legajo == legajoBuscado && aux.estado == 1)
            {
                printf("\n--- EMPLEADO ENCONTRADO ---\n");
                printf("Legajo: %d\nNombre: %s\nPuesto: %s\n", aux.legajo, aux.nombre, aux.puesto);
                flag = 1;
            }
        }
        fclose(buffer);
        if (flag == 0) printf("No se encontro ningun empleado activo con ese legajo.\n");
    }
    else
    {
        printf("No hay base de datos de empleados aun.\n");
    }
}

void menuEmpleados(Pila *pedidos) {
    int opcion;

    do {
        system("cls");
        printf("========================================\n");
        printf("       GESTION DE PERSONAL Y TAREAS     \n");
        printf("========================================\n");
        printf("1. Alta de empleado\n");
        printf("2. Listar personal activo\n");
        printf("3. Baja logica de empleado\n");
        printf("4. Modificar puesto de empleado\n");
        printf("5. Consultar empleado por legajo\n");
        printf("----------------------------------------\n");
        printf("6. Atender proximo Room Service (Desapilar)\n");
        printf("7. Ver servicios pendientes (Mostrar Pila)\n");
        printf("8. Administrar Carta de Comidas (Restaurante)\n");
        printf("0. Volver\n");
        printf("========================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        system("cls");

        switch(opcion) {
            case 1:
                printf("\n--- ALTA DE EMPLEADO ---\n");
                cargarEmpleados();
                break;
            case 2:
                printf("\n--- LISTA DE EMPLEADOS ACTIVOS ---\n\n");
                mostrarEmpleados();
                break;
            case 3:
                printf("\n--- BAJA DE EMPLEADO ---\n");
                bajaEmpleado();
                break;
            case 4:
                printf("\n--- MODIFICAR EMPLEADO ---\n");
                modificarEmpleado();
                break;
            case 5:
                printf("\n--- CONSULTA DE EMPLEADO ---\n\n");
                consultarEmpleado();
                break;
            case 6:
                printf("\n--- ATENDIENDO PEDIDO ---\n\n");
                if (!pilavacia(pedidos)) {
                    int numHab = desapilar(pedidos);
                    printf("Un empleado esta yendo a atender a la habitacion: %d\n", numHab);

                    procesarPedidoComida(numHab);
                } else {
                    printf("Excelente! No hay servicios pendientes.\n");
                }
                break;
            case 7:
                printf("\n--- PEDIDOS PENDIENTES DE ROOM SERVICE ---\n\n");
                if (!pilavacia(pedidos)) {
                    mostrar(pedidos);
                } else {
                    printf("La pila de pedidos esta vacia. Todo al dia.\n");
                }
                break;
            case 8:
                menuAdministrarComidas();
                break;
            case 0:
                printf("\nVolviendo al menu principal...\n");
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }

        if(opcion != 0) {
            printf("\n");
            system("pause");
        }

    } while (opcion != 0);
}
