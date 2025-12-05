//
// Created by moham on 14/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clientes.h"
#include "productos.h"
#include "validaciones.h"
#include "estructuras.h"
#include "utilidades.h"
#include "pedidos.h"
#include "empleados.h"



// ===============================================================
//                FUNCION: nuevoCliente
// ===============================================================
void nuevoCliente() {
    Cliente c;
    char tipoStr[10];

    limpiarPantalla();
    printf("===== REGISTRO DE CLIENTE =====\n\n");

    // DNI
    do {
        printf("Ingrese DNI: ");
        fflush(stdin);
        gets(c.dni);
    } while(!validarDni(c.dni));

    // Nombre
    do {
        printf("Ingrese nombre: ");
        fflush(stdin);
        gets(c.nombre);
    } while(!validarTexto(c.nombre));

    // Telefono
    do {
        printf("Ingrese telefono: ");
        fflush(stdin);
        gets(c.telefono);
    } while(!validarTelefono(c.telefono));

    // Direccion
    printf("Ingrese direccion: ");
    fflush(stdin);
    gets(c.direccion);

    // Tipo de cliente
    do {
        printf("Tipo de cliente (1=mayorista / 2=minorista): ");
        fflush(stdin);
        gets(tipoStr);
    } while(!validarNumero(tipoStr) || (tipoStr[0] != '1' && tipoStr[0] != '2'));

    if(tipoStr[0] == '1')
        strcpy(c.tipo, "mayorista");
    else
        strcpy(c.tipo, "minorista");

    // Email
    do {
        printf("Ingrese email: ");
        fflush(stdin);
        gets(c.email);
    } while(!validarEmail(c.email));

    // Guardar cliente
    FILE *archi = fopen("clientes.bin", "ab");
    if(archi) {
        fwrite(&c, sizeof(Cliente), 1, archi);
        fclose(archi);
        printf("\nCliente registrado correctamente!\n");
    } else {
        printf("\nNo se pudo abrir clientes.bin\n");
    }

    printf("Presione una tecla para volver al LogIn\n");
    pausarPantalla();
}


// ===============================================================
//             BUSCAR CLIENTE POR DNI
// ===============================================================
int buscarClientePorDni(char dniBuscado[], Cliente *cOut) {
    FILE *archi = fopen("clientes.bin", "rb");
    if(!archi) return 0;

    Cliente aux;
    while(fread(&aux, sizeof(Cliente), 1, archi) == 1) {
        if(strcmp(aux.dni, dniBuscado) == 0) {
            *cOut = aux;
            fclose(archi);
            return 1;
        }
    }

    fclose(archi);
    return 0;
}


// ===============================================================
//                CLIENTE REGISTRADO (LOGIN)
// ===============================================================
void clienteRegistrado() {
    char dni[15];
    Cliente c;

    limpiarPantalla();
    printf("===== ACCESO CLIENTE =====\n\n");

    do {
        printf("Ingrese DNI sin puntos (o 0 para volver): ");
        fflush(stdin);
        gets(dni);

        if(strcmp(dni, "0") == 0)
            return;

        if(!validarDniExistente(dni)) {
            printf("\nDNI no encontrado o invalido.\n");
            pausarPantalla();
        }

    } while(!validarDniExistente(dni));

    buscarClientePorDni(dni, &c);

    menuClienteRegistrado(c);
}



// ===============================================================
//                MENU DEL CLIENTE REGISTRADO
// ===============================================================
void menuClienteRegistrado(Cliente cliente) {
    int opcion = -1;
    char opcionStr[10];

    do {
        limpiarPantalla();
        printf("=====================================\n");
        printf(" CLIENTE: %s  (%s)\n", cliente.nombre, cliente.tipo);
        printf("=====================================\n");
        printf("1. Hacer un pedido\n");
        printf("2. Consultar estado del pedido\n");
        printf("3. Ver historial de pedidos\n");
        printf("4. Ver catalogo\n");
        printf("\n");
        printf("5. Volver atras\n\n");

        printf("Elija una opcion: ");
        fflush(stdin);
        gets(opcionStr);

        if(!validarNumero(opcionStr)) {
            printf("Opcion invalida.\n");
            pausarPantalla();
            continue;
        }

        opcion = opcionStr[0] - '0';

        switch(opcion) {

            case 1:
                nuevoPedido(cliente);
                break;

            case 2:
                mostrarPedidosClienteActivos(cliente);
                break;

            case 3:
                mostrarHistorialPedidos(cliente);
                break;

            case 4:
                mostrarCatalogoClienteSoloLectura(cliente.tipo);
                break;

            case 5:
                return;

            default:
                printf("Opcion invalida.\n");
                pausarPantalla();
        }

    } while(opcion != 5);
}


