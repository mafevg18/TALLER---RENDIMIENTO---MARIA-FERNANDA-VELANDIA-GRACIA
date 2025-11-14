/***************************************************************
*            Pontificia Universidad Javeriana                  *
*                         ---=---                              *
*                                                              *
* Autores:  Danna Rojas, María Fernanda Velandia,              *
*           Cristian Becerra, Giovanny Durán                   *
* Fecha: 13 Noviembre 2025                                     *
* Docente:  J. Corredor                                        *
* Archivo:  moFilasOpenMP.c                                    * 
*                                                              *
* Objetivo: Implementar las funciones auxiliares utilizadas    *
*           en la multiplicación clásica de matrices optimizada*
*           por filas y columnas transpuestas, empleando       *
*           paralelismo con OpenMP.                            *
*                                                              *
* Descripción:                                                 *
*   - Inicializa e imprime matrices cuadradas de tamaño N.     *
*   - Implementa la multiplicación                             *
*   - Incluye funciones para medir el tiempo total de ejecución.*
**************************************************************/

#include "moFilasOpenMP.h"
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

/* Imprime la matriz según tipo de presentación y si D<6 */
void impMatrix(double *matrix, int D, int t){
    int aux = 0;
    if(D < 6)
        switch(t){
            case 0:
                for(int i=0; i<D*D; i++){
                    if(i%D==0) printf("\n");
                        printf("%.2f ", matrix[i]);
                }
                printf("\n  - \n");
                break;
            case 1:
                while(aux<D){
                    for(int i=aux; i<D*D; i+=D)
                        printf("%.2f ", matrix[i]);
                    aux++;
                    printf("\n");
                }
                printf("\n  - \n");
                break;
            default:
                printf("Sin tipo de impresión\n");
        }
}

/* Inicializa matrices con valores aleatorios */
void iniMatrix(double *m1, double *m2, int D){
    for(int i=0;i<D*D;i++, m1++, m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);
        *m2 = (double)rand()/RAND_MAX*(9.0-5.0);
    }
}

/* Multiplica matrices usando filas y columnas transpuestas con OpenMP */
void multiMatrixTrans(double *mA, double *mB, double *mC, int D){
    double Suma, *pA, *pB;
    #pragma omp parallel
    {
    #pragma omp for
    for(int i=0; i<D; i++){
        for(int j=0; j<D; j++){
            pA = mA+i*D;
            pB = mB+j*D;
            Suma = 0.0;
            for(int k=0; k<D; k++, pA++, pB++){
                Suma += *pA * *pB;
            }
            mC[i*D+j] = Suma;
        }
    }
    }
}

