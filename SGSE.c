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
    nuevoEmpleado->estado = (char *)calloc(MAX_TEXTO, sizeof(char));
    if (!nuevoEmpleado->estado) exit(-1);
    nuevoEmpleado->genero = (char *)calloc(MAX_TEXTO, sizeof(char));
    if (!nuevoEmpleado->genero) exit(-1);

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
    printf("\n¿Cuál es tu género? (Masculino/Femenino/Otro): ");
    fgets(empleado->genero, MAX_TEXTO, stdin);
    printf("\nPuesto al que deseas postularte: ");
    fgets(empleado->puesto, MAX_TEXTO, stdin);
    printf("\nIndica tu expectativa salarial en pesos: ");
    scanf("%f", &empleado->salario);
    printf("\nNumero de telefono: ");
    getchar();
    fgets(empleado->telefono, MAX_TEXTO, stdin);
    printf("\n¿En qué estado resides?: ");
    fgets(empleado->estado, MAX_TEXTO, stdin);
    


}
void listarEmpleado(Empleados empleado)
{
    printf("\nNombre: %s", empleado.nombre);
    printf("Edad: %d", empleado.edad);
    printf("\nGénero: %s", empleado.genero);
    printf("ID: %d", empleado.id);
    printf("\nPuesto: %s", empleado.puesto);
    printf("Salario: %.2f", empleado.salario);
    printf("\nTelefono: %s", empleado.telefono);
    printf("Estado: %s", empleado.estado);
    printf("\nDepartamento: %s", empleado.departamento);
   

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
//Agregado 
void mostrarEdadRango(ColaCircular *colaC) {
    if (validarVacio(*colaC)) {
        printf("No hay datos en la cola.\n");
        return;
    }

    int enRango = 0, total = 0;
    
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
            int edad = colaC->arrCola[i].edad;
            if (edad >= 25 && edad <= 45) {
                enRango++;
            }
            total++;
        }
    } else {
        for (int i = colaC->h; i < colaC->max; i++) {
            int edad = colaC->arrCola[i].edad;
            if (edad >= 25 && edad <= 45) {
                enRango++;
            }
            total++;
        }
        for (int i = 0; i <= colaC->t; i++) {
            int edad = colaC->arrCola[i].edad;
            if (edad >= 25 && edad <= 45) {
                enRango++;
            }
            total++;
        }
    }

    float porcentaje = total > 0 ? ((float)enRango / total) * 100 : 0;

    printf("\nCantidad de empleados entre 25 y 45 años: %d empleados de %d (%.2f%%)\n", enRango, total, porcentaje);
}
void mostrarEstados(ColaCircular *colaC) {
    if (validarVacio(*colaC)) {
        printf("\nNo hay empleados registrados.\n");
        return;
    }

    printf("\n=== Estados de residencia de los empleados ===\n");

    char estadosUnicos[100][MAX_TEXTO]; // máximo 100 estados únicos
    int cantidadEstados = 0;

    int i = colaC->h;
    while (1) {
        int yaExiste = 0;
        for (int j = 0; j < cantidadEstados; j++) {
            if (strcmp(estadosUnicos[j], colaC->arrCola[i].estado) == 0) {
                yaExiste = 1;
                break;
            }
        }

        if (!yaExiste) {
            strcpy(estadosUnicos[cantidadEstados], colaC->arrCola[i].estado);
            cantidadEstados++;
        }

        if (i == colaC->t) break;
        i = (i + 1) % colaC->max;
    }

    for (int k = 0; k < cantidadEstados; k++) {
        printf(" - %s", estadosUnicos[k]);
    }
}

void mostrarGeneros(ColaCircular *colaC) {
    if (validarVacio(*colaC)) {
        printf("\nNo hay empleados registrados.\n");
        return;
    }

    printf("\n=== Géneros de los empleados registrados ===\n");

    char generosUnicos[10][MAX_TEXTO]; // máximo 10 tipos de género únicos
    int conteoGeneros[10] = {0};
    int cantidadGeneros = 0;

    int i = colaC->h;
    while (1) {
        int encontrado = 0;
        for (int j = 0; j < cantidadGeneros; j++) {
            if (strcmp(generosUnicos[j], colaC->arrCola[i].genero) == 0) {
                conteoGeneros[j]++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            strcpy(generosUnicos[cantidadGeneros], colaC->arrCola[i].genero);
            conteoGeneros[cantidadGeneros] = 1;
            cantidadGeneros++;
        }

        if (i == colaC->t) break;
        i = (i + 1) % colaC->max;
    }

    for (int k = 0; k < cantidadGeneros; k++) {
        printf(" - %s: %d empleados\n", generosUnicos[k], conteoGeneros[k]);
    }
}
void liberarEmpleados(Empleados *empleado)
{
    free(empleado->respuestas);
    free(empleado->departamento);
    free(empleado->telefono);
    free(empleado->experiencia);
    free(empleado->puesto);
    free(empleado->nombre);
    free(empleado->estado);
    free(empleado->genero);
}
