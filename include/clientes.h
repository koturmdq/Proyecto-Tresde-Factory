//
// Created by moham on 14/11/2025.
//
#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#define ARCHIVOCLIENTES "clientes.bin"

#include "estructuras.h"   // Cliente, Pedido, Fecha, Producto, etc.


// ===============================================================
//     PROTOTIPOS — CLIENTES
// ===============================================================

// Alta de cliente
void nuevoCliente();

// Buscar cliente por DNI
int buscarClientePorDni(char dniBuscado[], Cliente *cOut);

// Login cliente registrado
void clienteRegistrado();

// Menu principal del cliente logueado
void menuClienteRegistrado(Cliente cliente);

// Datos extra (debug)
void mostrarDatosCliente(Cliente c);

// Estado de pedidos del cliente (solo activos)
void mostrarPedidosClienteActivos(Cliente cliente);

// Historial de pedidos
void mostrarHistorialPedidos(Cliente cliente);
void mostrarHistorialPedidosRec(Pedido* arr, int validos, int i);

// Eliminar cliente (solo la función real)
void eliminarClientePorDni();
int clienteTienePedidosActivos(char dni[]);

// Mostrar clientes (segun necesito en funcion)
void mostrarCatalogoClienteSoloLectura(char tipoCliente[]);
void adminVerClientesSinPausa();

#endif // CLIENTES_H_INCLUDED
