#include "empleados.h"
const char empleados[] = "empleado.dat";
void cargarEmpleados()
{
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "ab");
    if (buffer != NULL)
    {
        printf("ingrese numero de legajo");
        scanf("%i", &aux.legajo);
        fflush(stdin);
        printf("ingrese el nombre del empleado");
        fgets(aux.nombre, 100, stdin);
        printf("ingrese el puesto: ");
        fgets(aux.puesto, 100, stdin);
        aux.estado = 1;
        fwrite(&aux, sizeof(stEmpleados), 1, buffer);
        fclose(buffer);
        printf("\nEmpleado cargado correctamente. \n");
    }
    else
    {
        printf("no abrio el archivo");
    }
}

void bajaEmpleado()
{
    int legajoBuscado, flag = 0;
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "rb");
    if (buffer != NULL)
    {
        printf("\ningrese el legado del empleado que quiera dar de baja");
        scanf("%i", &legajoBuscado);

        while (fread(&aux, sizeof(stEmpleados), 1, buffer) > 0 && flag == 0)
        {
            if (aux.legajo == legajoBuscado && aux.estado == 1)
            {
                aux.estado = 0;
                fseek(buffer, sizeof(stEmpleados) * -1, SEEK_CUR);
                fwrite(&aux, sizeof(stEmpleados), 1, buffer);
                flag = 1;
                printf("el empleado fue dado de baja");
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("\nel archivo no existe");
    }
}

void modificarEmpleado()
{
    int legajoBuscado, flag = 0;
    stEmpleados aux;
    FILE *buffer = fopen(empleados, "rb");
    if (buffer != NULL)
    {
        printf("\ningrese el legado del empleado que quiera modificar");
        scanf("%i", &legajoBuscado);
        while (fread(&aux, sizeof(stEmpleados), 1, buffer) > 0 && flag == 0)
        {
            if (aux.legajo == legajoBuscado && flag == 1)
            {
                printf("ingrese el nuevo puesto: ");
                fgets(aux.puesto, 100, stdin);
                fseek(buffer, sizeof(stEmpleados) * -1, SEEK_CUR);
                fwrite(&aux, sizeof(stEmpleados), 1, buffer);
                flag == 1;
            }
        }
        fclose(buffer);
    }else
    {
        printf("archivo no abrio");
    }

}

void menuEmpleados(Pila pedidos) {
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
                printf("\n--- LISTA DE EMPLEADOS ---\n");
                //4mostrarEmpleados();
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
                printf("\n--- CONSULTA DE EMPLEADO ---\n");
                //consultarEmpleado();
                break;
            case 6:
                printf("\n--- ATENDIENDO PEDIDO ---\n");
                if (!pilavacia(&pedidos)) {
                    printf("Un empleado esta yendo a atender a la habitacion: %d\n", desapilar(&pedidos));
                } else {
                    printf("Excelente! No hay servicios pendientes.\n");
                }
                break;
            case 7:
                printf("\n--- PEDIDOS PENDIENTES DE ROOM SERVICE ---\n");
                if (!pilavacia(&pedidos)) {
                    mostrar(&pedidos);
                } else {
                    printf("La pila de pedidos esta vacia. Todo al dia.\n");
                }
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
