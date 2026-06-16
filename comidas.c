#include "comida.h"

const char arqMenu[] = "comidas.dat";
const char arqPedidos[] = "pedidosComida.dat";

void cargarPlatoMenu() {
    stComida aux;
    FILE *archi = fopen(arqMenu, "ab");

    if (archi != NULL) {
        printf("Ingrese ID numerico del plato/bebida: ");
        scanf("%d", &aux.idComida);
        
        fflush(stdin);
        printf("Ingrese nombre de la comida: ");
        fgets(aux.nombre, 50, stdin);
        aux.nombre[strcspn(aux.nombre, "\n")] = 0;
        
        printf("Ingrese precio: $");
        scanf("%f", &aux.precio);
        
        aux.estado = 1; 

        fwrite(&aux, sizeof(stComida), 1, archi);
        fclose(archi);
        printf("\nPlato agregado a la carta exitosamente.\n");
    } else {
        printf("\nError al abrir el archivo de la carta.\n");
    }
}

void mostrarMenuComidas(){
    stComida aux; 
    FILE *buffer = fopen(arqMenu, "rb");
    int cont = 0;

    if(buffer != NULL){
        printf("--- CARTA DEL RESTAURANTE ---\n\n");
        while(fread(&aux, sizeof(stComida), 1, buffer)>0){
            if(aux.estado == 1){
                printf("ID: %i | %s | Precio: $%.2f\n", aux.idComida, aux.nombre, aux.precio);
                cont++;
            }
        }
        fclose(buffer);
    }
}

void realizarPedidoComida(int numHab, Pila *pedidosPila) {
    mostrarMenuComidas();
    
    stPedidoComida nuevoPedido;
    nuevoPedido.numHab = numHab;
    nuevoPedido.atendido = 0; 

    printf("\nIngrese el ID de la comida que desea ordenar: ");
    scanf("%d", &nuevoPedido.idComida);
    printf("Ingrese la cantidad: ");
    scanf("%d", &nuevoPedido.cantidad);

    FILE *buffer = fopen(arqPedidos, "ab");
    if (buffer != NULL) {
        fwrite(&nuevoPedido, sizeof(stPedidoComida), 1, buffer);
        fclose(buffer);

        apilar(pedidosPila, numHab);
        printf("\n¡Pedido enviado con exito! Su comida ya se esta preparando.\n");
    } else {
        printf("\nError critico al registrar el pedido.\n");
    }
}

void procesarPedidoComida(int numHab){
    stPedidoComida ped;
    stComida com;
    FILE *bufferPed = fopen(arqPedidos, "r+b");
    FILE *bufferMenu = fopen(arqMenu, "rb");
    int encontrado = 0;

    if (bufferMenu != NULL && bufferPed != NULL)
    {
        while (fread(&ped, sizeof(stPedidoComida), 1, bufferPed) > 0 && encontrado == 0){
            if(ped.numHab == numHab && ped.atendido == 0){
                while (fread(&com, sizeof(stComida), 1, bufferPed) > 0) {
                    if (com.idComida == ped.idComida) {
                        printf("-> DETALLE DEL PEDIDO: %s (Cantidad: %d)\n", com.nombre, ped.cantidad);
                        encontrado = 1;
                    }
                }
                ped.atendido = 1;
                fseek(bufferPed, sizeof(stPedidoComida) * -1, SEEK_CUR);
                fwrite(&ped, sizeof(stPedidoComida), 1, bufferPed);
            }
        }
        fclose(bufferPed);
        fclose(bufferMenu);
    }
}

void menuAdministrarComidas() {
    int opcion;
    do {
        system("cls"); 
        printf("==================================================\n");
        printf("          ADMINISTRACION DE RESTAURANTE           \n");
        printf("==================================================\n");
        printf("1. Cargar plato/bebida a la carta\n");
        printf("2. Mostrar carta completa\n");
        printf("0. Volver al Menu de Empleados\n");
        printf("==================================================\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        
        system("cls"); 

        switch(opcion) {
            case 1:
                printf("\n--- AGREGAR PLATO ---\n");
                cargarPlatoMenu();
                break;
            case 2:
                printf("\n--- REVISAR CARTA ---\n");
                mostrarMenuComidas();
                break;
            case 0:
                printf("\nVolviendo al menu de empleados...\n");
                break;
            default:
                printf("\nOpcion invalida.\n");
        }
        
        if (opcion != 0) {
            printf("\n");
            system("pause"); 
        }
    } while (opcion != 0);
}