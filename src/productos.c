//
// Created by moham on 14/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "productos.h"
#include "validaciones.h"

// ---------------------------------------------------------
// Inicializar catálogo
// ---------------------------------------------------------
void inicializarProductos() {
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "wb");
    if (!archi) {
        printf("No se pudo crear productos.bin\n");
        return;
    }

    Producto arr[10];

    strcpy(arr[0].codigo, "LMP-001");
    strcpy(arr[0].nombre, "Lampara Wave");
    strcpy(arr[0].descripcion, "Lampara organica impresa en 3D");
    arr[0].stock = 5;  arr[0].precio = 35000;

    strcpy(arr[1].codigo, "FIG-030");
    strcpy(arr[1].nombre, "Mario articulado 30cm");
    strcpy(arr[1].descripcion, "Figura articulada de Mario Bros");
    arr[1].stock = 2;  arr[1].precio = 35000;

    strcpy(arr[2].codigo, "ORG-200");
    strcpy(arr[2].nombre, "Organizador Brembo");
    strcpy(arr[2].descripcion, "Organizador estilo caliper Brembo");
    arr[2].stock = 8;  arr[2].precio = 21000;

    strcpy(arr[3].codigo, "VAS-010");
    strcpy(arr[3].nombre, "Vaso Milkshake");
    strcpy(arr[3].descripcion, "Vaso con tapa estilo milkshake");
    arr[3].stock = 9;  arr[3].precio = 16000;

    strcpy(arr[4].codigo, "SUP-050");
    strcpy(arr[4].nombre, "Soporte Joystick");
    strcpy(arr[4].descripcion, "Soporte universal para joystick");
    arr[4].stock = 6;  arr[4].precio = 19000;

    strcpy(arr[5].codigo, "MAT-090");
    strcpy(arr[5].nombre, "Mate Mickey");
    strcpy(arr[5].descripcion, "Mate tematico Mickey");
    arr[5].stock = 8;  arr[5].precio = 8500;

    strcpy(arr[6].codigo, "ZIG-100");
    strcpy(arr[6].nombre, "Pack Ziglu 10 animales");
    strcpy(arr[6].descripcion, "Pack articulado sensorial");
    arr[6].stock = 12; arr[6].precio = 12500;

    strcpy(arr[7].codigo, "KEY-007");
    strcpy(arr[7].nombre, "Portallaves DeLorean");
    strcpy(arr[7].descripcion, "Portallaves tematico DeLorean");
    arr[7].stock = 5;  arr[7].precio = 30000;

    strcpy(arr[8].codigo, "JAR-300");
    strcpy(arr[8].nombre, "Jarron Deco");
    strcpy(arr[8].descripcion, "Jarron decorativo moderno");
    arr[8].stock = 6;  arr[8].precio = 14500;

    strcpy(arr[9].codigo, "TET-400");
    strcpy(arr[9].nombre, "Tetris Equilibrista");
    strcpy(arr[9].descripcion, "Juego de habilidad Tetris");
    arr[9].stock = 15; arr[9].precio = 30000;

    fwrite(arr, sizeof(Producto), 10, archi);
    fclose(archi);

    printf("Productos cargados correctamente\n");
}


// ---------------------------------------------------------
// Mostrar catálogo
// ---------------------------------------------------------
void mostrarCatalogoProductos() {
    FILE *archi = fopen("productos.bin", "rb");
    if(!archi) {
        printf("No existe productos.bin\n");
        return;
    }

    Producto p;

    printf("===== CATALOGO DE PRODUCTOS =====\n\n");

    while(fread(&p, sizeof(Producto), 1, archi) == 1) {

        const char *colorStock = "\033[0m";

        if(p.stock == 0)
            colorStock = "\033[31m";
        else if(p.stock <= 2)
            colorStock = "\033[33m";
        else
            colorStock = "\033[32m";

        printf("Codigo: %s\n", p.codigo);
        printf("Nombre: %s\n", p.nombre);
        printf("Descripcion: %s\n", p.descripcion);
        printf("Precio: $%.2f\n", p.precio);
        printf("Stock: %s%d\033[0m\n", colorStock, p.stock);

        printf("----------------------------------------------\n\n");
    }

    fclose(archi);
}




// ---------------------------------------------------------
// Buscar producto por código
// ---------------------------------------------------------
int buscarProductoPorCodigo(char codigoBuscado[], Producto *pOut) {
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb");
    if (!archi) return 0;

    Producto p;
    while (fread(&p, sizeof(Producto), 1, archi) == 1) {
        if (strcmp(p.codigo, codigoBuscado) == 0) {
            *pOut = p;
            fclose(archi);
            return 1;
        }
    }
    fclose(archi);
    return 0;
}

