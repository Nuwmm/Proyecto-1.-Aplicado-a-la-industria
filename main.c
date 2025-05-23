#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "SGSE.h"
#include "colaYpila.h"

int main()
{
    int opcion, opcion2, numEmpleados;
    printf("\nEmpleados que se registraran: ");
    scanf("%d", &numEmpleados);
    ColaCircular *colaEmpleado = crearColaCircular(numEmpleados);
    Pila *pilaAceptados = crearPila(numEmpleados);
    Pila *pilaRechazados = crearPila(numEmpleados);
    int a = 0, r = 0;
    FILE *archivo;
    char linea[100]; 

    archivo = fopen("empleo.txt", "r");

    if (archivo == NULL) {
        printf("El archivo no existe. . .\n");
        exit (-1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea);
    }

    fclose(archivo);

    do
    {
        printf("\n\n====Sistema de Gestion de Solicitudes de Empleo====\n");
        opcion = desplegarMenu("\n1)Ingresar un nuevo empleado\n2)Realizar encuesta\n3)Realizar validacion\n4)Listar empleados\n5)Opciones de la Cola y Pila\n6)Mostrar las estadisticas de los empleados\n7)Salir\n\nOpcion: ", 7);
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
                validarEmpleados(colaEmpleado, pilaAceptados, pilaRechazados, &a, &r);
                printf("\nValidacion realizada con exito. . .");
                break;
            case 4:
                listar(*colaEmpleado);
                break;
            case 5:
                opcion2 = desplegarMenu("\nMenu de la Cola y Pila\n\n1)Borrar elemento de la Cola\n2)Listar Cola\n3)Borrar elemento de la Pila Aceptados\n4)Borrar elementos de la Pila Rechados\n5)Listar Pila Aceptados\n6)Listar Pila Rechazados\n7)Buscar Empleado\n\nOpcion: ", 8);
                switch (opcion2)
                {
                    case 1:
                        if(!validarVacio(*colaEmpleado))
                            borrar(colaEmpleado);
                        else
                            printf("\nNo hay datos en la cola. . .\n");
                        break;
                    case 2:
                        listar(*colaEmpleado);
                        break;
                    case 3:
                        if(!pilaVacia(*pilaAceptados))
                            pop(pilaAceptados);
                        else
                            printf("\nNo hay datos en la pila. . .\n");
                        break;
                    case 4:
                        if(!pilaVacia(*pilaRechazados))
                            pop(pilaRechazados);
                        else
                            printf("\nNo hay datos en la pila. . .\n");
                        break;
                    case 5:
                        if(!pilaVacia(*pilaAceptados))
                            listarPila(*pilaAceptados);
                        break;
                    case 6:
                        if(!pilaVacia(*pilaRechazados))
                            listarPila(*pilaRechazados);
                        break;
                    case 7: 
                        if (!validarVacio(*colaEmpleado)) {
                            int ID;
                            printf("Ingresa el ID del empleado: ");
                            scanf("%d",&ID);
                            Empleados *empleado=buscar(colaEmpleado, ID);
                            if(empleado!=NULL){
                                listarEmpleado(*empleado);
                            }else{
                                printf("No existe un usuario con ese ID");
                            }
                        }else
                            printf("No hay datos en la cola.\n");
                        break;
                }
            case 6:
                archivo=fopen("Estadisticas.txt", "w");
                if(archivo!=NULL){
                    mostrarPorcentajes(a, r, archivo);
                    aceptadosYrechazados(*pilaAceptados, *pilaRechazados, archivo);
                    mostrarPromedio(colaEmpleado, archivo);
                    promedioSalario(colaEmpleado, archivo);
                    mostrarEdadRango(colaEmpleado, archivo);
                    mostrarEstados(colaEmpleado, archivo);
                    contarGeneros(colaEmpleado, archivo);
                    salariosExpec(colaEmpleado, archivo);
                    carrera(colaEmpleado, archivo);
                    generoMayorP(colaEmpleado, archivo);
                }
                else{
                    printf("El archivo no existe. . .\n");
                    exit(-1);
                }
                fclose(archivo);
        }
    }while(opcion!=7);
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
    pilaAceptados=NULL;
    liberarMemoriaPila(pilaRechazados);
    pilaRechazados=NULL;
    if(colaEmpleado==NULL && pilaAceptados==NULL && pilaRechazados==NULL)
        printf("\nMemoria liberada con exito. . .\n");
        printf("\n");
    return 0;
}
