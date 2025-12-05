//
// Created by moham on 15/11/2025.
//

#include <stdio.h>
#include <string.h>

#include "menus.h"
#include "validaciones.h"
#include "clientes.h"
#include "empleados.h"
#include "utilidades.h"

/// ============================
//     MENU PRINCIPAL
// ============================
void menuPrincipal() {
    int opcion = -1;
    char opcionStr[10];

    do {
        limpiarPantalla();
        printf("======================================\n");
        printf("    PROYECTO TRESDE FACTORY - MENU\n");
        printf("======================================\n");

        printf("\n");
        printf("1. Ingresar al sistema\n");
        printf("2. Ayuda al Usuario\n");
        printf("3. Salir\n\n");

        printf("Elija una opcion: ");
        fflush(stdin);
        gets(opcionStr);

        if (!validarNumero(opcionStr)) {
            printf("\nOpcion invalida\n");
            pausarPantalla();
            continue;
        }

        opcion = opcionStr[0] - '0';

        switch (opcion) {
            case 1:
                menuLogin();
                break;

            case 2:
                mostrarAyuda();
                break;

            case 3:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida\n");
                pausarPantalla();
                break;
        }

    } while (opcion != 3);
}

// ============================
//           LOGIN
// ============================
void menuLogin() {
    int opcion = -1;
    char opcionStr[10];

    do {
        limpiarPantalla();
        printf("=====================================\n");
        printf("               LOGIN\n");
        printf("=====================================\n");
        printf("1. Cliente\n");
        printf("2. Empleado\n");
        printf("3. Volver atras\n\n");
        printf("Elija una opcion: ");
        fflush(stdin);
        gets(opcionStr);

        if (!validarNumero(opcionStr)) {
            printf("\nOpcion invalida\n");
            pausarPantalla();
            continue;
        }

        opcion = opcionStr[0]-'0';

        switch (opcion) {
            case 1: menuCliente(); break;
            case 2: menuEmpleado(); break;
            case 3: return;
            default: printf("Opcion invalida\n"); pausarPantalla(); break;
        }

    } while (opcion != 3);
}

// ============================
//        MENU EMPLEADO
// ============================
void menuEmpleado() {
    limpiarPantalla();
    loginEmpleado();
}

// ============================
//        MENU CLIENTE
// ============================
void menuCliente() {
    int opcion = -1;
    char opcionStr[10];

    do {
        limpiarPantalla();
        printf("=====================================\n");
        printf("              CLIENTE\n");
        printf("=====================================\n");
        printf("1. Cliente nuevo\n");
        printf("2. Cliente registrado\n");
        printf("3. Volver atras\n\n");
        printf("Elija una opcion: ");
        fflush(stdin);
        gets(opcionStr);

        if (!validarNumero(opcionStr)) {
            printf("\nOpcion invalida\n");
            pausarPantalla();
            continue;
        }

        opcion = opcionStr[0]-'0';

        switch (opcion) {
            case 1: nuevoCliente(); break;
            case 2: clienteRegistrado(); break;
            case 3: return;
            default: printf("Opcion invalida\n"); pausarPantalla(); break;
        }

    } while (opcion != 3);
}
