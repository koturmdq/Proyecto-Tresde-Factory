//
// Created by moham on 15/11/2025.
//

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estructuras.h"

#define COL_RESET   "\x1b[0m"
#define COL_AZUL    "\x1b[34m"
#define COL_AMARILLO "\x1b[33m"
#define COL_VERDE   "\x1b[32m"
#define COL_MAGENTA "\x1b[35m"


// Limpia pantalla
void limpiarPantalla();

// Pausa
void pausarPantalla();

// Fecha actual
Fecha cargarFechaActual();

// Animación opcional
void animacionImpresora3D(int totalSteps, int stepDelayMs);

// Carga inicial de Empleados y productos
void inicializacionPrimeraVez();

// Mostrar ayuda al usuario
void mostrarAyuda();


#endif