// ---------------------------------------------------------
// Verificar stock
// ---------------------------------------------------------
int verificarStockDisponible(char codigoBuscado[], int cantidad) {
    Producto p;
    if (!buscarProductoPorCodigo(codigoBuscado, &p)) return 0;
    return (p.stock >= cantidad);
}

// ---------------------------------------------------------
// Actualizar stock
// ---------------------------------------------------------
int actualizarStockProducto(char codigoBuscado[], int delta) {
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb+");
    if (!archi) return 0;

    Producto p;
    while (fread(&p, sizeof(Producto), 1, archi) == 1) {
        if (strcmp(p.codigo, codigoBuscado) == 0) {

            p.stock += delta;
            if (p.stock < 0) p.stock = 0;

            fseek(archi, -sizeof(Producto), SEEK_CUR);
            fwrite(&p, sizeof(Producto), 1, archi);

            fclose(archi);
            return 1;
        }
    }

    fclose(archi);
    return 0;
}

// ---------------------------------------------------------
// Catalogo enumerado
// ---------------------------------------------------------
int mostrarCatalogoProductosEnumerado(Cliente cliente) {
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb");
    if(!archi) return 0;

    Producto p;
    int index = 1;

    printf("===== CATALOGO =====\n\n");

    while(fread(&p, sizeof(Producto), 1, archi) == 1) {

        float precioMostrar = p.precio;

        if(strcmp(cliente.tipo, "mayorista") == 0) {
            precioMostrar = p.precio * 0.70;  // 30% OFF
        }

        printf("%d) %s - %s ($%.2f)\n",
               index,
               p.codigo,
               p.nombre,
               precioMostrar
        );

        index++;
    }

    fclose(archi);

    printf("\n0) Volver\n\n");
    return index - 1;    // cantidad de productos
}


// ---------------------------------------------------------
// Obtener producto por índice
// ---------------------------------------------------------
int obtenerProductoPorIndice(int indice, Producto *pOut) {
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb");
    if (!archi) return 0;

    int contador = 0;
    Producto p;

    while (fread(&p, sizeof(Producto), 1, archi) == 1) {
        if (contador == indice) {
            *pOut = p;
            fclose(archi);
            return 1;
        }
        contador++;
    }

    fclose(archi);
    return 0;
}


// ---------------------------------------------------------
// Seleccionar por número
// ---------------------------------------------------------
int seleccionarProductoPorNumero(const char tipoCliente[], Producto *prodOut) {
    int indiceElegido = -1;

    /* Mostrar catálogo + pedir opción */
    int ok = catalogoSeleccionarProductoCliente(tipoCliente, &indiceElegido);
    if (!ok)
        return 0;   // 0 = cancelar / volver atrás

    // Ahora indiceElegido tiene el índice del producto (0-based)
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb");
    if (!archi) {
        printf("Error abriendo productos.bin\n");
        return -1;
    }

    Producto p;
    int index = 0;

    while (fread(&p, sizeof(Producto), 1, archi) == 1) {
        if (index == indiceElegido) {
            fclose(archi);
            *prodOut = p;
            return 1;       // éxito
        }
        index++;
    }

    fclose(archi);
    return -1;
}



// ===============================================================
//   CATALOGO PARA CLIENTE (SIN STOCK, PRECIOS SEGÚN TIPO)
// ===============================================================
int mostrarCatalogoCliente(char tipoCliente[], int *indiceElegido) {

    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb");
    if (!archi) {
        printf("No se pudo abrir productos.bin\n");
        pausarPantalla();
        return 0;
    }

    Producto p;
    int indice = 1;

    limpiarPantalla();
    printf("=========================================\n");
    printf("           CATALOGO DE PRODUCTOS\n");
    printf("=========================================\n\n");
    printf("   0) Volver atras\n\n");

    while (fread(&p, sizeof(Producto), 1, archi) == 1) {

        float precioFinal = p.precio;

        // Precio final segun tipo
        if (strcmp(tipoCliente, "mayorista") == 0) {
            precioFinal = p.precio * 0.70f;   // 30% OFF
        }

        printf("   %d) %-20s  $%.2f\n", indice, p.nombre, precioFinal);
        indice++;
    }

    fclose(archi);

    // === Seleccion ===
    char opcionStr[10];
    int opcion = -1;

    printf("\nSeleccione una opcion: ");
    fflush(stdin);
    gets(opcionStr);

    if (!validarNumero(opcionStr))
        return 0;

    opcion = atoi(opcionStr);

    if (opcion == 0)
        return 0;

    if (opcion < 1 || opcion >= indice)
        return 0;

    *indiceElegido = opcion - 1;
    return 1;
}


