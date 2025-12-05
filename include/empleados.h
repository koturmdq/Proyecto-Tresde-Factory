//
// Created by moham on 14/11/2025.
//

#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#define ARCHIVOPRODUCTOS "productos.bin"
#define ARCHIVOEMPLEADOS "empleados.bin"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "estructuras.h"
#include "validaciones.h"
#include "clientes.h"
#include "productos.h"
#include "pedidos.h"

// -------------------------------------------------------------
// PROTOTIPOS GENERALES
// -------------------------------------------------------------
void inicializarEmpleados();
int buscarEmpleadoPorLegajo(char legajoBuscado[], Empleado *eOut);
void loginEmpleado();
void menuEmpleadoSegunRol(Empleado emp);

// -------------------------------------------------------------
// PRODUCCION
// -------------------------------------------------------------
void menuProduccion(Empleado emp);
void produccionVerPedidos();
void produccionCambiarEstado1a2();

// -------------------------------------------------------------
// CALIDAD
// -------------------------------------------------------------
void menuCalidad(Empleado emp);
void calidadVerPedidos();
void calidadCambiarEstado2a3();

// -------------------------------------------------------------
// ADMINISTRACION
// -------------------------------------------------------------
void menuAdministracion(Empleado emp);
void adminVerTodosLosPedidos();
void adminCambio3a4();
void adminMostrarCatalogo();
void adminVerClientes();
void administrarStock();
void eliminarClientePorDni();
void adminAgregarEmpleado();
int generarLegajoNuevo();
void adminVerEmpleados();
int empleadoTienePedidosActivos(Empleado e);
void eliminarEmpleadoPorLegajo();



#endif // EMPLEADOS_H
