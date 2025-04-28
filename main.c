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
    int a = 0, r = 0; // contadores para los porcentajes de aceptados y rechazados 
     FILE *archivo;
    char linea[100];

    archivo = fopen("empleo.txt", "r"); //Se abrió el archivo con r para que solo sea lectura y no se modifique o se borre. 

    if (archivo == NULL) {
        printf("El archivo no existe.\n");
        return 1;
    }
    
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea); // se mandó a imprimir todo el contenido del archivo txt 
    }

    fclose(archivo); // archivo de referencia de habilidades y vacantes 

    do
    {
        printf("\n\n====Sistema de Gestion de Solicitudes de Empleo====\n");
        opcion = desplegarMenu("\n1)Ingresar un nuevo empleado\n2)Realizar encuesta\n3)Realizar validacion\n4)Listar empleados\n5)Opciones de la Cola y Pila\n6)Mostrar las estadisticas de los empleados\n7)Salir\n\nOpcion: ", 7);
        switch (opcion) // se le agregó al switch una opcion mas para la funcion estadistica, de momento solo va a ser una pero se le van a meter mas. _____________________________________________________________________________________________
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
                validarEmpleados(colaEmpleado, pilaAceptados, pilaRechazados, &a, &r);// se pasa la direccion de memoria de a y r pero son obsoletas
                printf("\nValidacion realizada con exito. . .");
                break;
            case 4:
                listar(*colaEmpleado);
                break;
            case 5:
                opcion = desplegarMenu("\nMenu de la Cola y Pila\n\n1)Borrar elemento de la Cola\n2)Listar Cola\n3)Borrar elemento de la Pila Aceptados\n4)Borrar elementos de la Pila Rechados\n5)Listar Pila Aceptados\n6)Listar Pila Rechazados\n7)Salir\n\nOpcion: ", 7);
                switch (opcion)
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
                }
                break;
            case 6:
                mostrarPorcentajes(a, r); // se va a llamar la funcion para mostrar la primera estadistica 
                aceptadosYrechazados(*pilaAceptados, *pilaRechazados);
                mostrarPromedio(colaEmpleado);
                promedioSalario(colaEmpleado);// hay qe meter estas estadisticas al archivo txt e imprimirlo 
                mostrarEdadRango(colaEmpleado);//rango de edades de 17 a 45
                mostrarEstados(colaEmpleado);//Estado de origen 
                mostrarGeneros(colaEmpleado);//Genero de los empleados 
                salariosExpec(colaEmpleado); //Porcentajes que indican cuanto porcentaje ganan de mas sobre respectivamente sobre el salario minimo
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
