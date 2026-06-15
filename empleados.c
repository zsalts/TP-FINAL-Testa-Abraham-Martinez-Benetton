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