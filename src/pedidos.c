#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pedidos.h"
#include "validaciones.h"
#include "utilidades.h"
#include "estructuras.h"
#include "productos.h"


// ============================================================
//   GENERAR NUEVO ID AUTOMÁTICO
// ============================================================
int generarNuevoIdPedido() {
    FILE *archi = fopen(ARCHIVOPEDIDOS, "rb");
    if (!archi) return 1;

    Pedido p;
    int ultimo = 0;

    while (fread(&p, sizeof(Pedido), 1, archi) == 1) {
        if (p.idPedido > ultimo)
            ultimo = p.idPedido;
    }

    fclose(archi);
    return ultimo + 1;
}


// ============================================================
//   CALCULAR PRECIO CON DESCUENTO
// ============================================================
float calcularPrecioConDescuento(Producto p, int cantidad, char tipoCliente[]) {
    float precio = p.precio;

    if (strcmp(tipoCliente, "mayorista") == 0 && cantidad >= 5)
        precio = precio * 0.70f;

    return precio;
}


// ============================================================
//   TEXTO DE ESTADO
// ============================================================

void mostrarEstadoTexto(int estado) {
    switch (estado) {
        case 1: printf("\033[33mproduccion\033[0m"); break;
        case 2: printf("\033[34mimpresion\033[0m"); break;
        case 3: printf("\033[35mfinalizado\033[0m"); break;
        case 4: printf("\033[32mretirado\033[0m"); break;

        default: printf("desconocido"); break;
    }
}


// ============================================================
//   NUEVO PEDIDO
// ============================================================
void nuevoPedido(Cliente cliente) {

    while (1) {

        Pedido ped;
        Producto prod;
        char cantStr[10];
        int cantidad;
        int indiceElegido;

        limpiarPantalla();
        printf("===== NUEVO PEDIDO =====\n\n");

        if (!mostrarCatalogoCliente(cliente.tipo, &indiceElegido)) {
            return;
        }

        if (!obtenerProductoPorIndice(indiceElegido, &prod)) {
            printf("No se pudo obtener el producto.\n");
            pausarPantalla();
            continue;
        }

        printf("\nProducto seleccionado: %s\n", prod.nombre);
        printf("Codigo: %s\n", prod.codigo);

        float precioFinal = prod.precio;

        if (strcmp(cliente.tipo, "mayorista") == 0) {
            precioFinal = prod.precio * 0.70f;
            printf("Precio mayorista: $%.2f\n\n", precioFinal);
        } else {
            printf("Precio: $%.2f\n\n", prod.precio);
        }

        // Cantidad
        do {
            printf("Cantidad (0 para cancelar): ");
            fflush(stdin);
            gets(cantStr);

            if (!validarNumero(cantStr)) {
                printf("Cantidad invalida\n");
                continue;
            }

            cantidad = strtol(cantStr, NULL, 10);

            if (cantidad == 0) {
                printf("\nPedido cancelado.\n");
                pausarPantalla();
                break;
            }

        } while (cantidad < 1);

        if (cantidad == 0)
            continue;

        // =======================================================
        // DESCUENTO POR 5+ UNIDADES (minorista)
        // =======================================================
        if (strcmp(cliente.tipo, "mayorista") != 0 && cantidad >= 5) {

            precioFinal = prod.precio * 0.70f;

            printf("\n\033[0;32m>>> Descuento aplicado! <<<\033[0m\n");
            printf("\033[0;32mSe aplico un descuento del 30%% por comprar 5 o mas unidades.\033[0m\n\n");
        }

        // Estado del pedido
        if (prod.stock == 0)
            ped.estado = 1;
        else if (cantidad > prod.stock)
            ped.estado = 2;
        else
            ped.estado = 4;

        // Completar estructura
        ped.precioUnitario = precioFinal;
        ped.total          = precioFinal * cantidad;
        ped.idPedido       = generarNuevoIdPedido();
        ped.fecha          = cargarFechaActual();
        strcpy(ped.dniCliente, cliente.dni);
        strcpy(ped.codigoProducto, prod.codigo);
        ped.cantidad       = cantidad;

        // Guardar en archivo
        FILE *archi = fopen(ARCHIVOPEDIDOS, "ab");
        if (!archi) {
            printf("Error escribiendo archivo de pedidos.\n");
            pausarPantalla();
            return;
        }

        fwrite(&ped, sizeof(Pedido), 1, archi);
        fclose(archi);

        if (cantidad <= prod.stock)
            actualizarStockProducto(prod.codigo, -cantidad);

        printf("\nPedido registrado correctamente!\n");
        printf("Estado: ");
        mostrarEstadoTexto(ped.estado);
        printf("\nTotal: $%.2f\n", ped.total);

        // Otro pedido?
        char opcStr[10];
        printf("\nDesea realizar otro pedido?\n");
        printf("1) Si\n");
        printf("0) No, volver al menu\n");
        printf("Opcion: ");
        fflush(stdin);
        gets(opcStr);

        if (opcStr[0] != '1')
            return;
    }
}