/* ============================================================
   CATALOGO PARA CLIENTE (sin stock, precios segun tipo)
   Devuelve:
     1  -> el usuario eligio un producto valido
     0  -> volvio atras o hubo error
   En indiceElegido devuelve el indice (0-based) del producto elegido
   ============================================================ */
int catalogoSeleccionarProductoCliente(char tipoCliente[], int *indiceElegido) {
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb");
    if (!archi) {
        printf("No se pudo abrir productos.bin\n");
        pausarPantalla();
        return 0;
    }

    Producto p;
    int indice = 1;

    limpiarPantalla();
    printf("===== SELECCIONAR PRODUCTO =====\n\n");
    printf("  0) Cancelar\n\n");

    while (fread(&p, sizeof(Producto), 1, archi) == 1) {
        float precioMostrar = p.precio;

        if (strcmp(tipoCliente, "mayorista") == 0) {
            precioMostrar = p.precio * 0.70f;
        }

        printf("%2d) %s - %s ($%.2f)\n",
               indice, p.codigo, p.nombre, precioMostrar);
        indice++;
    }

    fclose(archi);

    if (indice == 1) {
        printf("No hay productos cargados.\n");
        pausarPantalla();
        return 0;
    }

    char opcStr[10];
    int num;

    printf("\nElija producto por numero (0 para cancelar): ");
    fflush(stdin);
    gets(opcStr);

    if (!validarNumero(opcStr)) {
        printf("Opcion invalida\n");
        pausarPantalla();
        return 0;
    }

    num = (int)strtol(opcStr, NULL, 10);

    if (num == 0)
        return 0;

    if (num < 1 || num >= indice) {
        printf("Opcion fuera de rango\n");
        pausarPantalla();
        return 0;
    }

    *indiceElegido = num - 1;
    return 1;
}


void mostrarCatalogoClienteSoloLectura(char tipoCliente[]) {
    FILE *archi = fopen(ARCHIVOPRODUCTOS, "rb");
    if (!archi) {
        printf("No se pudo abrir productos.bin\n");
        pausarPantalla();
        return;
    }

    Producto p;
    int indice = 1;

    limpiarPantalla();
    printf("===== CATALOGO DE PRODUCTOS =====\n\n");

    while (fread(&p, sizeof(Producto), 1, archi) == 1) {

        float precioMostrar = p.precio;

        if (strcmp(tipoCliente, "mayorista") == 0) {
            precioMostrar = p.precio * 0.70f;   // 30% OFF
        }

        printf("%2d) %s - %s ($%.2f)\n",
               indice, p.codigo, p.nombre, precioMostrar);

        indice++;
    }

    fclose(archi);

    printf("\nPresione una tecla para volver...");
    pausarPantalla();
}

void administrarStock() {
    while (1) {

        limpiarPantalla();
        printf("===== CATALOGO DE PRODUCTOS =====\n\n");

        mostrarCatalogoProductos();

        char codigo[20];
        printf("\nIngrese codigo del producto (0 para volver): ");
        fflush(stdin);
        gets(codigo);

        if (strcmp(codigo, "0") == 0)
            return;

        for (int i = 0; codigo[i]; i++)
            codigo[i] = toupper(codigo[i]);

        Producto p;
        if (!buscarProductoPorCodigo(codigo, &p)) {
            printf("\nProducto no encontrado.\n");
            pausarPantalla();
            continue;
        }

        char cantStr[10];
        printf("Cantidad a agregar: ");
        fflush(stdin);
        gets(cantStr);

        if (!validarNumero(cantStr)) {
            printf("Cantidad invalida.\n");
            pausarPantalla();
            continue;
        }

        int cantidad = atoi(cantStr);
        if (cantidad <= 0) {
            printf("Cantidad invalida.\n");
            pausarPantalla();
            continue;
        }

        actualizarStockProducto(codigo, cantidad);

        printf("\n\033[0;32mStock actualizado correctamente!\033[0m\n");
        printf("Nuevo stock de %s: \033[0;32m%d\033[0m\n",
                p.nombre, p.stock + cantidad);

        printf("\nPresione una tecla para continuar...");
        pausarPantalla();

    }
}





