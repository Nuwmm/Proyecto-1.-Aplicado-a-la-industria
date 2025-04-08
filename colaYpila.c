#include <stdio.h>
#include <stdlib.h>
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
        for(int i=colaC->h; i<=colaC->t; i++)
        {
            printf("\n\tEncuesta: %s\n", colaC->arrCola[i].nombre);
            encuestaEmpleado(&colaC->arrCola[i]);
        }
    }
    else
        printf("\nNo hay datos. . .");
}

void validarEmpleados(ColaCircular *colaC, Pila *pilaAceptados, Pila *pilaRechazados)
{
    int rechazado;
    if(!validarVacio(*colaC))
    {
        if(colaC->h<=colaC->t)
            for(int i=colaC->h; i<=colaC->t; i++)
            {
                rechazado=1;
                for(int j=0; j<MAX_ENCUESTA; j++)
                {
                    if((colaC->arrCola[i].respuestas[j]==0))
                    {
                        push(colaC->arrCola[i], pilaRechazados);
                        rechazado=0;
                        break;
                    }
                }
            if(rechazado)
                push(colaC->arrCola[i], pilaAceptados);
            }
        else
        {
            for(int i=colaC->h; i<=colaC->max; i++)
            {
                rechazado=1;
                for(int j=0; j<MAX_ENCUESTA; j++)
                    {
                        if(colaC->arrCola[i].respuestas[j]==0)
                        {
                            push(colaC->arrCola[i], pilaRechazados);
                            rechazado=0;
                            break;
                        }
                    }
            if(rechazado)
                push(colaC->arrCola[i], pilaAceptados);
            }
            for(int i=0; i<=colaC->t; i++)
            {
                rechazado=1;
                for(int j=0; j<MAX_ENCUESTA; j++)
                    {
                        if(colaC->arrCola[i].respuestas[j]==0)
                        {
                            push(colaC->arrCola[i], pilaRechazados);
                            rechazado=0;
                            break;
                        }
                    }
                if(rechazado)
                    push(colaC->arrCola[i], pilaAceptados);
            }
        }
    }
    else
        printf("No hay datos...");
}