// ============================================================
//   MOSTRAR PEDIDOS FILTRADOS
// ============================================================
void mostrarPedidosFiltrados(int estadoFiltrar) {
    FILE *archi = fopen(ARCHIVOPEDIDOS, "rb");
    if (!archi) {
        printf("No hay pedidos cargados.\n");
        return;
    }

    Pedido p;
    int encontrado = 0;

    printf("ID   Cliente     Prod     Cant   Total        Estado\n");
    printf("---------------------------------------------------------------\n");

    while (fread(&p, sizeof(Pedido), 1, archi) == 1) {
        if (p.estado == estadoFiltrar) {

            encontrado = 1;

            printf("%-4d %-12s %-10s %-5d $%-10.2f ",
                   p.idPedido,
                   p.dniCliente,
                   p.codigoProducto,
                   p.cantidad,
                   p.total
            );

            mostrarEstadoTexto(p.estado);
            printf("\n");

            // SEPARADOR ENTRE PEDIDOS
            printf("---------------------------------------------------------------\n");
        }
    }

    if (!encontrado)
        printf("(No hay pedidos con ese estado)\n");

    fclose(archi);
}


// ============================================================
//   MOSTRAR TODOS LOS PEDIDOS
// ============================================================
void mostrarPedidosTodos() {
    FILE *archi = fopen(ARCHIVOPEDIDOS, "rb");
    if (!archi) {
        printf("No hay pedidos cargados.\n");
        return;
    }

    Pedido p;

    printf("ID   Cliente     Prod     Cant   Total        Estado\n");
    printf("------------------------------------------------------------------\n");

    while (fread(&p, sizeof(Pedido), 1, archi) == 1) {

        printf("%-4d %-12s %-10s %-5d $%-10.2f ",
               p.idPedido,
               p.dniCliente,
               p.codigoProducto,
               p.cantidad,
               p.total
        );

        mostrarEstadoTexto(p.estado);
        printf("\n");

        // separador entre pedidos
        printf("------------------------------------------------------------------\n");
    }

    fclose(archi);
}


// ============================================================
//   CAMBIAR ESTADO DE PEDIDO
// ============================================================
void cambiarEstadoPedido(int estadoActual, int estadoNuevo, const char* titulo) {

    char repetir[5];

    do {
        limpiarPantalla();
        printf(">>> \033[0;36m%s\033[0m <<<\n\n", titulo);

        mostrarPedidosFiltrados(estadoActual);

        char idStr[20];
        int idBuscado;

        printf("\n\033[0;33mIngrese ID del pedido (0 para volver):\033[0m ");
        fflush(stdin);
        gets(idStr);

        // 1) Salida inmediata
        if (strcmp(idStr, "0") == 0) {
            return;
        }

        // 2) Validar numero
        if (!validarNumero(idStr)) {
            printf("\n\033[0;31mID invalido.\033[0m\n");
            pausarPantalla();
            continue;
        }

        idBuscado = atoi(idStr);

        FILE* archi = fopen(ARCHIVOPEDIDOS, "rb+");
        if (!archi) {
            printf("\n\033[0;31mNo existe pedidos.bin\033[0m\n");
            pausarPantalla();
            return;
        }

        Pedido p;
        int encontrado = 0;

        while (fread(&p, sizeof(Pedido), 1, archi) == 1) {

            if (p.idPedido == idBuscado && p.estado == estadoActual) {

                encontrado = 1;
                long pos = ftell(archi) - sizeof(Pedido);

                p.estado = estadoNuevo;

                fseek(archi, pos, SEEK_SET);
                fwrite(&p, sizeof(Pedido), 1, archi);

                fclose(archi);

                printf("\n\033[0;32mEstado actualizado correctamente!\033[0m\n");

                if (estadoNuevo == 2)
                    printf("-> El pedido ahora esta \033[0;33mEN IMPRESION\033[0m.\n");
                else if (estadoNuevo == 3)
                    printf("-> El pedido ahora esta \033[0;32mFINALIZADO\033[0m.\n");
                else if (estadoNuevo == 4)
                    printf("-> El pedido ahora esta \033[0;32mRETIRADO\033[0m.\n");

                printf("\nPresione una tecla para ver lista actualizada...");
                pausarPantalla();

                limpiarPantalla();
                printf(">>> \033[0;36mLISTA ACTUALIZADA\033[0m <<<\n\n");

                mostrarPedidosFiltrados(estadoActual);

                printf("\n\033[0;33mDesea cambiar otro pedido? (s/n):\033[0m ");
                fflush(stdin);
                gets(repetir);

                break;   // salimos del while de lectura
            }
        }

        if (!encontrado) {
            fclose(archi);
            printf("\n\033[0;31mNo existe un pedido con ese ID y ese estado.\033[0m\n");
            pausarPantalla();
            continue;
        }

    } while (repetir[0] == 's' || repetir[0] == 'S');
}


