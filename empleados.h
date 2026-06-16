#ifndef EMPLEADOS_H_INCLUDED
#define EMPLEADOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

typedef struct
{
    int legajo;
    char nombre[50];
    char puesto[50];
    int estado;

}stEmpleados;

void cargarEmpleados ();
void mostrarEmpleados ();
void bajaEmpleados();
void modificarEmpleados();
void consultarEmpleados();
void menuEmpleados(Pila *pedidos);

#endif
