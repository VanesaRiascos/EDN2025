#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pasajero {
    char genero[20];
    char apellido[30];
    struct Pasajero *siguiente;
} Pasajero;

Pasajero *listaVenta = NULL;  // Lista de todos los que compran
Pasajero *listaAbordados = NULL; // Lista de abordados
Pasajero *listaNoAbordados = NULL; // Lista de no abordados

int capacidadAvion = 0;
int maxSobreventa = 0;
int totalVendidos = 0;
int abordajeIniciado = 0;

// Creamos un nuevo pasajero
Pasajero* crearPasajero(char genero[], char apellido[]) {
    Pasajero *nuevo = (Pasajero*)malloc(sizeof(Pasajero));
    strcpy(nuevo->genero, genero);
    strcpy(nuevo->apellido, apellido);
    nuevo->siguiente = NULL;
    return nuevo;
}

// Agregamos un pasajero a una lista enlazada
void agregarALista(Pasajero **lista, Pasajero *nuevo) {
    if (*lista == NULL) {
        *lista = nuevo;
    } else {
        Pasajero *temp = *lista;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
}

void establecerCapacidad() {
    if (capacidadAvion > 0) {
        printf("\nLa capacidad ya ha sido establecida y no se puede cambiar.\n");
        return;
    }
    printf("\nIngrese la capacidad maxima del avion: ");
    scanf("%d", &capacidadAvion);
    maxSobreventa = capacidadAvion + (capacidadAvion * 0.10);
    printf("Capacidad registrada: %d pasajeros (+10%% sobreventa = %d maximos vendibles)\n", capacidadAvion, maxSobreventa);
}

void venderTiquete() {
    if (capacidadAvion == 0) {
        printf("\nPrimero debe establecer la capacidad del avion.\n");
        return;
    }
    if (abordajeIniciado) {
        printf("\nNo se pueden vender tiquetes despues de iniciar el abordaje.\n");
        return;
    }
    if (totalVendidos >= maxSobreventa) {
        printf("\nNo se pueden vender mas tiquetes (se alcanzo el limite con sobreventa).\n");
        return;
    }

    char genero[20], apellido[30];
    printf("\nIngrese genero (Femenino/Masculino/NoBinario): ");
    scanf("%s", genero);
    printf("Ingrese primer apellido: ");
    scanf("%s", apellido);

    Pasajero *nuevo = crearPasajero(genero, apellido);
    agregarALista(&listaVenta, nuevo);
    totalVendidos++;
    printf("\nTiquete vendido exitosamente. Total vendidos: %d/%d\n", totalVendidos, maxSobreventa);
}

void iniciarAbordaje() {
    if (abordajeIniciado) {
        printf("\nEl abordaje ya ha sido iniciado.\n");
        return;
    }
    if (totalVendidos == 0) {
        printf("\nNo hay pasajeros para abordar.\n");
        return;
    }

    abordajeIniciado = 1;
    int contador = 0;
    Pasajero *temp = listaVenta;

    while (temp != NULL) {
        Pasajero *siguiente = temp->siguiente;  // Guardarmos referencia
        temp->siguiente = NULL; // Desconectar

        if (contador < capacidadAvion) {
            agregarALista(&listaAbordados, temp);
            contador++;
        } else {
            agregarALista(&listaNoAbordados, temp);
        }
        temp = siguiente;
    }
    printf("\nAbordaje finalizado. Subieron %d pasajeros. %d se quedaron sin abordar.\n", contador, totalVendidos - contador);
}

void mostrarLista(Pasajero *lista) {
    if (lista == NULL) {
        printf("\n(No hay registros para mostrar)\n");
        return;
    }
    while (lista != NULL) {
        printf("Pasajero: %s - %s\n", lista->apellido, lista->genero);
        lista = lista->siguiente;
    }
}

int main() {
    int opcion;
    do {
        
        printf("1. Establecer Capacidad\n");
        printf("2. Vender Tiquete\n");
        printf("3. Iniciar Abordaje\n");
        printf("4. Ver Abordados\n");
        printf("5. Ver No Abordados\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: establecerCapacidad(); break;
            case 2: venderTiquete(); break;
            case 3: iniciarAbordaje(); break;
            case 4: mostrarLista(listaAbordados); break;
            case 5: mostrarLista(listaNoAbordados); break;
            case 6: printf("\nSaliendo del programa...\n"); break;
            default: printf("\nOpcion invalida.\n");
        }
    } while (opcion != 6);

    return 0;
}
