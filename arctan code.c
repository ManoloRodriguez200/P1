#include <ucontext.h>
#include <signal.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

void arctan () {
 int CargaTrabajo=100; //Para ser cambiado por el valor leido del archivo o teclado
 int iteraciones= CargaTrabajo *50;
 double pi=0.0;
 int n=0;
 double DetenerPorcentaje = 50.0;
 double PorcentajeCompletado=0.0;
 double arctan = 0.0;
 int FlagDetener=0;


 printf("Carga de trabajo de entrada=%i\n", CargaTrabajo);
 printf("Iniciando calculo para PI\n");

 for (n=0; n<iteraciones; n++) {

	if (FlagDetener ==1) break;
	arctan=arctan + pow((double)-1.0, (double)n) / (2.0*(double)n+1.0);
	PorcentajeCompletado = ((double)n/(double)iteraciones)*100.0;

	if (PorcentajeCompletado == DetenerPorcentaje) {
		FlagDetener =1;
		printf("Bandera de detencion\n");
		}
	}
        pi=4.0*arctan;
	printf("Carga de trabajo completado=%f\n", PorcentajeCompletado);
        printf("Resultado del calculo de PI=%f\n",pi);
//	return(pi,percent_done);
}