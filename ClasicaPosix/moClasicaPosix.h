/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha:   13 Noviembre 2025                                   *
* Docente:  J. Corredor                                        *
* Archivo:  moClasicaPosix.h                                   * 
*                                                              *
* Objetivo: Declarar las funciones y estructuras auxiliares    *
*           utilizadas para la multiplicación clásica de       *
*           matrices mediante hilos POSIX.                     *
*                                                              *
* Descripción:                                                 *
*   - Define las funciones de inicialización, impresión y      *
*     medición de tiempo de matrices.                          *
*   - Declara la estructura de parámetros compartidos por los  *
*     hilos durante la multiplicación paralela.                *
**************************************************************/

#ifndef MO_CLASICA_POSIX_H
#define MO_CLASICA_POSIX_H

/* Marca el inicio de la medición del tiempo */
void InicioMuestra();

/* Calcula e imprime el tiempo total de ejecución */
void FinMuestra();

/* Inicializa matrices con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D);

/* Imprime la matriz si su dimensión es menor a 9 */
void impMatrix(double *matriz, int D);

/* Función que ejecuta la multiplicación para cada hilo POSIX */
void *multiMatrix_thread(void *variables);

/* Estructura de parámetros compartida por los hilos */
struct parametros{
    int nH;
    int idH;
    int N;
};

#endif

