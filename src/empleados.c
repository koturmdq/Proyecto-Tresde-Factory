//
// Created by moham on 14/11/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "empleados.h"
#include "pedidos.h"
#include "productos.h"
#include "utilidades.h"
#include "validaciones.h"
#include "estructuras.h"
#include "clientes.h"


/* ============================================================
   ESTADOS EN TEXTO
   ============================================================ */
const char* estadoTexto(int e) {
    switch(e) {
        case 1: return "en preparacion";
        case 2: return "en impresion";
        case 3: return "finalizado";
        case 4: return "listo para retirar";
        default: return "desconocido";
    }
}

/* ============================================================
   CARGA INICIAL DE EMPLEADOS
   ============================================================ */
void inicializarEmpleados() {
    FILE *archi = fopen("empleados.bin", "wb");
    if(!archi) {
        printf("Error creando empleados.bin\n");
        return;
    }

    Empleado arr[3];

    strcpy(arr[0].legajo,  "611001");
    strcpy(arr[0].nombre,  "Kevin Raipane");
    strcpy(arr[0].puesto,  "produccion");
    strcpy(arr[0].telefono,"2235001000");
    strcpy(arr[0].email,   "produccion@proyectotresde.com");

    strcpy(arr[1].legajo,  "611002");
    strcpy(arr[1].nombre,  "Ayelen Ibanez");
    strcpy(arr[1].puesto,  "calidad");
    strcpy(arr[1].telefono,"2235002000");
    strcpy(arr[1].email,   "calidad@proyectotresde.com");

    strcpy(arr[2].legajo,  "611003");
    strcpy(arr[2].nombre,  "Eduardo Mango");
    strcpy(arr[2].puesto,  "administracion");
    strcpy(arr[2].telefono,"2235003000");
    strcpy(arr[2].email,   "administracion@proyectotresde.com");

    fwrite(arr, sizeof(Empleado), 3, archi);
    fclose(archi);
}

/* ============================================================
   BUSCAR EMPLEADO POR LEGAJO
   ============================================================ */
int buscarEmpleadoPorLegajo(char legajoBuscado[], Empleado *eOut) {
    FILE *archi = fopen("empleados.bin", "rb");
    if(!archi) return 0;

    Empleado aux;
    while(fread(&aux, sizeof(Empleado), 1, archi) == 1) {
        if(strcmp(aux.legajo, legajoBuscado) == 0) {
            *eOut = aux;
            fclose(archi);
            return 1;
        }
    }

    fclose(archi);
    return 0;
}

/* ============================================================
   LOGIN
   ============================================================ */
void loginEmpleado() {
    limpiarPantalla();

    char opcionStr[10];
    int opcion = -1;

    char legajo[15];
    Empleado emp;

    printf("===== LOGIN EMPLEADO =====\n\n");
    printf("1. Ingresar legajo\n");
    printf("2. Volver atras\n\n");

    printf("Elija una opcion: ");
    fflush(stdin);
    gets(opcionStr);
    opcion = atoi(opcionStr);

    if(opcion == 2) return;
    if(opcion != 1) {
        printf("\nOpcion invalida\n");
        pausarPantalla();
        return;
    }

    printf("\nIngrese su legajo (6 digitos): ");
    fflush(stdin);
    gets(legajo);

    if(!validarLegajo(legajo)) {
        printf("\nLegajo invalido\n");
        pausarPantalla();
        return;
    }

    if(!buscarEmpleadoPorLegajo(legajo, &emp)) {
        printf("\nEmpleado no encontrado\n");
        pausarPantalla();
        return;
    }

    printf("\nBienvenido/a %s (%s)\n", emp.nombre, emp.puesto);
    printf("\n");
    printf("Presione una tecla para ingresar a su terminal: ");

    pausarPantalla();

    menuEmpleadoSegunRol(emp);
}

/* ============================================================
   REDIRECCIÓN SEGÚN PUESTO
   ============================================================ */
