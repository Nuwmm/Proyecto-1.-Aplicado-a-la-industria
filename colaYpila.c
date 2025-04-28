#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SGSE.h"
#include "colaYpila.h"

// COLA

ColaCircular *crearColaCircular(int max) {
    ColaCircular *nuevaCola;
    //crear la cola y el arreglo
    nuevaCola = malloc(sizeof(ColaCircular));
    if(nuevaCola == NULL)
    {
        printf("\nError en la asignacion de memoria. . .");
        exit(-1);
    }
    nuevaCola->arrCola = (Empleados *)calloc(max,sizeof(Empleados));
    if(nuevaCola->arrCola == NULL)
    {
        printf("\nError en la asignacion de memoria. . .");
        exit(-1);
    }
    //INICIALIZAR
    nuevaCola->max = max;
    nuevaCola->h = nuevaCola->t= -1;
    return nuevaCola;
}

int validarEspacio(ColaCircular colaC){
    if ((colaC.h == 0 && colaC.t == colaC.max-1)
        || (colaC.t == colaC.h-1)){
        printf("\nNo hay espacio...\n");
        return 0;
    }
    return 1;
}

void insertar(ColaCircular *colaC, Empleados dato) {
    if (colaC->h == -1) //cola vacia
        colaC->h= 0;//INICIO DE LA FILA
    if (colaC->t == colaC->max-1)
        colaC->t = -1;

    colaC->t++;

    //INSERTA EL DATO EN LA FILA
    colaC->arrCola[colaC->t]=dato;
}

void listar(ColaCircular colaC){
    int i;
    printf("\n\tCOLA:");
    if (!validarVacio(colaC)){
        if (colaC.h<= colaC.t){
            for (i=colaC.h; i<=colaC.t ; i++)
            {
                printf("\n===================================\n");
                listarEmpleado(colaC.arrCola[i]);
            }
        }
        else {
            for (i=colaC.h; i<colaC.max; i++)
            {
                printf("\n===================================\n");
                listarEmpleado(colaC.arrCola[i]);
            }
            for (i=0; i<=colaC.t; i++)
            {
                printf("\n===================================\n");
                listarEmpleado(colaC.arrCola[i]);
            }
        }
    }
    else
        printf("  No hay datos...");
}

int validarVacio(ColaCircular colaC){
    return colaC.h == -1;
}

Empleados borrar(ColaCircular *colaC){
    Empleados aux = colaC->arrCola[colaC->h];
    if (colaC->h == colaC->t)
        colaC->h = colaC->t = -1;
    else if (colaC->h == colaC->max-1)
        colaC->h = 0;
    else
        colaC->h++;
    return aux;
}

void liberarMemoriaCola(ColaCircular *colaC){
    free(colaC->arrCola);
}

//PILA

Pila *crearPila(int max)
{
    Pila *pila = (Pila *)malloc(sizeof(Pila));
    if(pila==NULL)
        exit(-1);
    pila->arrPila = (Empleados *)calloc(max, sizeof(Empleados));
    if(pila->arrPila==NULL)
        exit(-1);
    //INICIALIZAR VALORES
    pila->cima=-1;
    pila->max=max;
    return pila;
}

void push(Empleados dato, Pila *pila)
{
    pila->cima++;
    pila->arrPila[pila->cima] = dato;
}

Empleados pop(Pila *pila)
{
    pila->cima--;
}

int pilaVacia(Pila pila)
{
    return (pila.cima==-1);
}

void listarPila(Pila pila)
{
    int i;
    for(i=pila.cima; i>=0; i--)
        listarEmpleado(pila.arrPila[i]);
}

void liberarMemoriaPila(Pila *pila){
    free(pila->arrPila);
    free(pila);
    pila = NULL;
    printf("Pila liberada . . .");
}

// ESTADISTICA 

void encuesta(ColaCircular *colaC)
{
    int i;
    if (!validarVacio(*colaC)){
        if(colaC->h <= colaC->t){
            for(int i=colaC->h; i<=colaC->t; i++)
            {
                printf("\n\tEncuesta: %s\n", colaC->arrCola[i].nombre);
                encuestaEmpleado(&colaC->arrCola[i]);
            }
        }
        else{
            for(int i=colaC->h; i<=colaC->max-1; i++)
            {
                printf("\n\tEncuesta: %s\n", colaC->arrCola[i].nombre);
                encuestaEmpleado(&colaC->arrCola[i]);
            }
            for(int i=0; i<=colaC->t; i++){
                printf("\n\tEncuesta: %s\n", colaC->arrCola[i].nombre);
                encuestaEmpleado(&colaC->arrCola[i]);
            }
        }
    }
    else
        printf("\nNo hay datos. . .");
}

