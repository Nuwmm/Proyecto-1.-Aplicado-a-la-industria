#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "SGSE.h"
#include "colaYpila.h"

int main()
{
    int opcion,opcion2, numEmpleados;
    // SOLICITAR DATOS
    printf("\nEmpleados que se registraran: ");
    scanf("%d", &numEmpleados);
    ColaCircular *colaEmpleado = crearColaCircular(numEmpleados);
    Pila *pilaAceptados = crearPila(numEmpleados);
    Pila *pilaRechazados = crearPila(numEmpleados);
    int a = 0, r = 0; // contadores para los porcentajes de aceptados y rechazados
    FILE *archivo;
    char linea[100]; //cantidad maxima de caracteres que peude leer la funcion fgets 

    archivo = fopen("empleo.txt", "r"); //Se abrio el archivo con r para que solo sea lectura y no se modifique o se borre.

    if (archivo == NULL) {
        printf("El archivo no existe. . .\n");
        exit (-1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea); // se mando a imprimir todo el contenido del archivo txt linea por linea
    }

    fclose(archivo); // se cierra el archivo y se guarda en la corrida

    do
    {
        printf("\n\n====Sistema de Gestion de Solicitudes de Empleo====\n");
        opcion = desplegarMenu("\n1)Ingresar un nuevo empleado\n2)Realizar encuesta\n3)Realizar validacion\n4)Listar empleados\n5)Opciones de la Cola y Pila\n6)Mostrar las estadisticas de los empleados\n7)Salir\n\nOpcion: ", 7);
        switch (opcion) // se le agreg� al switch una opcion mas para la funcion estadistica, de momento solo va a ser una pero se le van a meter mas. _____________________________________________________________________________________________
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
                validarEmpleados(colaEmpleado, pilaAceptados, pilaRechazados, &a, &r);// se pasa la direccion de memoria de a y r para que se guarde el contador en al variable
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
                            printf("Ingresa el ID de empleado:");
                            scanf("%d",&ID);
                            Empleados empleado=buscar(colaEmpleado,ID);
                            listarEmpleado(empleado);
                           
                        }else{
                             printf("No hay datos en la cola.\n");
                        }
                        break;
                }   
            case 6:
                archivo=fopen("Estadisticas.txt", "w");
                if(archivo!=NULL){
                    mostrarPorcentajes(a, r, archivo); // se va a llamar la funcion para mostrar la primera estadistica #1
                    aceptadosYrechazados(*pilaAceptados, *pilaRechazados, archivo); // #2
                    mostrarPromedio(colaEmpleado, archivo); // #3
                    promedioSalario(colaEmpleado, archivo);// hay qe meter estas estadisticas al archivo txt e imprimirlo #4
                    mostrarEdadRango(colaEmpleado, archivo);//rango de edades de 17 a 45 #5
                    mostrarEstados(colaEmpleado, archivo);//Estado de origen #6
                    contarGeneros(colaEmpleado, archivo);//Genero de los empleados #7
                    salariosExpec(colaEmpleado, archivo); //Porcentajes que indican cuanto porcentaje ganan de mas sobre respectivamente sobre el salario minimo #8
                    carrera(colaEmpleado, archivo); // #9
                    generoMayorP(colaEmpleado, archivo); // #10
                }
                else{
                    printf("El archivo no existe. . .\n");
                    exit(-1);
                }
                fclose(archivo);
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
    pilaAceptados=NULL;
    liberarMemoriaPila(pilaRechazados);
    pilaRechazados=NULL;
    if(colaEmpleado==NULL && pilaAceptados==NULL && pilaRechazados==NULL)
        printf("\nMemoria liberada con exito. . .\n");
        printf("\n");
    return 0;
}