void menuEmpleadoSegunRol(Empleado emp) {

    if(strcmp(emp.puesto, "produccion") == 0)
        menuProduccion(emp);

    else if(strcmp(emp.puesto, "calidad") == 0)
        menuCalidad(emp);

    else if(strcmp(emp.puesto, "administracion") == 0)
        menuAdministracion(emp);

    else {
        printf("Puesto desconocido\n");
        pausarPantalla();
    }
}

/* ============================================================
                   MÓDULO PRODUCCIÓN
   ============================================================ */
void menuProduccion(Empleado emp) {

    char opcionStr[10];
    int opcion = -1;

    do {
        limpiarPantalla();
        printf("=====================================\n");
        printf(" PRODUCCION - %s\n", emp.nombre);
        printf("=====================================\n");
        printf("1. Ver pedidos (1 y 2)\n");
        printf("2. Pasar a IMPRESION (1 -> 2)\n");
        printf("\n");
        printf("3. Desloguear\n\n");

        printf("Elija una opcion: ");
        fflush(stdin);
        gets(opcionStr);
        opcion = atoi(opcionStr);

        switch(opcion) {
            case 1: produccionVerPedidos(); break;
            case 2: produccionCambiarEstado1a2(); break;
            case 3: return;
            default: printf("Opcion invalida\n"); pausarPantalla();
        }

    } while(opcion != 3);
}

void produccionVerPedidos() {
    limpiarPantalla();

    printf(">>> PEDIDOS EN PREPARACION (1) <<<\n");
    printf(">>> PEDIDOS EN IMPRESION   (2) <<<\n\n");

    printf ("Pedidos Estado Preparacion\n");
    mostrarPedidosFiltrados(1);   // en preparacion
    printf ("\n\n");
    printf ("Pedidos Estado Impresion\n");
    mostrarPedidosFiltrados(2);   // en impresion

    printf ("\n");
    printf("Presione una tecla para volver atras: ");
    pausarPantalla();
}


void produccionCambiarEstado1a2() {
    cambiarEstadoPedido(1, 2, "CAMBIAR ESTADO 1 -> 2");
}



/* ============================================================
                   MÓDULO CALIDAD
   ============================================================ */
void menuCalidad(Empleado emp) {

    char opcionStr[10];
    int opcion = -1;

    do {
        limpiarPantalla();
        printf("=====================================\n");
        printf(" CALIDAD - %s\n", emp.nombre);
        printf("=====================================\n");
        printf("1. Ver pedidos en impresion (2)\n");
        printf("2. Pasar a FINALIZADO (2 -> 3)\n");
        printf("\n");
        printf("3. Desloguear\n\n");

        printf("Elija una opcion: ");
        fflush(stdin);
        gets(opcionStr);
        opcion = atoi(opcionStr);

        switch(opcion) {
            case 1: calidadVerPedidos(); break;
            case 2: calidadCambiarEstado2a3(); break;
            case 3: return;
            default: printf("Opcion invalida\n"); pausarPantalla();
        }

    } while(opcion != 3);
}

void calidadVerPedidos() {
    limpiarPantalla();
    printf(">>> MOSTRANDO PEDIDOS EN IMPRESION (2) <<<\n\n");

    mostrarPedidosFiltrados(2);

    printf("\nPresione una tecla para volver atras: ");
    pausarPantalla();
}

void calidadCambiarEstado2a3() {
    cambiarEstadoPedido(2, 3, "CAMBIAR ESTADO 2 -> 3");
}



/* ============================================================
                   MÓDULO ADMINISTRACIÓN
   ============================================================ */
