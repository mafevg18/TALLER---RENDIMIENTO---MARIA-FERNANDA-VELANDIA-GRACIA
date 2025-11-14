/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha: 13 Noviembre 2025                                     *
* Docente:  J. Corredor                                        *
* Archivo:  moClasicaOpenMP.c                                  * 
*                                                              *
* Objetivo: Implementar las funciones auxiliares utilizadas    *
*           para la multiplicación clásica de matrices con     *
*           paralelismo mediante OpenMP.                       *
*                                                              *
* Descripción:                                                 *
*   - Inicializa y muestra matrices cuadradas de tamaño N.     *
*   - Implementa la multiplicación paralela con directivas     *
*     OpenMP.                                                  *
*   - Mide el tiempo total de ejecución de la operación.       *
**************************************************************/

#include "moClasicaOpenMP.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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

/* Imprime la matriz si su dimensión es menor a 9 */
void impMatrix(double *matrix, int D){
    if(D < 9){
        printf("\n");
        for(int i=0; i<D*D; i++){
            if(i%D==0) printf("\n");
            printf("%.2f ", matrix[i]);
        }
        printf("\n**-----------------------------**\n");
    }
}

/* Inicializa las matrices con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D){
    for(int i=0;i<D*D;i++, m1++, m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);
        *m2 = (double)rand()/RAND_MAX*(9.0-2.0);
    }
}

/* Multiplica matrices en paralelo usando OpenMP */
void multiMatrix_openmp(double *mA, double *mB, double *mC, int D){
    double Suma, *pA, *pB;
    #pragma omp parallel
    {
    #pragma omp for
    for(int i=0; i<D; i++){
        for(int j=0; j<D; j++){
            pA = mA+i*D;
            pB = mB+j;
            Suma = 0.0;
            for(int k=0; k<D; k++, pA++, pB+=D){
                Suma += *pA * *pB;
            }
            mC[i*D+j] = Suma;
        }
    }
    }
}

