#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"
#include "estructuras.h"

// ===========================================================================
// QUITAR ESPACIOS AL INICIO Y FINAL
// ===========================================================================
void quitarEspaciosExtremos(char cadena[]) {
    int inicio = 0;
    int fin = strlen(cadena) - 1;

    while (cadena[inicio] == ' ' && cadena[inicio] != '\0') {
        inicio++;
    }
    while (fin >= inicio && cadena[fin] == ' ') {
        cadena[fin] = '\0';
        fin--;
    }
    if (inicio > 0) {
        memmove(cadena, cadena + inicio, strlen(cadena + inicio) + 1);
    }
}

// ===========================================================================
// VALIDAR SOLO NUMEROS (NO SOLO CEROS, NO VACÍO)
// ===========================================================================
int validarNumero(char cadena[]) {
    quitarEspaciosExtremos(cadena);

    if (strlen(cadena) == 0) {
        printf("Debe ingresar un numero (no vacio).\n");
        return 0;
    }

    int hayNumeroReal = 0;

    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isdigit(cadena[i])) {
            printf("Solo se permiten digitos numericos.\n");
            return 0;
        }
        if (cadena[i] != '0') hayNumeroReal = 1;
    }

    if (!hayNumeroReal) {
        printf("El valor no puede ser solo ceros.\n");
        return 0;
    }

    return 1;
}

// ===========================================================================
// VALIDAR TEXTO (SOLO LETRAS Y ESPACIOS - AL MENOS UNA LETRA)
// ===========================================================================
int validarTexto(char cadena[]) {
    quitarEspaciosExtremos(cadena);

    if (strlen(cadena) == 0) {
        printf("Debe ingresar texto (no vacio).\n");
        return 0;
    }

    int tieneLetra = 0;

    for (int i = 0; cadena[i] != '\0'; i++) {
        char c = cadena[i];

        if (!(isalpha(c) || c == ' ')) {
            printf("Solo se permiten letras y espacios.\n");
            return 0;
        }

        if (isalpha(c)) tieneLetra = 1;
    }

    if (!tieneLetra) {
        printf("Debe contener al menos una letra.\n");
        return 0;
    }

    return 1;
}

// ===========================================================================
// VALIDAR DNI (7 u 8 DIGITOS + ES UNICO)
// ===========================================================================
int validarDni(char cadena[]) {
    quitarEspaciosExtremos(cadena);

    // Solo numeros
    if (!validarNumero(cadena))
        return 0;

    int len = strlen(cadena);

    // Largo valido
    if (len != 7 && len != 8) {
        printf("DNI invalido: debe tener 7 u 8 digitos.\n");
        return 0;
    }

    // Evitar DNIs con todos los digitos iguales (00000000, 11111111, etc.)
    int todosIguales = 1;
    for (int i = 1; i < len; i++) {
        if (cadena[i] != cadena[0]) {
            todosIguales = 0;
            break;
        }
    }
    if (todosIguales) {
        printf("DNI invalido: todos los digitos son iguales.\n");
        return 0;
    }

    // Unicidad en el archivo clientes.bin
    FILE *fc = fopen("clientes.bin", "rb");
    if (fc) {
        Cliente aux;
        while (fread(&aux, sizeof(Cliente), 1, fc) == 1) {
            if (strcmp(aux.dni, cadena) == 0) {
                fclose(fc);
                printf("DNI ya registrado. Ingrese otro.\n");
                return 0;
            }
        }
        fclose(fc);
    }

    return 1;
}

// ===========================================================================
// VALIDAR TELEFONO (10–12 DIGITOS + UNICO ENTRE CLIENTES Y EMPLEADOS)
// ===========================================================================

