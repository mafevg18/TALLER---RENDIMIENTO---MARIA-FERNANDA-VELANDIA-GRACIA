/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha:  13  Noviembre 2025                                   *
* Docente:  J. Corredor                                        *
* Archivo:  moClasicaPosix.c                                   * 
*                                                              *
* Objetivo: Implementar las funciones auxiliares utilizadas    *
*           para la multiplicación clásica de matrices con     *
*           hilos POSIX.                                       *
*                                                              *
* Descripción:                                                 *
*   - Inicializa y muestra matrices cuadradas de tamaño N.     *
*   - Implementa funciones para medir el tiempo de ejecución.  *
*   - Apoya el cálculo paralelo en el archivo principal con    *
*     funciones auxiliares reutilizables.                      *
**************************************************************/

#include "moClasicaPosix.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

pthread_mutex_t MM_mutex;

static struct timeval inicio, fin;

/* Marca el inicio de la medición del tiempo */
void InicioMuestra(){
    gettimeofday(&inicio, NULL);
}

/* Calcula e imprime el tiempo total de ejecución */
void FinMuestra(){
    gettimeofday(&fin, NULL);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
    printf("%9.0f \n", tiempo);
}

/* Inicializa matrices con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D){
    for(int i=0;i<D*D;i++,m1++,m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);
        *m2 = (double)rand()/RAND_MAX*(9.0-5.0);
    }
}

/* Imprime la matriz si su dimensión es menor a 9 */
void impMatrix(double *matriz, int D){
    if(D < 9){
        for(int i = 0; i < D*D; i++){
            if(i%D==0) printf("\n");
            printf(" %.2f ", matriz[i]);
        }
        printf("\n>-------------------->\n");
    }
}

