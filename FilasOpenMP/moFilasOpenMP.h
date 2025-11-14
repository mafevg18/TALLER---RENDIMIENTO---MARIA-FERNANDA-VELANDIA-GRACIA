/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha:  13  Noviembre 2025                                   *
* Docente:  J. Corredor                                        *
* Archivo:  moFilasOpenMP.h                                    * 
*                                                              *
* Objetivo: Declarar las funciones auxiliares utilizadas para  *
*           la multiplicación de matrices optimizada por filas *
*           y transposición, empleando paralelismo con OpenMP. *
*                                                              *
* Descripción:                                                 *
*   - Define las funciones de inicialización, impresión y      *
*     multiplicación paralela con matriz transpuesta.          *
*   - Incluye rutinas para medir el tiempo total de ejecución. *
**************************************************************/

#ifndef MO_FILAS_OPENMP_H
#define MO_FILAS_OPENMP_H

/* Marca el inicio de la medición del tiempo */
void InicioMuestra();

/* Calcula e imprime el tiempo total de ejecución */
void FinMuestra();

/* Inicializa matrices con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D);

/* Imprime la matriz según tipo de presentación y tamaño */
void impMatrix(double *matrix, int D, int t);

/* Multiplica matrices usando filas y columnas transpuestas con OpenMP */
void multiMatrixTrans(double *mA, double *mB, double *mC, int D);

#endif

