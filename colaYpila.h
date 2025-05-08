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
    Emp INE;//MOvimiento 1 
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
void listarArchivo(ColaCircular colaC, FILE *archivo);
void liberarMemoriaCola(ColaCircular *colaC);
void encuesta(ColaCircular *colaC);
void validarEmpleados(ColaCircular *colaC, Pila *pilaAceptados, Pila *pilaRechazados,int *aceptados, int *rechazados);
Empleados buscar(ColaCircular *colaC, int ID); // FUNCION BUSCAR 

//OPERACION DEL TAD PILA
void push(Empleados dato, Pila *pila);
Empleados pop(Pila *pila);
//OPERACIONES AUXILIARES TAD PILA
Pila *crearPila(int max);
int pilaVacia(Pila pila);
void listarPila(Pila pila);
void listarPilaArchivo(Pila pila, FILE *archivo);
void liberarMemoriaPila(Pila *pila);

//ESTADISTICAS
void mostrarPorcentajes(int aceptados, int rechazados, FILE *archivo);// se agrega la funcion para mostra la primera estadisticaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
void mostrarPromedio(ColaCircular *colaC, FILE *archivo);// se agreg� la funcion para dar el promedio de las edades de los candidatos___________________________________________________
void aceptadosYrechazados(Pila pilaAceptados, Pila pilaRechazados, FILE *archivo);
void promedioSalario(ColaCircular *colaC, FILE *archivo);
void salariosExpec(ColaCircular *colaC, FILE *archivo);
void mostrarEdadRango(ColaCircular *colaC, FILE *archivo);//Se agrego para el rango de 17 a 45
void contarGeneros(ColaCircular *colaC, FILE *archivo);
void mostrarEstados(ColaCircular *colaC, FILE *archivo);
void carrera(ColaCircular *cola, FILE *archivo);
void generoMayorP(ColaCircular *colaC, FILE *archivo);

#endif // COLAYPILA_H_INCLUDED
