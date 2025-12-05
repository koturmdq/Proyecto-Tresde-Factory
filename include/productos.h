//
// Created by moham on 15/11/2025.
//
#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#define ARCHIVOPRODUCTOS "productos.bin"

#include <stdio.h>
#include "estructuras.h"
#include "utilidades.h"

// Inicializar productos
void inicializarProductos();

// Mostrar catálogo completo
void mostrarCatalogoProductos();

// Buscar producto por código
int buscarProductoPorCodigo(char codigoBuscado[], Producto *pOut);

// Verificar si hay stock
int verificarStockDisponible(char codigoBuscado[], int cantidad);

// Actualizar stock (devuelve 1 si OK, 0 si no existe)
int actualizarStockProducto(char codigoBuscado[], int delta);

// Catálogo enumerado
int mostrarCatalogoProductosEnumerado();

// Obtener producto por índice (devuelve 1 si lo encontró)
int obtenerProductoPorIndice(int indice, Producto *pOut);

// Seleccionar producto por número (devuelve 1 si OK)
int seleccionarProductoPorNumero(const char tipoCliente[], Producto *prodOut);

// Catalogo para cliente (sin stock)
int mostrarCatalogoCliente(char tipoCliente[], int *indiceElegido);
int catalogoSeleccionarProductoCliente(char tipoCliente[], int *indiceElegido);

void administrarStock();


#endif


