/******************************************************************
*            Pontificia Universidad Javeriana                     *
*                         ---=---                                 *
*                                                                 *
* Autores: Danna Rojas, María Fernanda Velandia,                  * 
*	Cristian Becerra, Giovanny Duran                          *
* Fecha: 13 Noviembre 2025                                        *
* Docente:  J. Corredor                                           *
* Archivo:  moClasicaFork.c                                       * 
* Objetivo: Implementar funciones auxiliares                      *
*	    la multiplicación clásica de matrices                 *
*	    utilizando procesos mediante fork().                  * 
* Descripción:                                                    *
*	- Definiciones de funciones en moClasicaFork.h            *
******************************************************************/

#define _GNU_SOURCE
#include "moClasicaFork.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

static struct timeval inicio, fin;

/* Marca el inicio de la medición del tiempo */
void InicioMuestra(){
    gettimeofday(&inicio, NULL);
}

/* Calcula el tiempo total transcurrido y lo imprime */
void FinMuestra(){
    gettimeofday(&fin, NULL);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
    printf("%9.0f \n", tiempo);
}

/* Inicializa las matrices A y B con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D){
    for (int i = 0; i < D*D; i++, m1++, m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);
        *m2 = (double)rand()/RAND_MAX*(9.0-5.0);
    }
}

/* Imprime la matriz si su dimensión es menor a 9 */
void impMatrix(double *matrix, int D){
    if (D < 9) {
        printf("\nImpresión    ...\n");
        for (int i = 0; i < D*D; i++, matrix++) {
            if(i%D==0) printf("\n");
            printf(" %.2f ", *matrix);
        }
        printf("\n ");
    }
}

/* Multiplica una región de la matriz (por filas asignadas) */
void multiMatrix_region(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
    double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) {
        for (int j = 0; j < D; j++) {
            Suma = 0.0;
            pA = mA + i*D;
            pB = mB + j;
            for (int k = 0; k < D; k++, pA++, pB+=D) {
                Suma += *pA * *pB;
            }
            mC[i*D+j] = Suma;
        }
    }
}

/* Crea una matriz compartida en memoria usando mmap() */
double *create_shared_matrix(int N){
    size_t bytes = sizeof(double) * N * N;
    void *ptr = mmap(NULL, bytes, PROT_READ | PROT_WRITE,
                     MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return NULL;
    }
    
    double *d = (double *)ptr;
    for (int i=0;i<N*N;i++) d[i]=0.0;
    return d;
}

/* Libera la memoria compartida reservada con mmap() */
void free_shared_matrix(double *ptr, int N){
    if (!ptr) return;
    size_t bytes = sizeof(double) * N * N;
    munmap((void*)ptr, bytes);
}

