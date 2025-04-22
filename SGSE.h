#ifndef SGSE_H_INCLUDED
#define SGSE_H_INCLUDED
#include "colaYpila.h"
#define MAX_ENCUESTA 5
#define MAX_TEXTO 50
/*
typedef struct
{
    char *nombre;
    int edad;
    int id;
    char *puesto;
    float salario;
    char *experiencia;
    int telefono;
    char *departamento;
    int respuestas[MAX_ENCUESTA];
} Empleados;
 */

//PROTOTIPOS DE FUNCIONES
Empleados *inicializarEmpleados();
void capturarEmpleado(Empleados *empleado);
void listarEmpleado(Empleados empleado);
void liberarEmpleados(Empleados *empleado);
void encuestaEmpleado(Empleados *empleado);
void mostrarEdadRango(ColaCircular *colaC);//Se agrego para el rango de 17 a 45 


#endif // SGSE_H_INCLUDED
