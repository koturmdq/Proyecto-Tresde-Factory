#include <stdio.h>
#include <stdlib.h>

#include "utilidades.h"
#include "menus.h"

int main() {

    limpiarPantalla();
    animacionImpresora3D(35, 70);

    //inicializacionPrimeraVez();   // SOLO una vez si fuera necesario

    menuPrincipal();
    return 0;
}