void menuAdministracion(Empleado emp) {

    char opcionStr[10];
    int opcion = -1;

    do {
        limpiarPantalla();
        printf("=====================================\n");
        printf(" ADMINISTRACION - %s\n", emp.nombre);
        printf("=====================================\n");
        printf("1. Ver TODOS los pedidos\n");
        printf("2. Pasar a RETIRO (3 -> 4)\n");
        printf("3. Ver catalogo con stock\n");
        printf("4. Agregar stock a un producto\n");
        printf("5. Ver todos los clientes\n");
        printf("6. Eliminar cliente\n");
        printf("7. Ver empleados\n");
        printf("8. Agregar empleado\n");
        printf("9. Eliminar empleado\n\n");
        printf("10. Desloguear\n\n");

        printf("Elija una opcion: ");
        fflush(stdin);
        gets(opcionStr);
        opcion = atoi(opcionStr);

        switch(opcion) {
            case 1: adminVerTodosLosPedidos(); break;
            case 2: adminCambio3a4(); break;
            case 3: adminMostrarCatalogo(); break;
            case 4: administrarStock(); break;
            case 5: adminVerClientes(); break;
            case 6: eliminarClientePorDni(); break;
            case 7: adminVerEmpleados(); break;
            case 8: adminAgregarEmpleado(); break;
            case 9: eliminarEmpleadoPorLegajo(); break;
            case 10: return;

            default:
                printf("Opcion invalida\n");
                pausarPantalla();
        }

    } while (opcion != 10);
}


/* ============================================================
                   ADMIN - VER TODOS LOS PEDIDOS
   ============================================================ */
void adminVerTodosLosPedidos() {
    limpiarPantalla();
    printf(">>> MOSTRANDO TODOS LOS PEDIDOS <<<\n\n");

    mostrarPedidosTodos();

    printf("\n");
    printf("Presione una tecla para volver atras: ");

    pausarPantalla();
}

/* ============================================================
                   ADMIN - CAMBIAR 3 -> 4
   ============================================================ */
void adminCambio3a4() {
    cambiarEstadoPedido(3, 4, "CAMBIAR ESTADO 3 -> 4 (FINALIZADO -> RETIRADO)");
}



/* ============================================================
                   ADMIN - VER CATALOGO
   ============================================================ */
void adminMostrarCatalogo() {
    limpiarPantalla();
    printf(">>> CATALOGO COMPLETO (CON STOCK) <<<\n\n");

    mostrarCatalogoProductos();  // esta ya existe en productos.c

    printf("Presione una tecla para volver atras:");

    pausarPantalla();
}

/* ============================================================
                   ADMIN - AGREGAR EMPLEADO
   ============================================================ */
int generarLegajoNuevo() {
    FILE *archi = fopen("empleados.bin", "rb");
    if (!archi) return 611001;  // primer legajo por defecto

    Empleado e;
    int ultimo = 611000;

    while (fread(&e, sizeof(Empleado), 1, archi) == 1) {
        int leg = atoi(e.legajo);
        if (leg > ultimo) ultimo = leg;
    }

    fclose(archi);

    return ultimo + 1;
}

/* ============================================================
                 AGREGAR EMPLEADO (ADMIN)
   ============================================================ */
