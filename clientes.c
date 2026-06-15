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
    FILE *archi = fopen("clientes.dat", "ab");
    if (archi != NULL)
    {
        printf("Ingrese el ID del cliente: ");
        scanf("%d", &nuevoCliente.idCliente);

        rewind(archi);
        if (buscarClienteRecursivo(archi, nuevoCliente.idCliente) == 1)
        {
            printf("\nERROR: El ID ya se encuentra registrado.\n");
            fclose(archi);
            return;
        }

        fflush(stdin);
        printf("Ingrese el nombre completo: ");
        while(getchar() != '\n');
        gets(nuevoCliente.nombreCompleto);
        printf("Ingrese el email: ");
        while(getchar() != '\n');
        gets(nuevoCliente.email);
        printf("Ingrese un password: ");
        while(getchar() != '\n');
        gets(nuevoCliente.password);

        nuevoCliente.estado = 1;

        fseek(archi, 0, SEEK_END);
        fwrite(&nuevoCliente, sizeof(stCliente), 1, archi);
        fclose(archi);
        printf("\nCliente registrado con exito.\n");
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
            if (strcmpi(arregloClientes[j].nombreCompleto, arregloClientes[posMenor].nombreCompleto) < 0)
            {
                posMenor = j;
            }
        }
        aux = arregloClientes[i];
        arregloClientes[i] = arregloClientes[posMenor];
        arregloClientes[posMenor] = aux;
    }

    printf("\n--- LISTADO DE CLIENTES (Orden Alfabetico) ---\n");
    for (i = 0; i < validos; i++)
    {
        printf("ID: %d | Nombre: %s | Email: %s\n", arregloClientes[i].idCliente, arregloClientes[i].nombreCompleto, arregloClientes[i].email);
    }
    free(arregloClientes);
}

void menuClientes()
{
    int opcion;
    do
    {
        printf("\n--- MENU CLIENTES ---\n");
        printf("1. Alta de Cliente\n");
        printf("2. Baja Logica de Cliente\n");
        printf("3. Modificar Cliente\n");
        printf("4. Consultar Cliente por ID\n");
        printf("5. Listar Clientes (Seleccion)\n");
        printf("0. Volver\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            altaCliente();
            break;
        case 2:
            bajaCliente();
            break;
        case 3:
            modificarCliente();
            break;
        case 4:
            consultarCliente();
            break;
        case 5:
            listarClientesSeleccion();
            break;
        }
    } while (opcion != 0);
}