int validarTelefono(char cadena[]) {

    quitarEspaciosExtremos(cadena);

    // Solo numeros
    if (!validarNumero(cadena))
        return 0;

    int len = strlen(cadena);

    // Largo razonable (linea celular/local)
    if (len < 10 || len > 12) {
        printf("Telefono invalido: debe tener entre 10 y 12 digitos.\n");
        return 0;
    }

    // No puede comenzar con 0
    if (cadena[0] == '0') {
        printf("Telefono invalido: no puede comenzar con 0.\n");
        return 0;
    }

    // =====================================================================
    // Todos los digitos iguales (0000000000, 1111111111, etc.)
    // =====================================================================
    int todosIguales = 1;
    for (int i = 1; i < len; i++) {
        if (cadena[i] != cadena[0]) {
            todosIguales = 0;
            break;
        }
    }
    if (todosIguales) {
        printf("Telefono invalido: todos los digitos son iguales.\n");
        return 0;
    }

    // =====================================================================
    // Mas de 4 repetidos consecutivos (0000054321, 1111123456)
    // =====================================================================
    int repActual = 1;
    int repMax = 1;

    for (int i = 1; i < len; i++) {
        if (cadena[i] == cadena[i - 1]) {
            repActual++;
            if (repActual > repMax)
                repMax = repActual;
        } else {
            repActual = 1;
        }
    }

    if (repMax > 4) {
        printf("Telefono invalido: demasiados digitos repetidos.\n");
        return 0;
    }

    // =====================================================================
    // Secuencia ascendente o descendente perfecta (1234567890 / 9876543210)
    // =====================================================================
    int asc = 1;
    int desc = 1;

    for (int i = 1; i < len; i++) {
        if (cadena[i] != cadena[i-1] + 1)
            asc = 0;
        if (cadena[i] != cadena[i-1] - 1)
            desc = 0;
    }

    if (asc || desc) {
        printf("Telefono invalido: no puede ser una secuencia perfecta.\n");
        return 0;
    }

    // =====================================================================
    // Detectar secuencias ascendentes largas (ej: 123456, 234567, 345678)
    // =====================================================================
    int ascendentes = 1;
    int maxAsc = 1;
    int ascActual = 1;

    for (int i = 1; i < len; i++) {
        if (cadena[i] == cadena[i-1] + 1) {
            ascActual++;
            if (ascActual > maxAsc)
                maxAsc = ascActual;
        } else {
            ascActual = 1;
        }
    }

    if (maxAsc >= 5) {
        printf("Telefono invalido: secuencia ascendente demasiado simple.\n");
        return 0;
    }


    // =====================================================================
    // Patrones repetitivos simples (12121212, 34343434)
    // =====================================================================
    int patronSimple = 1;
    if (len >= 4) {
        for (int i = 2; i < len; i++) {
            if (cadena[i] != cadena[i - 2]) {
                patronSimple = 0;
                break;
            }
        }
    } else {
        patronSimple = 0;
    }

    if (patronSimple) {
        printf("Telefono invalido: patron demasiado simple.\n");
        return 0;
    }

    // =====================================================================
    // Unicidad en clientes.bin
    // =====================================================================
    FILE *fc = fopen("clientes.bin", "rb");
    if (fc) {
        Cliente aux;
        while (fread(&aux, sizeof(Cliente), 1, fc) == 1) {
            if (strcmp(aux.telefono, cadena) == 0) {
                fclose(fc);
                printf("Telefono ya registrado (cliente).\n");
                return 0;
            }
        }
        fclose(fc);
    }

    // =====================================================================
    // Unicidad en empleados.bin
    // =====================================================================
    FILE *fe = fopen("empleados.bin", "rb");
    if (fe) {
        Empleado aux;
        while (fread(&aux, sizeof(Empleado), 1, fe) == 1) {
            if (strcmp(aux.telefono, cadena) == 0) {
                fclose(fe);
                printf("Telefono ya registrado (empleado).\n");
                return 0;
            }
        }
        fclose(fe);
    }

    return 1;
}



// ===========================================================================
// VALIDAR LEGAJO (6 DIGITOS - SOLO EMPLEADOS)
// ===========================================================================
int validarLegajo(char cadena[]) {
    quitarEspaciosExtremos(cadena);

    if (!validarNumero(cadena))
        return 0;

    if (strlen(cadena) != 6) {
        printf("Legajo invalido: debe tener exactamente 6 digitos.\n");
        return 0;
    }

    return 1;
}

// ===========================================================================
// VALIDAR EMAIL (FORMATO + UNICIDAD EN CLIENTES Y EMPLEADOS)
// ===========================================================================

