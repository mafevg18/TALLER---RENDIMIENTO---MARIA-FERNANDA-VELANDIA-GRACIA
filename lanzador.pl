###############################################################
#            Pontificia Universidad Javeriana                 #
#                         ---=---                             #
#                                                             #
# Autores:  Danna Rojas, María Fernanda Velandia,             #
#           Cristian Becerra, Giovanny Durán                  #
# Fecha: 13 Noviembre 2025                                    #
# Docente:  J. Corredor                                       #
# Archivo:  lanzador.pl                                       #
#                                                             #
# Objetivo: Automatizar la compilación y ejecución de los     #
#           programas de multiplicación de matrices en sus    #
#           distintas versiones.                              #
#                                                             #
# Descripción:                                                #
#   - Ejecuta los binarios de multiplicación con diferentes   #
#     tamaños de matriz y número de hilos o procesos.         #
#   - Calcula el promedio de tiempos de ejecución y guarda los#
#     resultados en archivos .dat dentro de la carpeta results.#
#   - Permite comparar el rendimiento entre versiones.        #
###############################################################

#!/usr/bin/perl
use strict;
use warnings;
use File::Spec;

# Definición de ejecutables, tamaños de matriz y número de hilos/procesos
my @executables = (
    "./ClasicaFork/mmClasicaFork",
    "./ClasicaPosix/mmClasicaPosix",
    "./ClasicaOpenMP/mmClasicaOpenMP",
    "./FilasOpenMP/mmFilasOpenMP"
);

my @sizes   = (600, 800, 1200, 2400);    # tamaños de matriz
my @threads = (1, 2, 4, 12, 32);         # número de hilos/procesos
my $reps    = 30;                         # repeticiones por prueba
my $results_dir = "results";

# Crear carpeta results si no existe
mkdir $results_dir unless -d $results_dir;

# Archivo CSV resumen
my $csv_file = "$results_dir/resumen_general.csv";
open(my $csv, '>', $csv_file) or die "No se pudo crear $csv_file: $!";
print $csv "Programa,Tamaño,Hilos,Promedio_microsegundos\n";

# Bucle principal: ejecutar todos los programas para cada tamaño y número de hilos
foreach my $exe (@executables) {
    unless (-x $exe) {
        warn "  No se encontró ejecutable o no es ejecutable: $exe\n";
        next;
    }
    print "\n=== Ejecutando pruebas para $exe ===\n";

    foreach my $size (@sizes) {
        foreach my $th (@threads) {
            # Archivo de resultados por combinación
            my $base = (File::Spec->splitpath($exe))[2];
            my $file = "$results_dir/$base-$size-Hilos-$th.dat";
            open(my $fh, '>', $file) or die "No se pudo abrir $file: $!\n";

            # Ejecutar el programa repetidamente y capturar tiempos
            my @times;
            for (my $i=0; $i<$reps; $i++) {
                my $cmd = "$exe $size $th 2>/dev/null";
                my $output = `$cmd`;
                if ($output =~ /(-?\d+(\.\d+)?)/) {
                    push @times, $1 + 0;
                } else {
                    push @times, -1;
                }
                print "[$base] Size=$size Threads=$th Run ".($i+1)."/$reps -> $times[-1]\n";
            }

            # Calcular promedio de tiempos válidos
            my @good = grep { $_ >= 0 } @times;
            my $avg = 0;
            if (@good) {
                my $sum = 0; $sum += $_ for @good;
                $avg = $sum / scalar(@good);
            } else {
                $avg = -1;
            }

            # Guardar resultados en archivo .dat
            print $fh "Repetición\tTiempo_microsegundos\n";
            for (my $i=0; $i<@times; $i++) {
                print $fh ($i+1)."\t".$times[$i]."\n";
            }
            print $fh "Promedio\t$avg\n";
            close($fh);

            printf(" Guardado: %s (promedio = %.2f µs)\n", $file, $avg);
            print $csv "$base,$size,$th,$avg\n";
        }
    }
}

close($csv);

# Mensaje final de resumen
print "\n Resultados guardados en la carpeta '$results_dir'\n";
print " Resumen CSV general: $csv_file\n";