void adminAgregarEmpleado() {

    limpiarPantalla();
    printf("===== AGREGAR NUEVO EMPLEADO =====\n\n");

    char opcion[5];

    // ------------------------------------------
    // OPCIÓN PARA VOLVER ATRÁS
    // ------------------------------------------
    printf("Ingrese 1 para continuar o 0 para volver atras: ");
    fflush(stdin);
    gets(opcion);

    if (opcion[0] == '0') {
        return;   // vuelve al menu administracion
    }

    if (opcion[0] != '1') {
        printf("Opcion invalida.\n");
        pausarPantalla();
        return;
    }

    Empleado nuevo;
    char puestoStr[20];

    // ------------------------------------------
    // 1) LEGAJO AUTOINCREMENTAL
    // ------------------------------------------
    FILE *archi = fopen("empleados.bin", "rb");
    int mayor = 611000;

    if (archi) {
        Empleado aux;
        while (fread(&aux, sizeof(Empleado), 1, archi) == 1) {
            int leg = atoi(aux.legajo);
            if (leg > mayor)
                mayor = leg;
        }
        fclose(archi);
    }

    int nuevoLegajo = mayor + 1;
    sprintf(nuevo.legajo, "%d", nuevoLegajo);
    printf("\nLegajo generado automaticamente: %s\n\n", nuevo.legajo);

    // ------------------------------------------
    // 2) NOMBRE
    // ------------------------------------------
    do {
        printf("Nombre completo (0 para cancelar): ");
        fflush(stdin);
        gets(nuevo.nombre);

        if(strcmp(nuevo.nombre, "0") == 0) return;

    } while (!validarTexto(nuevo.nombre));

    // ------------------------------------------
    // 3) PUESTO
    // ------------------------------------------
    do {
        printf("Puesto (1=produccion, 2=calidad, 3=administracion, 0=volver): ");
        fflush(stdin);
        gets(puestoStr);

        if (puestoStr[0] == '0') return;

    } while (!validarNumero(puestoStr) ||
             (puestoStr[0] != '1' && puestoStr[0] != '2' && puestoStr[0] != '3'));

    if (puestoStr[0] == '1') strcpy(nuevo.puesto, "produccion");
    if (puestoStr[0] == '2') strcpy(nuevo.puesto, "calidad");
    if (puestoStr[0] == '3') strcpy(nuevo.puesto, "administracion");

    // ------------------------------------------
    // 4) TELEFONO
    // ------------------------------------------
    do {
        printf("Telefono (0 para cancelar): ");
        fflush(stdin);
        gets(nuevo.telefono);

        if(strcmp(nuevo.telefono, "0") == 0) return;

    } while (!validarNumero(nuevo.telefono));

    // ------------------------------------------
    // 5) EMAIL
    // ------------------------------------------
    do {
        printf("Email (0 para cancelar): ");
        fflush(stdin);
        gets(nuevo.email);

        if(strcmp(nuevo.email, "0") == 0) return;

    } while (!validarEmail(nuevo.email));

    // ------------------------------------------
    // 6) GUARDAR
    // ------------------------------------------
    FILE *out = fopen("empleados.bin", "ab");
    if (!out) {
        printf("Error abriendo empleados.bin\n");
        pausarPantalla();
        return;
    }

    fwrite(&nuevo, sizeof(Empleado), 1, out);
    fclose(out);

    printf("\n\033[0;32mEmpleado agregado correctamente.\033[0m\n");
    printf("Legajo: %s\n", nuevo.legajo);
    printf("Nombre: %s\n", nuevo.nombre);
    printf("Puesto: %s\n", nuevo.puesto);

    printf("Presione una tecla para volver atras: ");
    pausarPantalla();
}



/* ============================================================
                   ADMIN - VER EMPLEADOS
   ============================================================ */
void adminVerEmpleados() {

    FILE *archi = fopen("empleados.bin", "rb");
    if (!archi) {
        printf("No existen empleados cargados.\n");
        pausarPantalla();
        return;
    }

    limpiarPantalla();
    printf("===== LISTADO DE EMPLEADOS =====\n\n");

    printf("Legajo   Nombre                 Puesto          Telefono                  Email\n");
    printf("-----------------------------------------------------------------------------------------------\n");

    Empleado e;
    while (fread(&e, sizeof(Empleado), 1, archi) == 1) {

        // Colorear puesto
        if (strcmp(e.puesto, "produccion") == 0)
            printf("\033[1;34m");      // azul
        else if (strcmp(e.puesto, "calidad") == 0)
            printf("\033[1;33m");      // amarillo
        else if (strcmp(e.puesto, "administracion") == 0)
            printf("\033[1;32m");      // verde

        printf("%-8s %-22s %-15s %-13s %-25s\033[0m\n",
               e.legajo, e.nombre, e.puesto, e.telefono, e.email);

        printf("-----------------------------------------------------------------------------------------------\n");
    }

    fclose(archi);

    printf ("\nPresione una tecla para volver atras: ");
    pausarPantalla();
}

/* ============================================================
      ADMIN - VER EMPLEADOS (SIN PAUSA)
   ============================================================ */
void adminVerEmpleadosSinPausa() {

    FILE *archi = fopen("empleados.bin", "rb");
    if (!archi) {
        printf("No existen empleados cargados.\n");
        return;
    }

    limpiarPantalla();
    printf("===== LISTADO DE EMPLEADOS =====\n\n");

    printf("Legajo   Nombre                 Puesto          Telefono                  Email\n");
    printf("-----------------------------------------------------------------------------------------------\n");

    Empleado e;
    while (fread(&e, sizeof(Empleado), 1, archi) == 1) {

        if (strcmp(e.puesto, "produccion") == 0)
            printf("\033[1;34m");
        else if (strcmp(e.puesto, "calidad") == 0)
            printf("\033[1;33m");
        else if (strcmp(e.puesto, "administracion") == 0)
            printf("\033[0;32m");

        printf("%-8s %-22s %-15s %-13s %-25s\033[0m\n",
               e.legajo, e.nombre, e.puesto, e.telefono, e.email);

        printf("-----------------------------------------------------------------------------------------------\n");
    }

    fclose(archi);
}