void validarEmpleados(ColaCircular *colaC, Pila *pilaAceptados, Pila *pilaRechazados, int *aceptados, int *rechazados)
{   
    int r = 0, a = 0; // Contadores
    int rechazado;
    if(!validarVacio(*colaC))
    {
        if(colaC->h <= colaC->t) {
            for(int i = colaC->h; i <= colaC->t; i++)
            {
                rechazado = 1;
                for(int j = 0; j < MAX_ENCUESTA; j++)
                {
                    if(colaC->arrCola[i].respuestas[j] == 0)
                    {
                        push(colaC->arrCola[i], pilaRechazados);
                        (*rechazados)++; // contador de rechazados
                        rechazado = 0;
                        break;
                    }
                }
                if(rechazado)
                {
                    push(colaC->arrCola[i], pilaAceptados);
                    (*aceptados)++; // contador de aceptados
                }
            }
        }
        else
        {
            for(int i = colaC->h; i <= colaC->max-1; i++)
            {
                rechazado = 1;
                for(int j = 0; j < MAX_ENCUESTA; j++)
                {
                    if (colaC->arrCola[i].respuestas[j] == 0)
                    {
                        push(colaC->arrCola[i], pilaRechazados);
                        (*rechazados)++;
                        rechazado = 0;
                        break;
                    }
                }
                if (rechazado)
                {
                    push(colaC->arrCola[i], pilaAceptados);
                    (*aceptados)++;
                }
            }
            for (int i = 0; i <= colaC->t; i++)
            {
                rechazado = 1;
                for (int j = 0; j < MAX_ENCUESTA; j++)
                {
                    if (colaC->arrCola[i].respuestas[j] == 0)
                    {
                        push(colaC->arrCola[i], pilaRechazados);
                        (*rechazados)++;;
                        rechazado = 0;
                        break;
                    }
                }
                if (rechazado)
                {
                    push(colaC->arrCola[i], pilaAceptados);
                    (*aceptados)++;;
                }
            }
        }
        // Mostrar resultados
        printf("Total aceptados: %d\n", *aceptados); // se imprime la cantidad de rechazados y aceptados 
        printf("Total rechazados: %d\n", *rechazados);
    }
    else
    {
        printf("No hay datos...\n");
    }
}

//ESTADISTICAS
void aceptadosYrechazados(Pila pilaAceptados, Pila pilaRechazados){
    printf("\nEmpleados aceptados\n");
    listarPila(pilaAceptados);
    printf("\n==================================================================================\n");
    printf("\nEmpleados rechazados\n");
    listarPila(pilaRechazados);
}

void mostrarPorcentajes(int aceptados, int rechazados)// funcion que saca el porcentaje de rechazados y aceptados segun la cantidad de encuestados. 
{
    int total = aceptados + rechazados;

    if (total == 0) {
        printf("No hay candidatos evaluados.\n");
        return;
    }
    float porcentajeAceptados =  (float)aceptados / total * 100;
    float porcentajeRechazados = (float)rechazados / total * 100;
    printf("Total evaluados: %d\n", total);
    printf("La cantidad de personas aceptadas fue de %d, que corresponde al  (%.2f%%) de los candidatos.\n", aceptados, porcentajeAceptados);
    printf("La cantidad de personas rechazadas fue de  %d, que corresponde al  (%.2f%%) de los encuestados.\n", rechazados, porcentajeRechazados);
}

void mostrarPromedio(ColaCircular *colaC) {
    if (validarVacio(*colaC)) {
        printf("No hay datos en la cola.\n");
        exit;
    }
    float suma = 0.0;
    int contador = 0;
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
            suma += colaC->arrCola[i].edad;
            contador++;
        }
    } else {
        for (int i = colaC->h; i < colaC->max; i++) {
            suma += colaC->arrCola[i].edad;
            contador++;
        }
        for (int i = 0; i <= colaC->t; i++) {
            suma += colaC->arrCola[i].edad;
            contador++;
        }
    }
    suma=(float)suma / contador;
    printf("\nLa media de las edades entre los entrevistados es de %f años de edad.", suma);
} // probar la funcion con el flotamte y entero en contador y suma 

