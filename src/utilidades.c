//
// Created by moham on 15/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilidades.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausarPantalla() {
    fflush(stdin);
    getchar();
}

Fecha cargarFechaActual() {
    Fecha f;

    time_t t = time(NULL);
    struct tm *hoy = localtime(&t);

    f.dia = hoy->tm_mday;
    f.mes = hoy->tm_mon + 1;
    f.anio = hoy->tm_year + 1900;

    return f;
}

void animacionImpresora3D(int totalSteps, int stepDelayMs) {

    if (totalSteps <= 0) totalSteps = 30;
    if (stepDelayMs < 10) stepDelayMs = 80;

    const char frames[] = {'/', '-', '\\', '|'};  // spinner


    // Banner simple
    printf("\x1b[1;36m=====================================\n");
    printf("       PROYECTO TRESDE FACTORY          \n");
    printf("=====================================\x1b[0m\n\n");

    printf("Inicializando el sistema...\n\n");

    // Pre-espacio para no dejar basura visual
    printf("\n");

    for (int filled = 0; filled <= totalSteps; filled++) {

        int percent = (filled * 100) / totalSteps;
        char spin = frames[filled % 4];

        // Mover el cursor al inicio de la línea anterior
        printf("\r[");

        // Barra
        printf("\x1b[1;31m");   // rojo
        for (int i = 0; i < totalSteps; i++) {
            if (i < filled) printf("=");
            else printf(".");
        }
        printf("\x1b[0m");

        printf("]  ");

        // Porcentaje en blanco
        printf("\x1b[1;37m%3d%%\x1b[0m  %c", percent, spin);

        fflush(stdout);

#ifdef _WIN32
        Sleep(stepDelayMs);
#else
        usleep(stepDelayMs * 1000);
#endif
    }

    printf("\a"); // beep
    printf("\n\n");
}


void inicializacionPrimeraVez() {
    // Ejecutar SOLO una vez cuando se instala el sistema
    // Luego dejar comentado este llamado en main

    //inicializarEmpleados();
    // inicializarProductos();

    // Si algún día agregamos más inicializaciones, van aca.
}

void mostrarAyuda()
{
    limpiarPantalla();

    printf(COL_VERDE "===============================================\n");
    printf("               AYUDA AL USUARIO\n");
    printf("===============================================\n\n" COL_RESET);

    // Bienvenida
    printf("Bienvenido a Proyecto Tresde Factory.\n");
    printf("Este sistema permite gestionar pedidos de Impresion 3D.\n\n");

    // Como usar el sistema
    printf(COL_AMARILLO "Como usar el sistema?\n" COL_RESET);
    printf("- Al iniciar, elegi si sos cliente o empleado.\n\n");

    // Clientes
    printf(COL_AMARILLO "Clientes\n" COL_RESET);
    printf("- Si sos nuevo, registrate con tus datos. El sistema te los va pedir de a uno. "
           "No olvides elegir que tipo de cliente sos (mayorista, minorista).\n");
    printf("- Si ya estas registrado, ingresa  con tu tu DNI.\n");
    printf("\n");
    printf("- Desde tu menu podes:\n");
    printf("  * Hacer un nuevo pedido\n");
    printf("  * Consultar el estado de tus pedidos\n");
    printf("  * Ver tu historial\n");
    printf("  * Ver el catalogo de productos\n\n");

    // Empleados
    printf(COL_AMARILLO "Empleados\n" COL_RESET);
    printf("- Ingresa tu legajo para acceder a tu consola de trabajo.\n");
    printf("- Segun tu rol, vas a poder:\n");
    printf("  * Produccion: ver pedidos en preparacion y pasarlos a impresion\n");
    printf("  * Calidad: aprobar pedidos impresos\n");
    printf("  * Administracion: habilitar pedidos para retiro, gestionar stock, administrar clientes y empleados, etc.\n\n");

    // Estados
    printf(COL_AMARILLO "Estados del pedido\n" COL_RESET);
    printf("1 = En preparacion\n");
    printf("2 = En impresion\n");
    printf("3 = Finalizado\n");
    printf("4 = Retirado\n\n");

    // Importante
    printf(COL_AMARILLO "Importante\n" COL_RESET);
    printf("- Clientes mayoristas reciben 30%% de descuento si compran 5 unidades o mas de un determinado producto.\n");
    printf("- Clientes minoristas, tambien reciben su descuento del 30%% si compran 5 unidades o mas de un determinado producto.\n");
    printf("- Todos los datos se guardan automaticamente.\n");
    printf("- Para una mejor experiencia, navega usando los numeros del menu y segui las instrucciones en pantalla.\n\n");

    printf("Presiona cualquier tecla para volver hacia atras: ");
    pausarPantalla();
}



