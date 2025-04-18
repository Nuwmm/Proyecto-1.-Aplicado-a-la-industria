#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "SGSE.h"
#include "colaYpila.h"

int main()
{
    int opcion, numEmpleados;
    // SOLICITAR DATOS
    printf("\nEmpleados que se registraran: ");
    scanf("%d", &numEmpleados);
    ColaCircular *colaEmpleado = crearColaCircular(numEmpleados);
    Pila *pilaAceptados = crearPila(numEmpleados);
    Pila *pilaRechazados = crearPila(numEmpleados);

    do
    {
        printf("\n====Sistema de Gestion de Solicitudes de Empleo====\n");
        opcion = desplegarMenu("\n1)Ingresar un nuevo empleado\n2)Realizar encuesta\n3)Realizar validacion\n4)Listar empleados\n5)Empleados ACEPTADOS\n6)Empleados RECHAZADOS\n7)Salir\n\nOpcion: ", 7);
        switch (opcion)
        {
            case 1:
                if(validarEspacio(*colaEmpleado))
                {
                    Empleados *empleado = inicializarEmpleados();
                    capturarEmpleado(empleado);
                    insertar(colaEmpleado, *empleado);
                }
                listar(*colaEmpleado);
                break;
            case 2:
                encuesta(colaEmpleado);
                break;
            case 3:
                validarEmpleados(colaEmpleado, pilaAceptados, pilaRechazados);
                printf("\nValidacion realizada con exito. . .");
                break;
            case 4:
                listar(*colaEmpleado);
                break;
            case 5:
                listarPila(*pilaAceptados);
                break;
            case 6:
                listarPila(*pilaRechazados);
                break;
        }
    }while(opcion!=7); //Se va a ir modificando
    if(colaEmpleado->h<=colaEmpleado->t)
    {
        for(int i=colaEmpleado->h; i<colaEmpleado->t; i++)
            liberarEmpleados(&colaEmpleado->arrCola[i]);
    }
    else
    {
        for (int i=colaEmpleado->h; i<colaEmpleado->max; i++)
            liberarEmpleados(&colaEmpleado->arrCola[i]);
        for (int i=0; i<=colaEmpleado->t; i++)
            liberarEmpleados(&colaEmpleado->arrCola[i]);
    }
    liberarMemoriaCola(colaEmpleado);
    free(colaEmpleado);
    colaEmpleado=NULL;
    liberarMemoriaPila(pilaAceptados);
    liberarMemoriaPila(pilaRechazados);
    if(colaEmpleado==NULL && pilaAceptados==NULL && pilaRechazados==NULL)
        printf("\nMemoria liberada con exito. . .\n");
        printf("\n");
    return 0;
}