#ifndef COLAYPILA_H_INCLUDED
#define COLAYPILA_H_INCLUDED

#define MAX_ENCUESTA 5
#define MAX_TEXTO 50

typedef struct{
    char estado[MAX_TEXTO];
    char genero[MAX_TEXTO];
}   Emp;

typedef struct
{
    char *nombre;
    int edad;
    int id;
    char *puesto;
    float salario;
    char *experiencia;
    char *telefono;
    char *departamento;
    int *respuestas;
    Emp INE;
} Empleados;

typedef struct {
    int max;
    int h;
    int t;
    Empleados *arrCola;
} ColaCircular;

typedef struct
{
    int max;
    int cima;
    Empleados *arrPila;
} Pila;

void insertar(ColaCircular *colaC, Empleados empleado) ;
Empleados borrar(ColaCircular *colaC);

ColaCircular *crearColaCircular(int max);
int validarEspacio(ColaCircular colaC);
int validarVacio(ColaCircular colaC);
void listar(ColaCircular colaC);
void listarArchivo(ColaCircular colaC, FILE *archivo);
void liberarMemoriaCola(ColaCircular *colaC);
void encuesta(ColaCircular *colaC);
void validarEmpleados(ColaCircular *colaC, Pila *pilaAceptados, Pila *pilaRechazados,int *aceptados, int *rechazados);
Empleados *buscar(ColaCircular *colaC, int ID);

void push(Empleados dato, Pila *pila);
Empleados pop(Pila *pila);
Pila *crearPila(int max);
int pilaVacia(Pila pila);
void listarPila(Pila pila);
void listarPilaArchivo(Pila pila, FILE *archivo);
void liberarMemoriaPila(Pila *pila);

void mostrarPorcentajes(int aceptados, int rechazados, FILE *archivo);
void mostrarPromedio(ColaCircular *colaC, FILE *archivo);
void aceptadosYrechazados(Pila pilaAceptados, Pila pilaRechazados, FILE *archivo);
void promedioSalario(ColaCircular *colaC, FILE *archivo);
void salariosExpec(ColaCircular *colaC, FILE *archivo);
void mostrarEdadRango(ColaCircular *colaC, FILE *archivo);
void contarGeneros(ColaCircular *colaC, FILE *archivo);
void mostrarEstados(ColaCircular *colaC, FILE *archivo);
void carrera(ColaCircular *cola, FILE *archivo);
void generoMayorP(ColaCircular *colaC, FILE *archivo);

#endif
