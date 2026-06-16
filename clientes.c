#include "clientes.h"

int buscarClienteRecursivo(FILE *archi, int idBusqueda)
{
    stCliente c;
    if (fread(&c, sizeof(stCliente), 1, archi) == 0)
    {
        return 0;
    }
    if (c.idCliente == idBusqueda)
    {
        return 1;
    }
    return buscarClienteRecursivo(archi, idBusqueda);
}

void altaCliente()
{
    stCliente nuevoCliente;
    printf("Ingrese el ID del cliente: ");
    scanf("%d", &nuevoCliente.idCliente);
    FILE *archiBusqueda = fopen("clientes.dat", "rb");
    if (archiBusqueda != NULL)
    {

        if (buscarClienteRecursivo(archiBusqueda, nuevoCliente.idCliente) == 1)
        {
            printf("\nERROR: El ID ya se encuentra registrado.\n");
            fclose(archiBusqueda);
            return;
        }
        fclose(archiBusqueda);
    }

    fflush(stdin);

    printf("Ingrese el nombre completo: ");
    while(getchar() != '\n');
    gets(nuevoCliente.nombreCompleto);

    printf("Ingrese el email: ");
    scanf("%s", nuevoCliente.email);

    printf("Ingrese un password: ");
    scanf("%s", nuevoCliente.password);

    nuevoCliente.estado = 1;

    FILE *archiGuardar = fopen("clientes.dat", "ab");
    if (archiGuardar != NULL)
    {
        fwrite(&nuevoCliente, sizeof(stCliente), 1, archiGuardar);
        fclose(archiGuardar);
        printf("\nCliente registrado con exito.\n");
    }
    else
    {
        printf("\nError al abrir el archivo para guardar.\n");
    }
}

void bajaCliente()
{
    int idBaja, flag = 0;
    stCliente c;
    FILE *archi = fopen("clientes.dat", "r+b");
    if (archi != NULL)
    {
        printf("Ingrese el ID del cliente a dar de baja: ");
        scanf("%d", &idBaja);
        while (fread(&c, sizeof(stCliente), 1, archi) > 0 && flag == 0)
        {
            if (c.idCliente == idBaja && c.estado == 1)
            {
                c.estado = 0;
                fseek(archi, sizeof(stCliente) * -1, SEEK_CUR);
                fwrite(&c, sizeof(stCliente), 1, archi);
                flag = 1;
                printf("\nCliente dado de baja exitosamente.\n");
            }
        }
        if (flag == 0)
            printf("\nCliente no encontrado o ya estaba dado de baja.\n");
        fclose(archi);
    }
}

void modificarCliente()
{
    int idMod, flag = 0;
    stCliente c;
    FILE *archi = fopen("clientes.dat", "r+b");
    if (archi != NULL)
    {
        printf("Ingrese el ID del cliente a modificar: ");
        scanf("%d", &idMod);
        while (fread(&c, sizeof(stCliente), 1, archi) > 0 && flag == 0)
        {
            if (c.idCliente == idMod && c.estado == 1)
            {
                fflush(stdin);
                printf("Nuevo nombre: ");
                while(getchar() != '\n');
                gets(c.nombreCompleto);
                fseek(archi, sizeof(stCliente) * -1, SEEK_CUR);
                fwrite(&c, sizeof(stCliente), 1, archi);
                flag = 1;
                printf("\nCliente modificado exitosamente.\n");
            }
        }
        fclose(archi);
    }
}

void consultarCliente()
{
    int idConsulta, flag = 0;
    stCliente c;
    FILE *archi = fopen("clientes.dat", "rb");
    if (archi != NULL)
    {
        printf("Ingrese el ID del cliente a consultar: ");
        scanf("%d", &idConsulta);
        while (fread(&c, sizeof(stCliente), 1, archi) > 0 && flag == 0)
        {
            if (c.idCliente == idConsulta && c.estado == 1)
            {
                printf("\n--- DATOS DEL CLIENTE ---\n");
                printf("ID: %d\nNombre: %s\nEmail: %s\n", c.idCliente, c.nombreCompleto, c.email);
                flag = 1;
            }
        }
        if (flag == 0)
            printf("\nCliente no encontrado.\n");
        fclose(archi);
    }
}

void listarClientesSeleccion()
{
    FILE *archi = fopen("clientes.dat", "rb");
    if (archi == NULL)
        return;

    int validos = 0;
    stCliente c;
    while (fread(&c, sizeof(stCliente), 1, archi) > 0)
    {
        if (c.estado == 1)
            validos++;
    }

    if (validos == 0)
    {
        printf("\nNo hay clientes activos para listar.\n");
        fclose(archi);
        return;
    }

    stCliente *arregloClientes = (stCliente *)malloc(validos * sizeof(stCliente));
    rewind(archi);
    int i = 0;
    while (fread(&c, sizeof(stCliente), 1, archi) > 0)
    {
        if (c.estado == 1)
        {
            arregloClientes[i] = c;
            i++;
        }
    }
    fclose(archi);

    int posMenor;
    stCliente aux;
    for (i = 0; i < validos - 1; i++)
    {
        posMenor = i;
        for (int j = i + 1; j < validos; j++)
        {
            if (arregloClientes[j].idCliente < arregloClientes[posMenor].idCliente)
            {
                posMenor = j;
            }
        }
        aux = arregloClientes[i];
        arregloClientes[i] = arregloClientes[posMenor];
        arregloClientes[posMenor] = aux;
    }

    printf("\n--- LISTADO DE CLIENTES (Orden ID) ---\n");
    for (i = 0; i < validos; i++)
    {
        printf("ID: %d | Nombre: %s | Email: %s\n", arregloClientes[i].idCliente, arregloClientes[i].nombreCompleto, arregloClientes[i].email);
    }
    free(arregloClientes);
}

void menuClientes() {
    int opcion;

    do {
        system("cls");
        printf("========================================\n");
        printf("           GESTION DE CLIENTES          \n");
        printf("========================================\n");
        printf("1. Alta de Cliente\n");
        printf("2. Baja Logica de Cliente\n");
        printf("3. Modificar Cliente\n");
        printf("4. Consultar Cliente por ID\n");
        printf("5. Listar Clientes (Seleccion)\n");
        printf("0. Volver\n");
        printf("========================================\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        system("cls");

        switch(opcion) {
            case 1:
                printf("\n--- ALTA DE CLIENTE ---\n");
                altaCliente();
                break;
            case 2:
                printf("\n--- BAJA LOGICA DE CLIENTE ---\n");
                bajaCliente();
                break;
            case 3:
                printf("\n--- MODIFICAR CLIENTE ---\n");
                modificarCliente();
                break;
            case 4:
                printf("\n--- CONSULTA DE CLIENTE ---\n\n");
                consultarCliente();
                break;
            case 5:
                printf("\n--- LISTA DE CLIENTES ---\n\n");
                listarClientesSeleccion();
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
