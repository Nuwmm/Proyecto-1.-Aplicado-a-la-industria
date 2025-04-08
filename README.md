# Proyecto-1.-Aplicado-a-la-industria
Proyecto 1. Aplicado a la industria para EDA I

Estadística del proyecto
Vamos a gestionar las solicitudes de empleo de una empresa. En dicha empresa se tienen que aceptar a aquellos que estén calificados para el empleo y también reconocer a los que no cumplen con los requisitos. 
En código esto se hace mediante una cola, primero se registran las personas que quieren ser contratadas y se van agregando a una cola para empezar con el primero que se registró. Luego existe una función que valida cada persona de cola si es apta o no para el puesto, las personas que no son aptas se mandan a una pila de NO ACEPTADOS y los que cumplen los requisitos se mandan a otra pila de SI ACEPTADOS, en un archivo .txt se muestran las personas aceptadas y las que no fueron aceptadas. También mostrar el número de cuántas fueron aceptadas y cuántas no.

La estructura del empleado cuenta con:
- Nombre 
- Edad *Nuevo miembro*
- ID
- Puesto al que aspiran
- Salario
- Antigüedad / Experiencia laboral
- Teléfono 
- Departamento 
- Respuestas *Validan si se contrata o no*

Encuesta
Los requisitos que tendría que cumplir cada aspirante es:
1. Ser mayor de edad
2. Tener un nivel de estudios de licenciatura o mayor
3. Tener experiencia laboral en alguna empresa
	3.1 Si no tiene experiencia el sueldo que pide debe ser menor a $3,000.
	3.2 Si tiene experiencia laboral el sueldo no debe pasar de $25,000.
4. Si tiene antecedentes penales se descarta de inmediato.
5. Del 1 al 10 cómo te consideras para el trabajo? Las especificaciones se ven después, pero cada numero debe tener una referencia para que el aspirante pueda calificarse, por ejemplo, 1 nada apto, en cambio 10 muy apto.
	5.1 Si su calificación es menor a 6 se descarta.

Debe cumplir todos los requisitos para ser aceptado. Las respuesta se guardan en un arreglo con valores de 0 y 1. Si responde "si" = 1, en el caso en el que responda "no" = 0. Debe cumplir con que todas sus respuestas sean 1, en el caso en que una no sea 1 se descarta y se manda a la pila de NO CONTRATADOS donde se va a decir el PORQUÉ NO FUERON CONTRATADOS.
