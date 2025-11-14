/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha:   13 Noviembre 2025                                   *
* Docente:  J. Corredor                                        *
* Archivo:  mmFilasOpenMP.c                                    * 
*                                                              *
* Objetivo: Implementar la multiplicación clásica de matrices  *
*           utilizando OpenMP y optimización por filas y       *
*           columnas transpuestas.                             *
*                                                              *
* Descripción:                                                 *
*   - Multiplica dos matrices cuadradas de tamaño N empleando  *
*     paralelismo con OpenMP.                                  *
*   - Mide el tiempo total de ejecución del cálculo paralelo.  *
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "moFilasOpenMP.h"

int main(int argc, char *argv[]){
    /* Validación de argumentos */
    if(argc < 3){
        printf("\n Use: $./mmFilasOpenMP SIZE Hilos \n\n");
        exit(0);
    }

    int N = atoi(argv[1]);
    int TH = atoi(argv[2]);

    /* Asignación dinámica de memoria para matrices */
    double *matrixA  = (double *)calloc(N*N, sizeof(double));
    double *matrixB  = (double *)calloc(N*N, sizeof(double));
    double *matrixC  = (double *)calloc(N*N, sizeof(double));

    /* Inicialización de la semilla aleatoria */
    srand(time(NULL));

    /* Configuración del número de hilos de OpenMP */
    omp_set_num_threads(TH);

    /* Inicialización de matrices con valores aleatorios */
    iniMatrix(matrixA, matrixB, N);

    /* Impresión de matrices de entrada */
    impMatrix(matrixA, N, 0);
    impMatrix(matrixB, N, 1);

    /* Medición del tiempo de ejecución de la multiplicación */
    InicioMuestra();
    multiMatrixTrans(matrixA, matrixB, matrixC, N);
    FinMuestra();

    /* Impresión de la matriz resultante */
    impMatrix(matrixC, N, 0);

    /* Liberación de memoria dinámica */
    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}

