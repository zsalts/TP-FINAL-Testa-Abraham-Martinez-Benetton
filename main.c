#include <stdio.h>
#include <stdlib.h>
void loginempleado();
void logincliente();
void registrarempleado();
void registrarcliente();
typedef struct
{
    int contrasenia;
    int usuario;
    char nombreyapellido[30];
    int edad;
    char sector[30];

} stempleado;
typedef struct
{
    int contrasenia;
    int usuario;
    char nombreyapellido[30];
    int documento;
    int edad;
    char genero[20]; // Femenino o Masculino
} stcliente;

int main()
{
    int opcion;

    do
    {
        printf("--------MENU PRINCIPAL DEL HOTEL--------");
        printf("\n1. login Empleado");
        printf("\n2. login cliente");
        printf("\n3. registrar empleado");
        printf("\n4. registrar cliente");
        printf("\n0. salir del programa\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            loginempleado();
            break;
        case 2:
            logincliente();
            break;
        case 3:
            registrarempleado();
            break;
        case 4:
            registrarcliente();
            break;
        case 0:
            printf("saliendo del programa...");
            break;
        default:
            printf("Ingrese una opcion valida :)");
            break;
        }
    } while (opcion != 0);
}
stempleado cargarUnEmpleado()
{
    stempleado A;

    printf("\nIngrese el ID de usuario: ");
    scanf("%d", &A.usuario);

    printf("\nIngrese la contrasenia: ");
    scanf("%d", &A.contrasenia);

    printf("\nIngrese el nombre del empleado. Maximo 30 caracteres: ");
    fflush(stdin);
    gets(A.nombreyapellido);

    printf("\nIngrese la edad (entre 18 y 99): ");
    scanf("%d", &A.edad);

    while (A.edad < 18 || A.edad > 99)
    {
        printf("\nEdad erronea (debe ser entre 18 y 99), ingrese nuevamente: ");
        fflush(stdin);
        scanf("%d", &A.edad);
    }

    printf("\nIngrese el sector de trabajo: ");
    fflush(stdin);
    gets(A.sector);

    return A;
}
stcliente cargarUnCliente()
{
    stcliente A;

    printf("\nIngrese el ID de usuario: ");
    scanf("%d", &A.usuario);

    printf("\nIngrese la contrasenia: ");
    scanf("%d", &A.contrasenia);

    printf("\nIngrese el nombre y apellido. Maximo 30 caracteres: ");
    fflush(stdin);
    gets(A.nombreyapellido);

    printf("\nIngrese el documento: ");
    scanf("%d", &A.documento);

    printf("\nIngrese la edad: ");
    scanf("%d", &A.edad);

    printf("\nIngrese el genero (Masculino / Femenino): ");
    fflush(stdin);
    gets(A.genero);

    // VALIDACIÓN: Mientras NO sea "Masculino" Y tampoco sea "Femenino"
    while (strcmp(A.genero, "Masculino") != 0 && strcmp(A.genero, "Femenino") != 0)
    {
        printf("\nGenero erroneo (ingrese 'Masculino' o 'Femenino'): ");
        fflush(stdin);
        gets(A.genero);
    }

    return A;
}

void loginempleado()
{
}
void logincliente()
{
}
void registrarempleado()
{
}
void registrarcliente()
{
}