// ===============================================================
//          CONSULTAR ESTADO DEL PEDIDO (CLIENTE)
// ===============================================================
void mostrarPedidosClienteActivos(Cliente cliente) {

    FILE *archi = fopen(ARCHIVOPEDIDOS, "rb");
    if (!archi) {
        printf("No hay pedidos cargados.\n");
        pausarPantalla();
        return;
    }

    Pedido p;
    int hay = 0;

    limpiarPantalla();
    printf("===== ESTADO DE TUS PEDIDOS =====\n\n");

    while (fread(&p, sizeof(Pedido), 1, archi) == 1) {

        if (strcmp(p.dniCliente, cliente.dni) == 0) {

            // SOLO activos (1, 2, 4)
            if (p.estado == 1 || p.estado == 2 || p.estado == 4) {

                hay = 1;

                printf("Pedido #%d\n", p.idPedido);
                printf("Producto: %s\n", p.codigoProducto);
                printf("Cantidad: %d\n", p.cantidad);
                printf("Total: $%.2f\n", p.total);

                printf("Estado: ");
                mostrarEstadoTexto(p.estado);
                printf("\n");

                printf("----------------------------------------\n"); // separador
            }
        }
    }

    fclose(archi);

    if (!hay) {
        printf("\nNo tienes pedidos activos en este momento.\n");
    }

    printf("\nPresione una tecla para continuar...");
    pausarPantalla();
}



// ===============================================================
//              HISTORIAL DE PEDIDOS (CLIENTE)
// ===============================================================
void mostrarHistorialPedidos(Cliente cliente) {

    FILE *archi = fopen("pedidos.bin", "rb");
    if(!archi) {
        printf("No se pudo abrir pedidos.bin\n");
        pausarPantalla();
        return;
    }

    Pedido arr[300];
    int validos = 0;

    Pedido p;
    while(fread(&p, sizeof(Pedido), 1, archi) == 1) {
        if(strcmp(p.dniCliente, cliente.dni) == 0) {
            arr[validos++] = p;
        }
    }

    fclose(archi);

    limpiarPantalla();
    printf("===== HISTORIAL DE PEDIDOS =====\n\n");

    if(validos == 0) {
        printf("No tiene pedidos.\n");
        pausarPantalla();
        return;
    }

    mostrarHistorialPedidosRec(arr, validos, validos - 1);

    printf("\nPresione una tecla para continuar...");
    pausarPantalla();
}


// ===============================================================
//       MOSTRAR HISTORIAL (RECURSIVO, LIFO)
// ===============================================================
void mostrarHistorialPedidosRec(Pedido* arr, int validos, int i) {
    if (i < 0) return;

    Pedido p = arr[i];

    printf("#%d - %02d/%02d/%04d\n",
           p.idPedido, p.fecha.dia, p.fecha.mes, p.fecha.anio);

    printf("Producto: %s\n", p.codigoProducto);
    printf("Cantidad: %d\n", p.cantidad);
    printf("Total: $%.2f\n", p.total);

    printf("Estado: ");
    mostrarEstadoTexto(p.estado);
    printf("\n");

    printf("----------------------------------------\n\n");

    mostrarHistorialPedidosRec(arr, validos, i - 1);
}

// ===============================================================
//                      VER CLIENTES
// ===============================================================
void adminVerClientes() {
    FILE *archi = fopen(ARCHIVOCLIENTES, "rb");
    if (!archi) {
        printf("No se pudo abrir archivo clientes.\n");
        pausarPantalla();
        return;
    }

    Cliente c;

    limpiarPantalla();
    printf("===== LISTADO DE CLIENTES =====\n\n");
    printf("DNI         Nombre y Apellido       Telefono      Tipo\n");
    printf("------------------------------------------------------------\n");

    while (fread(&c, sizeof(Cliente), 1, archi) == 1) {

        const char *colorTipo =
            (strcmp(c.tipo, "mayorista") == 0) ? "\033[32m" : "\033[33m";

        printf("%-11s  %-20s  %-12s  %s%s\033[0m\n",
               c.dni, c.nombre, c.telefono, colorTipo, c.tipo);

        printf("------------------------------------------------------------\n");
    }

    fclose(archi);

    printf("\nPresione una tecla para volver atras: ");
    pausarPantalla();
}