/* ============================================================
      ADMIN - EMPLEADO CON PEDIDOS ACTIVOS
   ============================================================ */
int empleadoTienePedidosActivos(Empleado e) {
    FILE *archi = fopen(ARCHIVOPEDIDOS, "rb");
    if (!archi) return 0;

    Pedido p;

    while (fread(&p, sizeof(Pedido), 1, archi) == 1) {
        if (p.estado == 1 || p.estado == 2 || p.estado == 3) {
            fclose(archi);
            return 1;   // hay pedidos activos → no se puede eliminar
        }
    }

    fclose(archi);
    return 0;
}

/* ============================================================
      ADMIN - ELIMINAR EMPLEADO POR LEGAJO
   ============================================================ */
void eliminarEmpleadoPorLegajo() {

    char legajo[20];
    char conf[5];
    char repetir[5];
    Empleado e;

    do {
        adminVerEmpleadosSinPausa();

        printf("\nIngrese legajo del empleado a eliminar (0 para volver): ");
        fflush(stdin);
        gets(legajo);

        // Volver atras (al menu de empleados)
        if (strcmp(legajo, "0") == 0)
            break;

        if (!validarLegajoExistente(legajo)) {
            printf("\nLegajo no encontrado.\n");
            pausarPantalla();
            continue;
        }

        if (!buscarEmpleadoPorLegajo(legajo, &e)) {
            printf("\nError al recuperar datos del empleado.\n");
            pausarPantalla();
            continue;
        }

        // BLOQUEO PRO (Easter Egg)
        if (empleadoTienePedidosActivos(e)) {

            printf("\n\033[0;31m------------------------------------------\033[0m\n");
            printf("\033[0;31mNO SE PUEDE ELIMINAR ESTE EMPLEADO\033[0m\n\n");

            printf("Existen pedidos activos en el sistema.\n");
            printf("Debe finalizarse la produccion antes.\n");

            printf("\n------------------------------------------\n");
            printf("\nPresione una tecla para volver atras...");
            pausarPantalla();

            continue;   // vuelve a pedir otro legajo
        }

        printf("\nSeguro que desea eliminar a %s (%s)? (s/n): ",
               e.nombre, e.puesto);
        fflush(stdin);
        gets(conf);

        if (conf[0] != 's' && conf[0] != 'S') {
            printf("\nOperacion cancelada.\n");
            pausarPantalla();
            break;   // vuelve al menu de empleados
        }

        // Eliminacion con archivo temporal
        FILE *origen = fopen("empleados.bin", "rb");
        FILE *temp = fopen("empleados_temp.bin", "wb");

        if (!origen || !temp) {
            printf("\nError al abrir archivos para eliminar.\n");
            if (origen) fclose(origen);
            if (temp) fclose(temp);
            pausarPantalla();
            break;
        }

        Empleado aux;
        int eliminado = 0;

        while (fread(&aux, sizeof(Empleado), 1, origen) == 1) {
            if (strcmp(aux.legajo, legajo) != 0)
                fwrite(&aux, sizeof(Empleado), 1, temp);
            else
                eliminado = 1;
        }

        fclose(origen);
        fclose(temp);

        remove("empleados.bin");
        rename("empleados_temp.bin", "empleados.bin");

        if (eliminado)
            printf("\nEmpleado eliminado correctamente.\n");
        else
            printf("\nNo se pudo eliminar el empleado.\n");

        printf("\nDesea eliminar otro empleado? (s/n): ");
        fflush(stdin);
        gets(repetir);

    } while (repetir[0] == 's' || repetir[0] == 'S');
}





