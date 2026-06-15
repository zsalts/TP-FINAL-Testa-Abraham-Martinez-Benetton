#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int idCliente;
    char nombreCompleto[100];
    char email[100];
    char password[50];
    int estado; // 1 = Activo, 0 = Baja Logica
} stCliente;

void altaCliente();
int buscarClienteRecursivo(FILE *archi, int idBusqueda);
void bajaCliente();
void modificarCliente();
void consultarCliente();
void listarClientesSeleccion();
void menuClientes();

#endif