void promedioSalario(ColaCircular *colaC) {
    if (validarVacio(*colaC)) {
        printf("No hay datos en la cola.\n");
        exit;
    }
    float suma = 0.0;
    int contador = 0;
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
            suma += colaC->arrCola[i].salario;
            contador++;
        }
    } else {
        for (int i = colaC->h; i < colaC->max; i++) {
            suma += colaC->arrCola[i].salario;
            contador++;
        }
        for (int i = 0; i <= colaC->t; i++) {
            suma += colaC->arrCola[i].salario;
            contador++;
        }
    }
    suma=(float)suma / contador;
    printf("\nLa media del salario anhelado entre los entrevistados es de %f pesos.", suma);
}

void salariosExpec(ColaCircular *colaC) {
    if (validarVacio(*colaC)) {
        printf("No hay datos en la cola.\n");
        exit;
    }
    printf("El salario minimo dispuesto por la empresea es alrededor de 4500 pesos\n");
    int salarioExpectativaAlta=0, salarioExpectativaBaja=0;
    float salarioAlt=0, salarioBa=0, totalSA=0, totalSB=0, promedioSA=0, promedioSB=0;
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
            int salarioRegistrado=colaC->arrCola[i].salario; //una variable que nos permita ingresar facilmente a los valores de la cola
            if(salarioRegistrado>10000 &&salarioRegistrado<=20000){ //el if sera un parametro que dirija los salarios con expectativa alta
                salarioAlt=((float)(salarioRegistrado-4500)/4500)*100;
                totalSA+=salarioAlt; //variable que acumule los porcentajes para posteriormente saber que porcentaje de mas quieren ganar sobre salario, es decir 8500 salario bajo, al aplicar este codigo obtendremos que querra ganar un 30% mas sobre el salario minimo
                salarioExpectativaAlta++;
                promedioSA=totalSA/salarioExpectativaAlta;
            }else if(salarioRegistrado>=5000 && salarioRegistrado<10000){
                salarioBa=((float)(salarioRegistrado-4500)/4500)*100;
                totalSB+=salarioBa;
                salarioExpectativaBaja++;
                promedioSB=totalSB/salarioExpectativaBaja;
            }
            
            
        }
    } else {
        for (int i = colaC->h; i < colaC->max; i++) {
            int salarioRegistrado=colaC->arrCola[i].salario;
            if(salarioRegistrado>10000 &&salarioRegistrado<=20000){
                salarioAlt=((float)(salarioRegistrado-4500)/4500)*100;
                totalSA+=salarioAlt;
                salarioExpectativaAlta++;
                promedioSA=totalSA/salarioExpectativaAlta;
            }else if(salarioRegistrado>=5000 && salarioRegistrado<10000){
                salarioBa=((float)(salarioRegistrado-4500)/4500)*100;
                totalSB+=salarioBa;
                salarioExpectativaBaja++;
                promedioSB=totalSB/salarioExpectativaBaja;
            }
            
        }
        for (int i = 0; i <= colaC->t; i++) {
            int salarioRegistrado=colaC->arrCola[i].salario;
            if(salarioRegistrado>10000 &&salarioRegistrado<=20000){
                salarioAlt=((float)(salarioRegistrado-4500)/4500)*100;
                totalSA+=salarioAlt;
                salarioExpectativaAlta++;
                promedioSA=totalSA/salarioExpectativaAlta;

            }else if(salarioRegistrado>=5000 && salarioRegistrado<10000){
                salarioBa=((float)(salarioRegistrado-4500)/4500)*100;
                totalSB+=salarioBa;
                salarioExpectativaBaja++;
                promedioSB=totalSB/salarioExpectativaBaja;
            }
            
            
        }
    }
    if(totalSA!=0){
    printf("\nSalarios con expectativa entre el 10 y 20 mil pesos: %d\n", salarioExpectativaAlta);
    printf("\nEn total ganan un porcentaje total mas del salario minimo de la empresa entre 10-20 mil pesos es del: %.2f\n", promedioSA);}
    else printf("No ingresaste ningun salario que cumple este parametro de 10-20 mil pesos");
    if(salarioBa!=0){
    printf("\nSalarios con expectativa entre 5 a 10 a mil pesos: %d\n", salarioExpectativaBaja);
    printf("\nEn total ganan un porcentaje total mas del salario minimo de la empresa entre 5-10 mil pesos es del: %.2f\n", promedioSB);}
    else printf("No ingresaste ningun salario que cumple el parametro de 5-10 mil pesos");
}

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