int validarEmail(char cadena[]) {
    quitarEspaciosExtremos(cadena);

    int len = strlen(cadena);

    // Largo basico
    if (len < 5) {
        printf("Email invalido: demasiado corto.\n");
        return 0;
    }

    // No debe contener espacios
    for (int i = 0; i < len; i++) {
        if (cadena[i] == ' ') {
            printf("Email invalido: contiene espacios.\n");
            return 0;
        }
    }

    // Contar @
    int posArroba = -1;
    int cantidadArroba = 0;

    for (int i = 0; i < len; i++) {
        if (cadena[i] == '@') {
            cantidadArroba++;
            posArroba = i;
        }
    }

    if (cantidadArroba == 0) {
        printf("Email invalido: falta '@'.\n");
        return 0;
    }

    if (cantidadArroba > 1) {
        printf("Email invalido: contiene mas de un '@'.\n");
        return 0;
    }

    // No puede empezar ni terminar con @
    if (posArroba == 0 || posArroba == len - 1) {
        printf("Email invalido: posicion de '@' incorrecta.\n");
        return 0;
    }

    // Verificar que haya un punto luego del @
    int posPunto = -1;
    for (int i = posArroba + 1; i < len; i++) {
        if (cadena[i] == '.') {
            posPunto = i;
            break;
        }
    }

    if (posPunto == -1) {
        printf("Email invalido: falta dominio (.com, .net, etc).\n");
        return 0;
    }

    // No puede terminar en punto
    if (cadena[len - 1] == '.') {
        printf("Email invalido: no puede terminar con punto.\n");
        return 0;
    }

    // No permitir ".."
    for (int i = 1; i < len; i++) {
        if (cadena[i] == '.' && cadena[i - 1] == '.') {
            printf("Email invalido: contiene '..'\n");
            return 0;
        }
    }

    // Evitar emails como "aaaa@aaaa"
    if (posPunto == posArroba + 1) {
        printf("Email invalido: dominio incompleto.\n");
        return 0;
    }

    // Evitar emails repetitivos
    int todosIguales = 1;
    for (int i = 1; i < len; i++) {
        if (cadena[i] != cadena[0]) {
            todosIguales = 0;
            break;
        }
    }
    if (todosIguales) {
        printf("Email invalido: no puede ser repetitivo.\n");
        return 0;
    }

    // ===================================================================
    //  CHEQUEO DE DOMINIOS REALES (final)
    // ===================================================================
    char *dominiosValidos[] = {
        ".com", ".net", ".org", ".gov", ".edu",
        ".ar", ".com.ar", ".net.ar", ".org.ar", ".edu.ar", ".gob.ar",
        NULL
    };

    int dominioOK = 0;

    for (int i = 0; dominiosValidos[i] != NULL; i++) {
        int lenDom = strlen(dominiosValidos[i]);
        if (len >= lenDom) {
            if (strcmp(cadena + (len - lenDom), dominiosValidos[i]) == 0) {
                dominioOK = 1;
                break;
            }
        }
    }

    if (!dominioOK) {
        printf("Email invalido: dominio no reconocido.\n");
        return 0;
    }

    return 1;
}



// ===========================================================================
// VALIDA DNI EXISTENTE PARA BAJAS, BUSQUEDAS Y MODIFICACIONES
// ===========================================================================
int validarDniExistente(char cadena[]) {
    quitarEspaciosExtremos(cadena);

    if (!validarNumero(cadena))
        return 0;

    int len = strlen(cadena);

    if (len != 7 && len != 8)
        return 0;

    FILE *fc = fopen("clientes.bin", "rb");
    if (!fc)
        return 0;

    Cliente aux;
    while (fread(&aux, sizeof(Cliente), 1, fc) == 1) {
        if (strcmp(aux.dni, cadena) == 0) {
            fclose(fc);
            return 1;
        }
    }

    fclose(fc);
    return 0;
}

// ===========================================================================
// VALIDA LEGAJO PARA ELIMINAR EMPLEADOS
// ===========================================================================
int validarLegajoExistente(char legajo[]) {

    FILE *archi = fopen("empleados.bin", "rb");
    if (!archi) return 0;

    Empleado e;

    while (fread(&e, sizeof(Empleado), 1, archi) == 1) {
        if (strcmp(e.legajo, legajo) == 0) {
            fclose(archi);
            return 1;   // existe
        }
    }

    fclose(archi);
    return 0;
}
