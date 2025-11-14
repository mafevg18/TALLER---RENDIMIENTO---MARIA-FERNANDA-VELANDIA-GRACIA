/******************************************************************
*            Pontificia Universidad Javeriana                     *
*                         ---=---                                 *
*                                                                 *
* Autores: Danna Rojas, María Fernanda Velandia,                  * 
*	Cristian Becerra, Giovanny Duran                          *
* Fecha: 13 Noviembre 2025                                        *
* Docente:  J. Corredor                                           *
* Archivo:  mmClasicaOPenMp.c                                     * 
* Objetivo: Implementar la multiplicación clásica de matrices     *
*	    utilizando procesos en paralelo con la biblioteca     *
*	    OpenMP                                                * 
* Descripción:                                                    *
*	- Multiplicación de dos matrices en varios procesos hijos.*
* 	- Cada proceso calcula una parte de la matriz y el        *
*	  resultado va a la memoria compartida.                   *
* 	- Se mide el tiempo total de ejecución.                   *
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "moClasicaOpenMP.h"

int main(int argc, char *argv[]){
    /* Validación de argumentos */
    if(argc < 3){
        printf("\n Use: $./mmClasicaOpenMP SIZE Hilos \n\n");
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

    /* Impresión de las matrices iniciales si N < 9 */
    impMatrix(matrixA, N);
    impMatrix(matrixB, N);

    /* Medición del tiempo de ejecución de la multiplicación */
    InicioMuestra();
    multiMatrix_openmp(matrixA, matrixB, matrixC, N);
    FinMuestra();

    /* Impresión de la matriz resultante si N < 9 */
    impMatrix(matrixC, N);

    /* Liberación de memoria dinámica */
    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}

