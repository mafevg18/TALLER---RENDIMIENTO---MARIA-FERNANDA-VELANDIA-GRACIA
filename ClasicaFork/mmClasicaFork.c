/******************************************************************
*            Pontificia Universidad Javeriana                     *
*                         ---=---                                 *
*                                                                 *
* Autores: Danna Rojas, María Fernanda Velandia,                  * 
*	Cristian Becerra, Giovanny Duran                          *
* Fecha: 13 Noviembre 2025                                        *
* Docente:  J. Corredor                                           *
* Archivo:  mmClasicaFork.c                                       * 
* Objetivo: Implementar la multiplicación clásica de matrices     *
*	    utilizando procesos en paralelo mediante fork().      * 
* Descripción:                                                    *
*	- Multiplicación de dos matrices en varios procesos hijos.*
* 	- Cada proceso calcula una parte de la matriz y el        *
*	  resultado va a la memoria compartida.                   *
* 	- Se mide el tiempo total de ejecución.                   *
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "moClasicaFork.h"


int main(int argc, char *argv[]) {

    /*Validacion de argumentos*/
    if (argc < 3) {
        printf("\n \t\tUse: $./mmClasicaFork Size Hilos \n");
        exit(0);
    }
    int N      = (int) atoi(argv[1]);
    int num_P  = (int) atoi(argv[2]);

    /*Asignacion dinamica de memoria*/
    double *matA = (double *) calloc(N*N, sizeof(double));
    double *matB = (double *) calloc(N*N, sizeof(double));
    double *matC = create_shared_matrix(N); // compartida

    if(!matA || !matB || !matC){
        perror("Allocacion fallida");
        return 1;
    }

    /*Inicialización de matrices con valores aleatorios*/
    srand(time(0));
    iniMatrix(matA, matB, N);
    impMatrix(matA, N);
    impMatrix(matB, N);

    /* División del trabajo*/
    int rows_per_process = N / num_P;
    InicioMuestra();

    /*Creación de procesos hijos*/
    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            int start_row = i * rows_per_process;
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;
            
            /*Llamado a la función de multiplicación*/
            multiMatrix_region(matA, matB, matC, N, start_row, end_row);
            
            // imprimir sólo si N<9
            if (N < 9) {
                printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);
                for (int r = start_row; r < end_row; r++) {
                    for (int c = 0; c < N; c++) {
                        printf(" %.2f ", matC[N*r+c]);
                    }
                    printf("\n");
                }
            }
            _exit(0);
        } else if (pid < 0) {
         
            /*Control de error*/
            perror("fork failed");
            exit(1);
        }
    }
	
    
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }

    FinMuestra();

    /*Impresión de la matriz resultante*/
    impMatrix(matC, N);

    /*Liberación de memoria*/
    free(matA);
    free(matB);
    free_shared_matrix(matC, N);

    return 0;
}

