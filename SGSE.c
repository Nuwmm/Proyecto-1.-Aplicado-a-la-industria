#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "SGSE.h"
#include "colaYpila.h"

Empleados *inicializarEmpleados()
{
    Empleados *nuevoEmpleado;
    nuevoEmpleado = (Empleados *)malloc(sizeof(Empleados));
    if(nuevoEmpleado == NULL)
        exit(-1);
    nuevoEmpleado->nombre = (char *)calloc(MAX_TEXTO, sizeof(char));
    nuevoEmpleado->puesto = (char *)calloc(MAX_TEXTO, sizeof(char));
    nuevoEmpleado->experiencia = (char *)calloc(MAX_TEXTO, sizeof(char));
    nuevoEmpleado->telefono = (char *)calloc(MAX_TEXTO, sizeof(char));
    nuevoEmpleado->departamento = (char *)calloc(MAX_TEXTO, sizeof(char));
    nuevoEmpleado->respuestas = (int *)calloc(MAX_ENCUESTA, sizeof(int));
    if(!nuevoEmpleado->nombre || !nuevoEmpleado->puesto || !nuevoEmpleado->experiencia || !nuevoEmpleado->departamento || !nuevoEmpleado->respuestas)
        exit(-1);
    // INICIALIZAR ID
    nuevoEmpleado->id=1000+rand()%1999;
    strcpy(nuevoEmpleado->departamento, "Recursos Humanos"); // Se puede modificar
    return nuevoEmpleado;
}
void capturarEmpleado(Empleados *empleado)
{
    getchar();
    printf("\nIngresa tu nombre completo: ");
    fgets(empleado->nombre, MAX_TEXTO, stdin);
    printf("\nIngresa tu edad: ");
    scanf("%d", &empleado->edad);
    getchar();
    printf("\nPuesto al que deseas postularte: ");
    fgets(empleado->puesto, MAX_TEXTO, stdin);
    printf("\nIndica tu expectativa salarial en pesos: ");
    scanf("%f", &empleado->salario);
    printf("\nNumero de telefono: ");
    getchar();
    fgets(empleado->telefono, MAX_TEXTO, stdin);
}
void listarEmpleado(Empleados empleado)
{
    printf("\nNombre: %s", empleado.nombre);
    printf("Edad: %d", empleado.edad);
    printf("\nID: %d", empleado.id);
    printf("\nPuesto: %s", empleado.puesto);
    printf("Salario: %.2f", empleado.salario);
    printf("\nTelefono: %s", empleado.telefono);
    printf("Departamento: %s", empleado.departamento);
    printf("\n====================================================\n");
}
void encuestaEmpleado(Empleados *empleado)
{
    int i=0, k;
    char respuesta[3];
    *(empleado->respuestas+i)=(empleado->edad<18) ? 0 : 1;
    i++;
    printf("\nIMORTANTE: responde las siguientes preguntas con si / no\n");
    printf("\nTienes un grado de licenciatura o mayor?\n");
    getchar();
    fgets(respuesta, 3, stdin);
    *(empleado->respuestas+i) = (strcmp(respuesta, "si")==0) ? 1 : 0;
    i++;
    printf("\nTrabajaste en alguna otra empresa?\n");
    getchar();
    fgets(respuesta, 3, stdin);
    *(empleado->respuestas+i) = (strcmp(respuesta, "si")==0) ? 1 : 0;
    i++;
    printf("\nTienes antecedentes penales?\n");
    getchar();
    fgets(respuesta, 3, stdin);
    *(empleado->respuestas+i) = (strcmp(respuesta, "si")==0) ? 0 : 1;
    i++;
    printf("\nDel 1 - 10 califica que tan apto estas para el trabajo\n");
    scanf("%d", &k);
    *(empleado->respuestas+i) = (k < 6) ? 0 : 1;
}
//Se agrego esto 
void mostrarEdadRango(ColaCircular *colaC) {
    if (validarVacio(*colaC)) {
        printf("No hay datos en la cola.\n");
        return;
    }

    int enRango = 0, total = 0;
    
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
            int edad = colaC->arrCola[i].edad;
            if (edad >= 17 && edad <= 45) {
                enRango++;
            }
            total++;
        }
    } else {
        for (int i = colaC->h; i < colaC->max; i++) {
            int edad = colaC->arrCola[i].edad;
            if (edad >= 17 && edad <= 45) {
                enRango++;
            }
            total++;
        }
        for (int i = 0; i <= colaC->t; i++) {
            int edad = colaC->arrCola[i].edad;
            if (edad >= 17 && edad <= 45) {
                enRango++;
            }
            total++;
        }
    }

    float porcentaje = total > 0 ? ((float)enRango / total) * 100 : 0;

    printf("\nCantidad de empleados entre 17 y 45 años: %d de %d (%.2f%%)\n", enRango, total, porcentaje);
}

void liberarEmpleados(Empleados *empleado)
{
    free(empleado->respuestas);
    free(empleado->departamento);
    free(empleado->telefono);
    free(empleado->experiencia);
    free(empleado->puesto);
    free(empleado->nombre);
}
