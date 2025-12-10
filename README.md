# Tresde Factory — Sistema de Gestión en C

Sistema de gestión desarrollado en C para una fábrica de impresión 3D. Incluye módulos de clientes, empleados, pedidos, inventario y un flujo completo de producción, siguiendo una arquitectura modular clara y un estilo de programación consistente.

**Calificación final:** **100 / 100**  
**Reconocimiento del profesor:**  
*"Sin dudas fue el mejor proyecto de la cursada. Trabajaron muy bien y es algo digno de felicitarlos."*  
— **Eduardo Mango**, Profesor de la cátedra

---

## Funcionalidades principales

### Login y Roles
- Inicio de sesión para **clientes** y **empleados**.  
- Roles disponibles:
  - **Administración:** gestiona empleados, modifica stock y genera reportes.  
  - **Producción:** avanza estados de pedido.  
  - **Ventas:** carga pedidos mediante catálogo y asiste al cliente.

---

## Módulos del Sistema

### Clientes
- Alta de nuevos clientes.  
- Edición de datos personales.  
- Login.  
- Consulta de pedidos propios.

---

### Empleados
- Alta de empleados (exclusivo del rol Administración).  
- Validaciones completas:
  - Verificación de legajo existente.  
  - Verificación de email existente.  
- Login por legajo o email.

---

### Pedidos
- Carga de pedidos utilizando catálogo numerado.  
- Control automático de stock:
  - **Con stock completo:** pasa directamente a *Listo para Retirar*.
  -  **Con stock parcial :** pasa a *En Impresión*. 
  - **Sin stock:** queda en *En Producción*.
    
- Estados del pedido:
  - En Producción 
  - En Impresión  
  - Finalizado
  - Retirado

---

### Producción
- Lista de pedidos en proceso.  
- Avance de estados.  
- Marcado de pedidos completados.

---

### Inventario
(Disponible únicamente para el rol Administración)  
- Modificación de stock.  
- Alta de nuevos productos.  
- Activación / desactivación de productos del catálogo.

---

## Estructura del Proyecto

/src
  main.c
  clientes.c
  clientes.h
  empleados.c
  empleados.h
  pedidos.c
  pedidos.h
  productos.c
  productos.h
  validaciones.c
  validaciones.h
  menus.c
  menus.h

---

## Estilo de Código

El proyecto adopta un estilo propio pensado para claridad, orden y mantenibilidad:

- Variables, funciones y módulos en **camelCase**.  
- `typedef struct` con nombres en formato **stNombre**.  
- Comentarios por secciones, por ejemplo:  
  //Ejercicio X  
- Arquitectura modular basada en archivos header (`.h`).  
- Uso de `gets()` para textos (bajo nuestro criterio).  
- `scanf()` para valores numéricos.  
- `fflush(stdin)` antes de cada lectura.  
- Desde `main` se envían siempre pilas y valores válidos por puntero.  
- Todos los menús incluyen opción de volver hacia atrás para evitar reiniciar el programa.

---

## Tecnologías Utilizadas

- Lenguaje **C**  
- Compilador **GCC**  
- Paradigma **estructurado modular**  
- Separación lógica mediante archivos `.h`  

---

## Futuras mejoras

- Reportes avanzados  
- Persistencia binaria completa de pedidos  
- Estadísticas automáticas por rol y módulo  
- Nuevas funciones para empleados (ej.: área de Calidad puede devolver productos a Producción)

---

## Resultados del Proyecto

El programa final cumple con todos los requisitos solicitados en el TP integrador, incluyendo:

- Sistema completo con roles (Cliente / Empleado).
- Validaciones reales de DNI, email, teléfono y legajo.
- Login funcional con archivos.
- Módulos separados y arquitectura modular.
- Flujo de pedidos, productos, clientes y empleados.
- Menús con retorno sin reiniciar el programa.

Además, el proyecto terminó compuesto por **más de 100 funciones** entre menús, validaciones y lógica interna.

---

## Nota Final Obtenida

# **100 / 100**

La máxima calificación.

---



