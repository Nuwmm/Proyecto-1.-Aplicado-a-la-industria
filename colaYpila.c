#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SGSE.h"
#include "colaYpila.h"

ColaCircular *crearColaCircular(int max) {
    ColaCircular *nuevaCola;
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
    if (colaC->h == -1)
        colaC->h= 0;
    if (colaC->t == colaC->max-1)
        colaC->t = -1;
    colaC->t++;
    colaC->arrCola[colaC->t]=dato;
}

void listar(ColaCircular colaC){
    int i;
    if (!validarVacio(colaC)){
        if (colaC.h<= colaC.t){
            for (i=colaC.h; i<=colaC.t ; i++)
            {
                printf("\n===================================\n");
                listarEmpleado(*(colaC.arrCola+i));
            }
        }
        else {
            for (i=colaC.h; i<colaC.max; i++)
            {
                printf("\n===================================\n");
                listarEmpleado(*(colaC.arrCola+i));
            }
            for (i=0; i<=colaC.t; i++)
            {
                printf("\n===================================\n");
                listarEmpleado(*(colaC.arrCola+i));
            }
        }
    }
    else
        printf("  No hay datos...");
}

void listarArchivo(ColaCircular colaC, FILE *archivo){
    int i;
    if (!validarVacio(colaC)){
        if (colaC.h<= colaC.t){
            for (i=colaC.h; i<=colaC.t ; i++)
            {
                fprintf(archivo, "\n===================================\n");
                listarEmpleadoArchivo(*(colaC.arrCola+i), archivo);
            }
        }
        else {
            for (i=colaC.h; i<colaC.max; i++)
            {
                fprintf(archivo, "\n===================================\n");
                listarEmpleadoArchivo(*(colaC.arrCola+i), archivo);
            }
            for (i=0; i<=colaC.t; i++)
            {
                fprintf(archivo, "\n===================================\n");
                listarEmpleadoArchivo(*(colaC.arrCola+i), archivo);
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

Empleados *buscar(ColaCircular *colaC, int ID){
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
            if (ID==colaC->arrCola[i].id){
                printf("\nEl empleado con el ID %d es:\n", ID);
                return &colaC->arrCola[i];
            }
            
        }
    }else{
        for(int i = colaC->h; i <= colaC->max-1; i++){
            if (ID==colaC->arrCola[i].id){
                printf("\nEl empleado con el ID %d es:\n", ID);
                return &colaC->arrCola[i];
            }
        }
        for(int i = 0; i <= colaC->t; i++){
            if (ID==colaC->arrCola[i].id){
                printf("\nEl empleado con el ID %d es:\n", ID);
                return &colaC->arrCola[i];
            }
        }
    }
    printf("\nNo existe un empleado con el ID: %d . . .\n", ID);
    return NULL;
}

void liberarMemoriaCola(ColaCircular *colaC){
    free(colaC->arrCola);
}

Pila *crearPila(int max){
    Pila *pila = (Pila *)malloc(sizeof(Pila));
    if(pila==NULL)
        exit(-1);
    pila->arrPila = (Empleados *)calloc(max, sizeof(Empleados));
    if(pila->arrPila==NULL)
        exit(-1);
    pila->cima=-1;
    pila->max=max;
    return pila;
}

void push(Empleados dato, Pila *pila){
    pila->cima++;
    pila->arrPila[pila->cima] = dato;
}

Empleados pop(Pila *pila){
    pila->cima--;
}

int pilaVacia(Pila pila){
    return (pila.cima==-1);
}

void listarPila(Pila pila){
    int i;
    for(i=pila.cima; i>=0; i--)
        listarEmpleado(*(pila.arrPila+i));
}

void listarPilaArchivo(Pila pila, FILE *archivo){
    int i;
    for(i=pila.cima; i>=0; i--)
        listarEmpleadoArchivo(*(pila.arrPila+i), archivo);
}

void liberarMemoriaPila(Pila *pila){
    free(pila->arrPila);
    free(pila);
    pila = NULL;
    printf("Pila liberada . . .");
}

void encuesta(ColaCircular *colaC){
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

void validarEmpleados(ColaCircular *colaC, Pila *pilaAceptados, Pila *pilaRechazados, int *aceptados, int *rechazados){
    int r = 0, a = 0;
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
                        (*rechazados)++;
                        rechazado = 0;
                        break;
                    }
                }
                if(rechazado)
                {
                    push(colaC->arrCola[i], pilaAceptados);
                    (*aceptados)++;
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
        printf("Total aceptados: %d\n", *aceptados);
        printf("Total rechazados: %d\n", *rechazados);
    }
    else
    {
        printf("No hay datos...\n");
    }
}

void aceptadosYrechazados(Pila pilaAceptados, Pila pilaRechazados, FILE *archivo){
    fprintf(archivo, "\n\t=====Empleados aceptados=====\n");
    listarPilaArchivo(pilaAceptados, archivo);
    fprintf(archivo, "\n\t=====Empleados rechazados=====\n");
    listarPilaArchivo(pilaRechazados, archivo);
}

void mostrarPorcentajes(int aceptados, int rechazados, FILE *archivo){// funcion que saca el porcentaje de rechazados y aceptados segun la cantidad de encuestados.
    int total = aceptados + rechazados;

    if (total == 0) {
        fprintf(archivo, "No hay candidatos evaluados.\n");
        return;
    }
    float porcentajeAceptados =  (float)aceptados / total * 100;
    float porcentajeRechazados = (float)rechazados / total * 100;
    fprintf(archivo, "Total evaluados: %d\n", total);
    fprintf(archivo, "La cantidad de personas aceptadas fue de %d, que corresponde al  (%.2f%%) de los candidatos.\n", aceptados, porcentajeAceptados);
    fprintf(archivo, "La cantidad de personas rechazadas fue de  %d, que corresponde al  (%.2f%%) de los encuestados.\n", rechazados, porcentajeRechazados);
}

void mostrarPromedio(ColaCircular *colaC, FILE *archivo) {
    if (validarVacio(*colaC)) {
        fprintf(archivo, "No hay datos en la cola.\n");
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
    fprintf(archivo, "\nLa media de las edades entre los entrevistados es de %f a�os de edad.", suma);
    fprintf(archivo, "======================================================================");
}

void promedioSalario(ColaCircular *colaC, FILE *archivo) {
    if (validarVacio(*colaC)) {
        fprintf(archivo, "No hay datos en la cola.\n");
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
    fprintf(archivo, "\nLa media del salario anhelado entre los entrevistados es de %f pesos.", suma);
    fprintf(archivo, "======================================================================");
}

void contarGeneros(ColaCircular *colaC, FILE *archivo){
    int i;
    int hombres = 0, mujeres = 0;
    if (!validarVacio(*colaC)){
        if (colaC->h<= colaC->t){
            for (i=colaC->h; i<=colaC->t ; i++){
                if (colaC->arrCola[i].INE.genero[0] == 'M'|| colaC->arrCola[i].INE.genero[0] == 'm') {
                    hombres++;
                } else if (colaC->arrCola[i].INE.genero[0] == 'F'|| colaC->arrCola[i].INE.genero[0] == 'f') {
                    mujeres++;
                }
            }
            fprintf(archivo, "Hombres (M): %d\n", hombres);
            fprintf(archivo, "Mujeres (F): %d\n", mujeres);
        }

        else {
            for (i=colaC->h; i<colaC->max; i++){
                if (colaC->arrCola[i].INE.genero[0] == 'M'|| colaC->arrCola[i].INE.genero[0] == 'm') {
                    hombres++;
                } else if (colaC->arrCola[i].INE.genero[0] == 'F'|| colaC->arrCola[i].INE.genero[0] == 'f') {
                    mujeres++;
                }
            }
            for (i=0; i<=colaC->t; i++){
                if (colaC->arrCola[i].INE.genero[0] == 'M'|| colaC->arrCola[i].INE.genero[0] == 'm') {
                    hombres++;
                } else if (colaC->arrCola[i].INE.genero[0] == 'F'|| colaC->arrCola[i].INE.genero[0] == 'f') {
                    mujeres++;
                }
            }
                printf("Hombres (M): %d\n", hombres);
                printf("Mujeres (F): %d\n", mujeres);
            }
    }else{
        printf("  No hay datos...");
    }
}

void salariosExpec(ColaCircular *colaC, FILE *archivo) {
    if (validarVacio(*colaC)) {
        fprintf(archivo, "No hay datos en la cola.\n");
        exit;
    }
    fprintf(archivo, "El salario minimo dispuesto por la empresea es alrededor de 4500 pesos\n");
    int salarioExpectativaAlta=0, salarioExpectativaBaja=0;
    float salarioAlt=0, salarioBa=0, totalSA=0, totalSB=0, promedioSA=0, promedioSB=0;
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
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
        if(totalSA!=0){
    fprintf(archivo, "\nLa personas que pidieron salarios entre el 10 y 20 mil pesos son: %d\n", salarioExpectativaAlta);
    fprintf(archivo, "\nEl promedio de porcentaje de expectativa alta respecto al salario minimo de las personas que ingresaron un salario entre 10-20 mil pesos es del: (%.2f%%)", promedioSA);
    } else
        fprintf(archivo, "No ingresaste ningun salario que cumple este parametro de 10-20 mil pesos");
    if(salarioBa!=0){
        fprintf(archivo, "\nLas personas que pidieron salarios entre 5 a 10 a mil pesos son: %d\n", salarioExpectativaBaja);
    fprintf(archivo, "\nEl promedio de porcentaje de expectativa baja  respecto al salario minimo de las personas que ingresaron un salario entre 5-10 mil pesos es del: (%.2f%%)", promedioSB);
    }
    else
        fprintf(archivo, "\nNo ingresaste ningun salario que cumple el parametro de 5-10 mil pesos");
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
    if(totalSA!=0){
    fprintf(archivo, "\nLa personas que pidieron salarios entre el 10 y 20 mil pesos son: %d\n", salarioExpectativaAlta);
    fprintf(archivo, "\nEl promedio de porcentaje de expectativa alta respecto al salario minimo de las personas que ingresaron un salario entre 10-20 mil pesos es del: (%.2f%%)", promedioSA);
    } else
        fprintf(archivo, "No ingresaste ningun salario que cumple este parametro de 10-20 mil pesos");
    if(salarioBa!=0){
        fprintf(archivo, "\nLas personas que pidieron salarios entre 5 a 10 a mil pesos son: %d\n", salarioExpectativaBaja);
    fprintf(archivo, "\nEl promedio de porcentaje de expectativa baja  respecto al salario minimo de las personas que ingresaron un salario entre 5-10 mil pesos es del: (%.2f%%)", promedioSB);
    }
    else
        fprintf(archivo, "No ingresaste ningun salario que cumple el parametro de 5-10 mil pesos");
    }
}

void mostrarEdadRango(ColaCircular *colaC, FILE *archivo) {
    if (validarVacio(*colaC)) {
        fprintf(archivo, "No hay datos en la cola.\n");
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
    fprintf(archivo, "\nCantidad de empleados entre 25 y 45 a�os: %d empleados de %d (%.2f%%)\n", enRango, total, porcentaje);
    fprintf(archivo, "======================================================================");
}

void mostrarEstados(ColaCircular *colaC, FILE *archivo) {
    if (validarVacio(*colaC)) {
        fprintf(archivo, "\nNo hay empleados registrados.\n");
        return;
    }

    fprintf(archivo, "\n=== Estados de residencia de los empleados ===\n");

    char estados[100][MAX_TEXTO];
    int numEstados = 0;

    int i = colaC->h;
    do {
        int repetido = 0;
        for (int j = 0; j < numEstados; j++) {
            if (strcmp(estados[j], colaC->arrCola[i].INE.estado) == 0) {
                repetido = 1;
                break;
            }
        }
        if (!repetido) {
            strcpy(estados[numEstados++], colaC->arrCola[i].INE.estado);
        }

        i++;
        if (i == colaC->max) i = 0;
    }while (i != (colaC->t + 1) % colaC->max);
    for (int i = 0; i < numEstados; i++) {
        fprintf(archivo, " - %s", estados[i]);
    }
}

void carrera(ColaCircular *colaC, FILE *archivo){
    int i;
    int v1=0, v2=0, v3=0, v4=0, v5=0;
    if (!validarVacio(*colaC)){
        if (colaC->h<= colaC->t){
            for (i=colaC->h; i<=colaC->t ; i++){
                if (colaC->arrCola[i].puesto[0] == '1'){
                    v1++;
                }
                if (colaC->arrCola[i].puesto[0] == '2'  ) {
                    v2++;
                }
                if (colaC->arrCola[i].puesto[0] == '3'){
                    v3++;
                }
                if (colaC->arrCola[i].puesto[0] == '4'){
                    v4++;
                }
                if (colaC->arrCola[i].puesto[0] == '5'){
                    v5++;
                }
            }
            fprintf(archivo, "\nSolicitudes para asistente de pruebas de software: %d\n", v1);
            fprintf(archivo, "Solicitudes para ingeniero de redes : %d\n", v2);
            fprintf(archivo, "Solicitudes para Auxiliar de control de versiones %d\n", v3);
            fprintf(archivo, "Solicitudes para Soporte Tecnico %d\n", v4);
            fprintf(archivo, "Solicitudes para Especialista en Ciberseguirdad %d\n", v5);
        }
        else {
            for (i=colaC->h; i<colaC->max; i++){
                if (colaC->arrCola[i].puesto[0] == '1'){
                    v1++;
                }
                if (colaC->arrCola[i].puesto[0] == '2'  ) {
                    v2++;
                }
                if (colaC->arrCola[i].puesto[0] == '3'){
                    v3++;
                }
                if (colaC->arrCola[i].puesto[0] == '4'){
                    v4++;
                }
                if (colaC->arrCola[i].puesto[0] == '5'){
                    v5++;
                }
            }
            for (i=0; i<=colaC->t; i++){
                if (colaC->arrCola[i].puesto[0] == '1'){
                    v1++;
                }
                if (colaC->arrCola[i].puesto[0] == '2'  ) {
                    v2++;
                }
                if (colaC->arrCola[i].puesto[0] == '3'){
                    v3++;
                }
                if (colaC->arrCola[i].puesto[0] == '4'){
                    v4++;
                }
                if (colaC->arrCola[i].puesto[0] == '5'){
                    v5++;
                }
            }
                fprintf(archivo, "\nSolicitudes para asistente de pruebas de software: %d\n", v1);
                fprintf(archivo, "Solicitudes para ingeniero de redes : %d\n", v2);
                fprintf(archivo, "Solicitudes para Auxiliar de control de versiones %d\n", v3);
                fprintf(archivo, "Solicitudes para Soporte Tecnico %d\n", v4);
                fprintf(archivo, "Solicitudes para Ciberseguirdad%d\n", v5);
        }
    }else{
        fprintf(archivo, "\nNo hay datos...");
    }
}

void generoMayorP(ColaCircular *colaC, FILE *archivo){
    fprintf(archivo, "======================================================================");
    if (validarVacio(*colaC)) {
        fprintf(archivo, "No hay datos en la cola.\n");
        exit;
    }
    float sumaM = 0.0, sumaF=0.0;
    int contadorM = 0, contadorF=0;
    if (colaC->h <= colaC->t) {
        for (int i = colaC->h; i <= colaC->t; i++) {
            if(colaC->arrCola[i].INE.genero[0]=='M'||colaC->arrCola[i].INE.genero[0]=='m'){
                sumaM += colaC->arrCola[i].salario;
                    contadorM++;
            }
            else if(colaC->arrCola[i].INE.genero[0]=='F' || colaC->arrCola[i].INE.genero[0]=='f'){
                    sumaF += colaC->arrCola[i].salario;
                    contadorF++;
                }
        }
    } else {
        for (int i = colaC->h; i < colaC->max; i++) {
            if(colaC->arrCola[i].INE.genero[0]=='M'||colaC->arrCola[i].INE.genero[0]=='m'){
                sumaM += colaC->arrCola[i].salario;
                    contadorM++;
            }
            else if(colaC->arrCola[i].INE.genero[0]=='F' || colaC->arrCola[i].INE.genero[0]=='f'){
                    sumaF += colaC->arrCola[i].salario;
                    contadorF++;
                }
        }
        for (int i = 0; i <= colaC->t; i++) {
            if(colaC->arrCola[i].INE.genero[0]=='M'||colaC->arrCola[i].INE.genero[0]=='m'){
                sumaM += colaC->arrCola[i].salario;
                    contadorM++;
            }
            else if(colaC->arrCola[i].INE.genero[0]=='F' || colaC->arrCola[i].INE.genero[0]=='f'){
                    sumaF += colaC->arrCola[i].salario;
                    contadorF++;
                }
        }
    }
    if(sumaM>sumaF){
            sumaM=(float)sumaM/ contadorM;
            fprintf(archivo, "\nEl genero con mayor expectativa salarial es el masculino con: %.2f", sumaM);
        } else
            if(sumaF>sumaM){
            sumaF=(float)sumaF/ contadorF;
            fprintf(archivo, "\nEl genero con mayor expectativa salarial es el femenino con: %.2f", sumaF);
        }
}