void adminVerClientesSinPausa() {
    FILE *archi = fopen(ARCHIVOCLIENTES, "rb");
    if (!archi) {
        printf("No se pudo abrir archivo clientes.\n");
        return;
    }

    Cliente c;

    limpiarPantalla();
    printf("===== LISTADO DE CLIENTES =====\n\n");
    printf("DNI         Nombre y Apellido       Telefono      Tipo\n");
    printf("------------------------------------------------------------\n");

    while (fread(&c, sizeof(Cliente), 1, archi) == 1) {

        const char *colorTipo =
            (strcmp(c.tipo, "mayorista") == 0) ? "\033[32m" : "\033[33m";

        printf("%-11s  %-20s  %-12s  %s%s\033[0m\n",
               c.dni, c.nombre, c.telefono, colorTipo, c.tipo);

        printf("------------------------------------------------------------\n");
    }

    fclose(archi);
}

// ===============================================================
//                      ELIMINAR CLIENTE
// ===============================================================

void eliminarClientePorDni() {
    char dni[20];
    char conf[5];
    char repetir[5];
    Cliente c;

    do {
        limpiarPantalla();
        adminVerClientesSinPausa();

        printf("\nIngrese DNI del cliente a eliminar (0 para volver): ");
        fflush(stdin);
        gets(dni);

        // Volver atras
        if (strcmp(dni, "0") == 0) {
            return;
        }

        // Validacion: debe existir
        if (!validarDniExistente(dni)) {
            printf("\nDNI no encontrado.\n");
            pausarPantalla();
            continue;
        }

        // Buscar cliente
        if (!buscarClientePorDni(dni, &c)) {
            printf("\nNo se encontro el cliente.\n");
            pausarPantalla();
            continue;
        }

        // Cliente con pedidos activos
        if (clienteTienePedidosActivos(dni)) {

            printf("\n\033[0;31mNo se puede eliminar este cliente.\033[0m\n");
            printf("Posee pedidos activos en estado 1, 2 o 3.\n");
            printf("Debe finalizar / cancelar todos los pedidos antes de eliminarlo.\n");

            printf("\nDesea intentar con otro cliente? (s/n): ");
            fflush(stdin);
            gets(repetir);

            if (repetir[0] != 's' && repetir[0] != 'S') {
                return;   // vuelve al menú anterior
            }

            continue;     // vuelve a pedir otro DNI
        }


        // Confirmacion
        printf("\nSeguro que desea eliminar este cliente? (s/n): ");
        fflush(stdin);
        gets(conf);

        if (conf[0] != 's' && conf[0] != 'S') {
            printf("\nOperacion cancelada.\n");
            pausarPantalla();
            return;
        }

        // Eliminación segura con archivo temporal
        FILE *origen = fopen("clientes.bin", "rb");
        FILE *temp = fopen("clientes_temp.bin", "wb");

        if (!origen || !temp) {
            printf("\nNo se pudo abrir archivo para eliminar.\n");
            if (origen) fclose(origen);
            if (temp) fclose(temp);
            pausarPantalla();
            return;
        }

        Cliente aux;
        int eliminado = 0;

        while (fread(&aux, sizeof(Cliente), 1, origen) == 1) {
            if (strcmp(aux.dni, dni) != 0) {
                fwrite(&aux, sizeof(Cliente), 1, temp);
            } else {
                eliminado = 1;
            }
        }

        fclose(origen);
        fclose(temp);

        // Reemplazar archivo definitivo
        remove("clientes.bin");
        rename("clientes_temp.bin", "clientes.bin");

        if (eliminado) {
            printf("\nCliente eliminado correctamente.\n");
        } else {
            printf("\nNo se pudo eliminar el cliente.\n");
        }

        printf("\nDesea eliminar otro cliente? (s/n): ");
        fflush(stdin);
        gets(repetir);

    } while (repetir[0] == 's' || repetir[0] == 'S');
}



int clienteTienePedidosActivos(char dni[]) {
    FILE *archi = fopen(ARCHIVOPEDIDOS, "rb");
    if (!archi) return 0;

    Pedido p;

    while (fread(&p, sizeof(Pedido), 1, archi) == 1) {

        // Si el pedido pertenece al cliente Y NO está retirado
        if (strcmp(p.dniCliente, dni) == 0 && p.estado < 4) {

            fclose(archi);
            return 1;   // Tiene pedidos activos / NO eliminar
        }
    }

    fclose(archi);
    return 0;   // No tiene pedidos activos / se puede eliminar
}

