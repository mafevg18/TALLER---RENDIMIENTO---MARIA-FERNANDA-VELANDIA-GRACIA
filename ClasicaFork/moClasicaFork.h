/******************************************************************
*            Pontificia Universidad Javeriana                     *
*                         ---=---                                 *
*                                                                 *
* Autores: Danna Rojas, María Fernanda Velandia,                  * 
*           Cristian Becerra, Giovanny Duran                      *
* Fecha: 13 Noviembre 2025                                        *
* Docente:  J. Corredor                                           *
* Archivo:  moClasicaFork.h                                        * 
* Objetivo: Declarar funciones auxiliares para                    *
*           la multiplicación clásica de matrices                 *
*           utilizando procesos mediante fork().                  * 
* Descripción:                                                    *
*   - Funciones de inicialización, impresión y                    *
*     multiplicación parcial.                                     *
*   - Gestión de memoria compartida y medición de tiempos         *
*     de ejecución.                                               *
******************************************************************/

#ifndef MO_CLASICA_FORK_H
#define MO_CLASICA_FORK_H

#include <sys/types.h>

/* Marca el inicio de la medición del tiempo */
void InicioMuestra();

/* Calcula e imprime el tiempo total de ejecución */
void FinMuestra();

/* Inicializa matrices con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D);

/* Imprime la matriz si su dimensión es menor a 9 */
void impMatrix(double *matrix, int D);

/* Multiplica una región de la matriz para un proceso hijo */
void multiMatrix_region(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

/* Crea una matriz compartida entre procesos */
double *create_shared_matrix(int N);

/* Libera la memoria de una matriz compartida */
void free_shared_matrix(double *ptr, int N);

#endif

