//
// Created by moham on 15/11/2025.
//

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define ARCHIVOPEDIDOS "pedidos.bin"
#define ARCHIVOPRODUCTOS "productos.bin"

// ------------------------------------
// FECHA
// ------------------------------------
typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

// ------------------------------------
// CLIENTE
// ------------------------------------
typedef struct {
    char dni[15];
    char nombre[50];
    char telefono[20];
    char direccion[50];
    char tipo[15];
    char email[50];
} Cliente;

// ------------------------------------
// EMPLEADO
// ------------------------------------
typedef struct {
    char legajo[10];
    char nombre[50];
    char puesto[30];
    char telefono[20];
    char email[50];
} Empleado;

// ------------------------------------
// PRODUCTO
// ------------------------------------
typedef struct {
    char codigo[15];
    char nombre[50];
    char descripcion[100];
    int stock;
    float precio;
} Producto;

// ------------------------------------
// PEDIDO
// ------------------------------------
typedef struct {
    int idPedido;
    Fecha fecha;
    char dniCliente[15];
    char codigoProducto[15];
    int cantidad;
    float precioUnitario;
    float total;
    int estado;
} Pedido;

#endif


