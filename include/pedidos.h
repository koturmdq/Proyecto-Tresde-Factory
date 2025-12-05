//
// Created by moham on 15/11/2025.
//

#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <stdio.h>
#include <string.h>

#include "estructuras.h"   // Pedido, Fecha, Cliente, Producto
#include "validaciones.h"
#include "utilidades.h"

#define ARCHIVOPEDIDOS "pedidos.bin"

// ============================================================
//        PROTOTIPOS GENERALES DE PEDIDOS
// ============================================================

// Genera ID nuevo autoincremental
int generarNuevoIdPedido();

// Calcula precio final segun cliente y cantidad
float calcularPrecioConDescuento(Producto p, int cantidad, char tipoCliente[]);

// Mostrar texto de estado (1,2,3,4)
void mostrarEstadoTexto(int estado);

// Tabla de estados (para menus)
void mostrarEstadosTabla();

// Cargar un nuevo pedido (cliente)
void nuevoPedido(Cliente cliente);


// ============================================================
//        FUNCIONES PARA EMPLEADOS
// ============================================================

// Mostrar solo pedidos con un estado específico
void mostrarPedidosFiltrados(int estadoFiltrar);

// Mostrar todos los pedidos (administracion)
void mostrarPedidosTodos();

// Cambiar estado de pedido (producción / administración)
void cambiarEstadoPedido(int estadoActual, int estadoNuevo, const char* titulo);


#endif // PEDIDOS_H


