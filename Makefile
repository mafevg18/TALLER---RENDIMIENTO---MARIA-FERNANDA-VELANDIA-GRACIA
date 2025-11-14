###############################################################
#            Pontificia Universidad Javeriana                 #
#                         ---=---                             #
#                                                             #
# Autores:  Danna Rojas, María Fernanda Velandia,             #
#           Cristian Becerra, Giovanny Durán                  #
# Fecha: 13 Noviembre 2025                                    #
# Docente:  J. Corredor                                       #
# Archivo:  Makefile                                          #
#                                                             #
# Objetivo: Automatizar el proceso de compilación de los      #
#           programas de multiplicación de matrices en sus    #
#           diferentes versiones.                             #
#                                                             #
# Descripción:                                                #
#   - Permite limpiar los archivos objeto y ejecutables.      #
#   - Facilita la ejecución rápida y ordenada de los módulos. #
###############################################################

GCC = gcc

PROGRAMAS = ClasicaFork/mmClasicaFork \
            ClasicaPosix/mmClasicaPosix \
            ClasicaOpenMP/mmClasicaOpenMP \
            FilasOpenMP/mmFilasOpenMP

CFLAGS = -O3 -lm -pthread
FOPENMP = -fopenmp -O3

ClasicaFork/mmClasicaFork:
	$(GCC) $(CFLAGS) ClasicaFork/mmClasicaFork.c ClasicaFork/moClasicaFork.c -o $@

ClasicaPosix/mmClasicaPosix:
	$(GCC) $(CFLAGS) ClasicaPosix/mmClasicaPosix.c ClasicaPosix/moClasicaPosix.c -o $@

ClasicaOpenMP/mmClasicaOpenMP:
	$(GCC) $(CFLAGS) $(FOPENMP) ClasicaOpenMP/mmClasicaOpenMP.c ClasicaOpenMP/moClasicaOpenMP.c -o $@

FilasOpenMP/mmFilasOpenMP:
	$(GCC) $(CFLAGS) $(FOPENMP) FilasOpenMP/mmFilasOpenMP.c FilasOpenMP/moFilasOpenMP.c -o $@

clean:
	-rm -f $(PROGRAMAS)

