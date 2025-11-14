/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha:   13 Noviembre 2025                                   *
* Docente:  J. Corredor                                        *
* Archivo:  mmClasicaPosix.c                                   * 
*                                                              *
* Objetivo: Implementar la multiplicación clásica de matrices  *
*           utilizando hilos POSIX para el cálculo paralelo.   *
*                                                              *
* Descripción:                                                 *
*   - Multiplica dos matrices cuadradas de tamaño N dividiendo *
*     las filas entre múltiples hilos de ejecución.            *
*   - Cada hilo calcula una parte de la matriz resultado.      *
*   - Se mide el tiempo total de ejecución y se imprimen las   *
*     matrices si el tamaño es pequeño.                        *
**************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "moClasicaPosix.h"

double *matrixA, *matrixB, *matrixC;
pthread_mutex_t MM_mutex_local;

/* Función que ejecuta la multiplicación para cada hilo */
void *multiMatrix(void *variables){
    struct parametros *data = (struct parametros *)variables;

    int idH     = data->idH;
    int nH      = data->nH;
    int D       = data->N;
    int filaI   = (D/nH)*idH;
    int filaF   = (idH == nH-1) ? D : (D/nH)*(idH+1);
    double Suma, *pA, *pB;

    for (int i = filaI; i < filaF; i++){
        for (int j = 0; j < D; j++){
            pA = matrixA + i*D;
            pB = matrixB + j;
            Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB+=D){
                Suma += *pA * *pB;
            }
            matrixC[i*D+j] = Suma;
        }
    }

    free(data);
    pthread_exit(NULL);
}

/* Función principal que controla la ejecución de los hilos POSIX */
int main(int argc, char *argv[]){
    /* Validación de argumentos */
    if (argc < 3){
        printf("Ingreso de argumentos \n $./mmClasicaPosix tamMatriz numHilos\n");
        exit(0);
    }

    int N = atoi(argv[1]);
    int n_threads = atoi(argv[2]);

    /* Asignación dinámica de memoria para los hilos y matrices */
    pthread_t *p = malloc(sizeof(pthread_t)*n_threads);

    matrixA  = (double *)calloc(N*N, sizeof(double));
    matrixB  = (double *)calloc(N*N, sizeof(double));
    matrixC  = (double *)calloc(N*N, sizeof(double));

    /* Inicialización de la semilla aleatoria */
    srand(time(NULL));

    /* Inicialización y visualización de matrices */
    iniMatrix(matrixA, matrixB, N);
    impMatrix(matrixA, N);
    impMatrix(matrixB, N);

    /* Inicio de la medición de tiempo */
    InicioMuestra();

    pthread_mutex_init(&MM_mutex_local, NULL);

    /* Creación de hilos para la multiplicación */
    for (int j=0; j<n_threads; j++){
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));
        datos->idH = j;
        datos->nH  = n_threads;
        datos->N   = N;

        pthread_create(&p[j], NULL, multiMatrix, (void *)datos);
    }

    /* Espera a que todos los hilos terminen */
    for (int j=0; j<n_threads; j++)
        pthread_join(p[j],NULL);

    /* Fin de la medición de tiempo */
    FinMuestra();

    /* Impresión de la matriz resultado */
    impMatrix(matrixC, N);

    /* Liberación de memoria dinámica y destrucción del mutex */
    free(matrixA);
    free(matrixB);
    free(matrixC);
    free(p);

    pthread_mutex_destroy(&MM_mutex_local);

    return 0;
}

