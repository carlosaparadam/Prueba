#include <stdio.h>
#include "materias.h"

void clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void pressCeroToContinue() {
	int continuar = 0;
    printf("Cero para continuar...");
    scanf("%d", &continuar);
}

int main()
{

    int numMaterias, numPrelaciones;
	Materia** materias = leerMateriasDesdeCSV("pensums/Informatica_Materias.csv", &numMaterias);
	Prelacion** prelaciones = leerPrelacionesDesdeCSV("pensums/Informatica_Prelaciones.csv", &numPrelaciones);

	if (materias != NULL && prelaciones != NULL) {
		int option = 100;
		char codBus[10];
		while (option > 0 ){
			clearScreen();
		    printf(" 1 ) Mostrar Pensum\n");
		    printf(" 2 ) Mostrar Prelaciones de una Materia\n");
		    printf(" 0 ) Salir\n");
		    scanf("%d", &option);

		    switch (option)
		    {
				case 1:
					mostrarPensum(materias, numMaterias, prelaciones, numPrelaciones);
					pressCeroToContinue();
					break;
				case 2:
					clearScreen();
					printf("Codigo de la Materia a consultar:");
				    scanf("%s", codBus);
					imprimirPrelacionesParaMateria(materias, numMaterias, prelaciones, numPrelaciones, codBus);
					pressCeroToContinue();
					break;
				default:
					break;

		    }
		}


		// Liberar la memoria asignada dinámicamente
		for (int i = 0; i < numMaterias; i++) {
			free(materias[i]);
		}
		free(materias);

		for (int i = 0; i < numPrelaciones; i++) {
			free(prelaciones[i]);
		}
		free(prelaciones);
	}

    return 0;
}
