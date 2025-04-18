#ifndef COLAYPILA_H_INCLUDED
#define COLAYPILA_H_INCLUDED

#define MAX_ENCUESTA 5
#define MAX_TEXTO 50

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
} Empleados;

typedef struct {
    int max; // tamanio de la cola
    int h;
    int t;
    Empleados *arrCola; //arreglo cola
} ColaCircular;

typedef struct
{
    int max; // Tamnio de la pila
    int cima; //Tope de la pila
    Empleados *arrPila;
} Pila;

//OPERACIONES DEL TAD COLA
void insertar(ColaCircular *colaC, Empleados empleado) ;
Empleados borrar(ColaCircular *colaC);

//OPERACIONES AUXILIARES DE TAD COLA
ColaCircular *crearColaCircular(int max);
int validarEspacio(ColaCircular colaC);
int validarVacio(ColaCircular colaC);
void listar(ColaCircular colaC);
void liberarMemoriaCola(ColaCircular *colaC);
void encuesta(ColaCircular *colaC);
void validarEmpleados(ColaCircular *colaC, Pila *pilaAceptados, Pila *pilaRechazados);

//OPERACION DEL TAD PILA
void push(Empleados dato, Pila *pila);
Empleados pop(Pila *pila);

//OPERACIONES AUXILIARES TAD PILA
Pila *crearPila(int max);
int pilaVacia(Pila pila);
void listarPila(Pila pila);
void liberarMemoriaPila(Pila *pila);

#endif // COLAYPILA_H_INCLUDED