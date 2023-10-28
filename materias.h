#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char codigo[10];
    char nombre[100];
} Materia;

typedef struct {
    char codigoMateria[10];
    char codigoPrelacion[10];
} Prelacion;

char* obtenerNombreMateria(const char* codigoMateria, Materia** materias, int numMaterias) {
	char* nombreMateria;
	 for (int i = 0; i < numMaterias; i++) {
		 if (strcmp(materias[i]->codigo, codigoMateria) == 0) {
			 nombreMateria = materias[i]->nombre;
			 break;
		 }
	 }
	 return nombreMateria;
}

// Función para leer materias desde un archivo CSV
Materia** leerMateriasDesdeCSV(const char* nombreArchivo, int* numMaterias) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    Materia** materias = (Materia**)malloc(100 * sizeof(Materia*));
    *numMaterias = 0;

    char linea[128]; // Tamaño suficiente para una línea del archivo CSV
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (*numMaterias >= 100) {
            printf("Se ha alcanzado el límite máximo de materias.\n");
            break;
        }

        // Parsear la línea del CSV
        char* codigo = strtok(linea, ",");
        char* nombre = strtok(NULL, "\n");

        if (codigo != NULL && nombre != NULL) {
            materias[*numMaterias] = (Materia*)malloc(sizeof(Materia));
            strcpy(materias[*numMaterias]->codigo, codigo);
            strcpy(materias[*numMaterias]->nombre, nombre);
            (*numMaterias)++;
        }
    }

    fclose(archivo);
    return materias;
}

// Función para leer las relaciones de prelación desde un archivo CSV
Prelacion** leerPrelacionesDesdeCSV(const char* nombreArchivo, int* numPrelaciones) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    Prelacion** prelaciones = (Prelacion**)malloc(100 * sizeof(Prelacion*));
    *numPrelaciones = 0;

    char linea[128];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (*numPrelaciones >= 100) {
            printf("Se ha alcanzado el límite máximo de relaciones de prelación.\n");
            break;
        }

        // Parsear la línea del CSV
        char* codigoMateria = strtok(linea, ",");
        char* codigoPrelacion = strtok(NULL, "\n");

        if (codigoMateria != NULL && codigoPrelacion != NULL) {
            prelaciones[*numPrelaciones] = (Prelacion*)malloc(sizeof(Prelacion));
            strcpy(prelaciones[*numPrelaciones]->codigoMateria, codigoMateria);
            strcpy(prelaciones[*numPrelaciones]->codigoPrelacion, codigoPrelacion);
            (*numPrelaciones)++;
        }
    }

    fclose(archivo);
    return prelaciones;
}

void mostrarPensum(Materia** materias, int numMaterias, Prelacion** prelaciones, int numPrelaciones) {
    printf("Codigo | Nombre | Cod Prelacion | Nombre Prelacion\n");
    for (int i = 0; i < numMaterias; i++) {
        char* codigoMateria = materias[i]->codigo;
        char* nombreMateria = materias[i]->nombre;

        char* codigoPrelacion = NULL;
        int hasPrelation = 0;
        char* nombrePrelacion = NULL;

        for (int j = 0; j < numPrelaciones; j++) {
            if (strcmp(prelaciones[j]->codigoMateria, codigoMateria) == 0) {
            	codigoPrelacion = prelaciones[j]->codigoPrelacion;
            	nombrePrelacion = obtenerNombreMateria(codigoPrelacion, materias, numMaterias);
            }

            if (codigoPrelacion!=NULL){
            	hasPrelation = 1;
            	printf("%s | %s | %s | %s\n", codigoMateria, nombreMateria, codigoPrelacion, nombrePrelacion);
            }
            codigoPrelacion= NULL;
        }
        if (hasPrelation == 0)
        	printf("%s | %s | %s | %s\n", codigoMateria, nombreMateria, "", "");

        hasPrelation = 0;
    }
}

// Función para imprimir las prelaciones para una materia específica
void imprimirPrelacionesParaMateria(Materia** materias, int numMaterias, Prelacion** prelaciones, int numPrelaciones, const char* codigoMateria) {
    printf("Prelaciones para la materia con código %s:\n", codigoMateria);
    for (int i = 0; i < numPrelaciones; i++) {
        if (strcmp(prelaciones[i]->codigoMateria, codigoMateria) == 0) {
            char* codigoPrelacion = prelaciones[i]->codigoPrelacion;

            // Buscar el nombre de la prelación en el arreglo de materias
            for (int j = 0; j < numMaterias; j++) {
                if (strcmp(materias[j]->codigo, codigoPrelacion) == 0) {
                    printf("Código de Prelación: %s, Nombre: %s\n", codigoPrelacion, materias[j]->nombre);
                    imprimirPrelacionesParaMateria(materias, numMaterias, prelaciones, numPrelaciones, codigoPrelacion);
                    break;  // Romper el bucle una vez que se haya encontrado la prelación
                }
            }
        }
    }
}
