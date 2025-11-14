/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha: 13 Noviembre 2025                                     *
* Docente:  J. Corredor                                        *
* Archivo:  moClasicaOpenMP.h                                  * 
*                                                              *
* Objetivo: Declarar las funciones auxiliares empleadas para   *
*           la multiplicación clásica de matrices usando       *
*           paralelismo con OpenMP.                            *
*                                                              *
* Descripción:                                                 *
*   - Define las cabeceras de funciones de inicialización,     *
*     impresión y multiplicación de matrices.                  *
*   - Contiene las rutinas para la medición del tiempo total   *
*     de ejecución.                                            *
**************************************************************/

#ifndef MO_CLASICA_OPENMP_H
#define MO_CLASICA_OPENMP_H

/* Marca el inicio de la medición del tiempo */
void InicioMuestra();

/* Calcula e imprime el tiempo total de ejecución */
void FinMuestra();

/* Inicializa matrices con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D);

/* Imprime la matriz si su dimensión es menor a 9 */
void impMatrix(double *matrix, int D);

/* Multiplica matrices en paralelo usando OpenMP */
void multiMatrix_openmp(double *mA, double *mB, double *mC, int D);

#endif

