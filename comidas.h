#ifndef COMIDAS_H_INCLUDED
#define COMIDAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

typedef struct {
    int idComida;
    char nombre[50];
    float precio;
    int estado; 
} stComida;

typedef struct {
    int numHab;
    int idComida;
    int cantidad;
    int atendido; 
} stPedidoComida;

void cargarPlatoMenu();
void mostrarMenuComidas();
void realizarPedidoComida(int numHab, Pila *pedidosPila);
void procesarPedidoComida(int numHab);
void menuAdministrarComidas();

#endif